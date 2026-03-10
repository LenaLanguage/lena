/* lena-codegen.c
   Updated: support for cli::out, cli::err, cli::in (i32 / str), cli::flush,
   and representation of `str` as slice { i8*, i64 }.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lena-codegen.h"
#include "lena-ast.h"
#include "lena-util.h"

/* --- type mapping --- */
/* Note: str maps to named LLVM type %str_t (i8*, i64). */
static const char *map_type(const char *t) {
    if (!t) return "i32";
    if (strcmp(t, "i32") == 0) return "i32";
    if (strcmp(t, "i64") == 0) return "i64";
    if (strcmp(t, "i8") == 0) return "i8";
    if (strcmp(t, "u64") == 0) return "i64";
    if (strcmp(t, "nil") == 0) return "void";
    if (strcmp(t, "exit_status") == 0) return "i32";
    if (strcmp(t, "str") == 0) return "%str_t"; /* slice struct type */
    return "i32"; /* default */
}

/* symbol table for codegen */
typedef struct sym_t {
    char *name;
    char *llname; /* could be pointer name (%tX), global name (@.strX), or immediate literal "0" */
    char *lltype;
    struct sym_t *next;
} sym_t;

typedef struct {
    FILE *out;
    int tmp_counter;
    int label_counter;
    int str_index;
    sym_t *symtab;
} cg_ctx;

static char *cg_tmp(cg_ctx *c) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%%t%d", c->tmp_counter++);
    return strdup(buf);
}

static void sym_put(cg_ctx *c, const char *name, const char *llname, const char *lltype) {
    sym_t *s = malloc(sizeof(sym_t));
    s->name = strdup(name);
    s->llname = strdup(llname);
    s->lltype = strdup(lltype);
    s->next = c->symtab;
    c->symtab = s;
    lena_logf("codegen: sym_put '%s' -> '%s' (%s)", name, llname, lltype);
}

static sym_t *sym_get(cg_ctx *c, const char *name) {
    for (sym_t *s = c->symtab; s; s = s->next) if (strcmp(s->name, name) == 0) return s;
    return NULL;
}

/* helper: emit global constant label for a C string literal */
static char *emit_global_string(cg_ctx *c, const char *lexeme, size_t *out_len) {
    if (!lexeme || !out_len) return NULL;
    size_t n = strlen(lexeme);
    if (n < 2 || lexeme[0] != '"' || lexeme[n-1] != '"') return NULL;

    unsigned char *bytes = malloc(n);
    if (!bytes) return NULL;
    size_t wi = 0;
    for (size_t i = 1; i + 1 < n; ++i) {
        if (lexeme[i] == '\\' && i + 1 < n - 1) {
            char esc = lexeme[i+1];
            if (esc == 'n') { bytes[wi++] = (unsigned char)'\n'; i++; continue; }
            if (esc == 't') { bytes[wi++] = (unsigned char)'\t'; i++; continue; }
            if (esc == '\\') { bytes[wi++] = (unsigned char)'\\'; i++; continue; }
            if (esc == '"') { bytes[wi++] = (unsigned char)'"'; i++; continue; }
            bytes[wi++] = (unsigned char)lexeme[i+1];
            i++;
            continue;
        }
        bytes[wi++] = (unsigned char)lexeme[i];
    }

    int idx = c->str_index++;
    fprintf(c->out, "@.str%d = private unnamed_addr constant [%zu x i8] c\"", idx, wi + 1);
    for (size_t i = 0; i < wi; ++i) {
        unsigned char uc = bytes[i];
        if (uc >= 32 && uc < 127 && uc != '"' && uc != '\\') {
            fputc((char)uc, c->out);
        } else {
            fprintf(c->out, "\\%02X", uc);
        }
    }
    fputs("\\00\"\n", c->out);

    free(bytes);
    *out_len = wi + 1;
    char *name = malloc(32);
    snprintf(name, 32, "@.str%d", idx);
    return name;
}

static long long parse_int_literal(const char *lex) {
    if (!lex) return 0;
    const char *s = lex;
    int base = 10;
    if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) { base = 2; s += 2; }
    else if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) { base = 16; s += 2; }
    char buf[64]; size_t wi = 0;
    for (size_t i = 0; s[i] && wi + 1 < sizeof(buf); ++i) { if (s[i] == '_') continue; buf[wi++] = s[i]; }
    buf[wi] = '\0';
    return strtoll(buf, NULL, base);
}

static char *cg_emit_expr(cg_ctx *c, ast_node_t *expr);

/* STATEMENTS */
static int cg_emit_stmt(cg_ctx *c, ast_node_t *stmt) {
    if (!stmt) { lena_logf("codegen: cg_emit_stmt called with NULL"); return 0; }
    lena_logf("codegen: cg_emit_stmt kind=%d", stmt->kind);
    switch (stmt->kind) {
        case AST_VAR_DECL: {
            const char *name = stmt->u.vardecl.name;
            const char *type_txt = stmt->u.vardecl.type_name ? stmt->u.vardecl.type_name : "i32";
            const char *llt = map_type(type_txt);
            char *llname = cg_tmp(c); /* e.g. %t0 */
            fprintf(c->out, "  %s = alloca %s\n", llname, llt);
            sym_put(c, name, llname, llt);

            /* special-case initializer for cli::in(...) to allow typed returns */
            if (stmt->u.vardecl.init && stmt->u.vardecl.init->kind == AST_CALL_EXPR) {
                ast_node_t *ce = stmt->u.vardecl.init;
                if (ce->u.call.callee && ce->u.call.callee->kind == AST_IDENTIFIER &&
                    strcmp(ce->u.call.callee->u.ident.name, "cli::in") == 0) {

                    /* We expect a single prompt arg (string literal or expression returning str) */
                    ast_node_t *prompt_arg = (ce->u.call.argc > 0) ? ce->u.call.args[0] : NULL;
                    char *prompt_gep = NULL;
                    size_t plen = 0;
                    if (prompt_arg && prompt_arg->kind == AST_LITERAL && prompt_arg->u.literal.lit_kind == LIT_STRING) {
                        char *gname = emit_global_string(c, prompt_arg->u.literal.value, &plen);
                        if (gname) {
                            char *tmpgep = cg_tmp(c);
                            fprintf(c->out, "  %s = getelementptr inbounds [%zu x i8], [%zu x i8]* %s, i32 0, i32 0\n",
                                    tmpgep, plen, plen, gname);
                            prompt_gep = tmpgep; /* caller must free string returned by cg_tmp */
                        }
                    } else if (prompt_arg) {
                        /* evaluate expression that yields string pointer */
                        prompt_gep = cg_emit_expr(c, prompt_arg);
                        /* not computing length in this branch */
                    }

                    /* if declared type is string slice */
                    if (stmt->u.vardecl.type_name && strcmp(stmt->u.vardecl.type_name, "str") == 0) {
                        /* call: %str_t @lena_cli_in_str(i8* %prompt, i64 %plen) */
                        /* ensure type %str_t exists in module header (done in preamble) */
                        char *calltmp = cg_tmp(c);
                        if (prompt_gep) {
                            fprintf(c->out, "  %s = call %%str_t @lena_cli_in_str(i8* %s, i64 %zu)\n", calltmp, prompt_gep, plen ? plen : 0);
                            /* store aggregate into alloca */
                            fprintf(c->out, "  store %%str_t %s, %%str_t* %s\n", calltmp, llname);
                            free(calltmp);
                            free(prompt_gep);
                        } else {
                            /* no prompt; pass null/0 */
                            fprintf(c->out, "  %s = call %%str_t @lena_cli_in_str(i8* null, i64 0)\n", calltmp);
                            fprintf(c->out, "  store %%str_t %s, %%str_t* %s\n", calltmp, llname);
                            free(calltmp);
                        }
                        return 0;
                    } else {
                        /* numeric case (i32 / i64 ...) - use lena_cli_in_i32 for our example i32 */
                        if (strcmp(llt, "i32") == 0) {
                            char *calltmp = cg_tmp(c);
                            if (prompt_gep) {
                                fprintf(c->out, "  %s = call i32 @lena_cli_in_i32(i8* %s, i64 %zu)\n", calltmp, prompt_gep, plen ? plen : 0);
                                fprintf(c->out, "  store i32 %s, i32* %s\n", calltmp, llname);
                                free(calltmp);
                                free(prompt_gep);
                            } else {
                                fprintf(c->out, "  %s = call i32 @lena_cli_in_i32(i8* null, i64 0)\n", calltmp);
                                fprintf(c->out, "  store i32 %s, i32* %s\n", calltmp, llname);
                                free(calltmp);
                            }
                            return 0;
                        } else if (strcmp(llt, "i64") == 0) {
                            char *calltmp = cg_tmp(c);
                            if (prompt_gep) {
                                fprintf(c->out, "  %s = call i64 @lena_cli_in_i64(i8* %s, i64 %zu)\n", calltmp, prompt_gep, plen ? plen : 0);
                                fprintf(c->out, "  store i64 %s, i64* %s\n", calltmp, llname);
                                free(calltmp);
                                free(prompt_gep);
                            } else {
                                fprintf(c->out, "  %s = call i64 @lena_cli_in_i64(i8* null, i64 0)\n", calltmp);
                                fprintf(c->out, "  store i64 %s, i64* %s\n", calltmp, llname);
                                free(calltmp);
                            }
                            return 0;
                        }
                    }
                }
            }

            /* default path: evaluate initializer via cg_emit_expr */
            if (stmt->u.vardecl.init) {
                char *val = cg_emit_expr(c, stmt->u.vardecl.init);
                fprintf(c->out, "  store %s %s, %s* %s\n", llt, val, llt, llname);
                free(val);
            }
            free(llname);
            return 0;
        }
        case AST_RETURN: {
            if (stmt->u.ret.expr) {
                char *v = cg_emit_expr(c, stmt->u.ret.expr);
                /* assume i32 return for now */
                fprintf(c->out, "  ret i32 %s\n", v);
                free(v);
            } else {
                fprintf(c->out, "  ret void\n");
            }
            return 1; /* emitted terminator */
        }
        case AST_CALL_EXPR: {
            if (stmt->u.call.callee && stmt->u.call.callee->kind == AST_IDENTIFIER)
                lena_logf("codegen: call expression to '%s', argc=%zu", stmt->u.call.callee->u.ident.name, stmt->u.call.argc);
            else
                lena_logf("codegen: call expression to non-identifier callee (kind=%d)", stmt->u.call.callee ? stmt->u.call.callee->kind : -1);
            /* expression-statement call (e.g., cli::out(...)); generate side-effect and return 0 */
            ast_node_t *callee = stmt->u.call.callee;
            if (callee->kind == AST_IDENTIFIER) {
                const char *fname = callee->u.ident.name;
                if (strcmp(fname, "cli::out") == 0 || strcmp(fname, "cli::err") == 0) {
                    /* single-argument expected */
                    if (stmt->u.call.argc > 0) {
                        ast_node_t *a0 = stmt->u.call.args[0];
                        size_t plen = 0;
                        char *gptr = NULL;
                        if (a0->kind == AST_LITERAL && a0->u.literal.lit_kind == LIT_STRING) {
                            char *g = emit_global_string(c, a0->u.literal.value, &plen);
                            if (g) {
                                char *tmpgep = cg_tmp(c);
                                fprintf(c->out, "  %s = getelementptr inbounds [%zu x i8], [%zu x i8]* %s, i32 0, i32 0\n", tmpgep, plen, plen, g);
                                gptr = tmpgep;
                            }
                        } else {
                            gptr = cg_emit_expr(c, a0);
                        }
                        if (gptr) {
                            if (strcmp(fname, "cli::out") == 0)
                                fprintf(c->out, "  call void @lena_cli_out(i8* %s, i64 %zu)\n", gptr, plen ? plen : 0);
                            else
                                fprintf(c->out, "  call void @lena_cli_err(i8* %s, i64 %zu)\n", gptr, plen ? plen : 0);
                            free(gptr);
                        } else {
                            /* no argument pointer, call with null */
                            if (strcmp(fname, "cli::out") == 0) fprintf(c->out, "  call void @lena_cli_out(i8* null, i64 0)\n");
                            else fprintf(c->out, "  call void @lena_cli_err(i8* null, i64 0)\n");
                        }
                    } else {
                        /* no args */
                        if (strcmp(fname, "cli::out") == 0) fprintf(c->out, "  call void @lena_cli_out(i8* null, i64 0)\n");
                        else fprintf(c->out, "  call void @lena_cli_err(i8* null, i64 0)\n");
                    }
                    return 0;
                }
                if (strcmp(fname, "cli::flush") == 0) {
                    /* flush takes stream identifier, e.g., cli::stdout */
                    if (stmt->u.call.argc > 0) {
                        ast_node_t *a0 = stmt->u.call.args[0];
                        /* if identifier cli::stdout or cli::stderr */
                        if (a0->kind == AST_IDENTIFIER &&
                            (strcmp(a0->u.ident.name, "cli::stdout") == 0 || strcmp(a0->u.ident.name, "cli::stderr") == 0)) {
                            const char *which = (strcmp(a0->u.ident.name, "cli::stdout") == 0) ? "1" : "2";
                            fprintf(c->out, "  call void @lena_cli_flush(i32 %s)\n", which);
                            return 0;
                        } else {
                            char *v = cg_emit_expr(c, a0);
                            fprintf(c->out, "  call void @lena_cli_flush(i32 %s)\n", v);
                            free(v);
                            return 0;
                        }
                    } else {
                        fprintf(c->out, "  call void @lena_cli_flush(i32 1)\n");
                        return 0;
                    }
                }
            }
            /* fallback: generic call handling (tries to pass i32 args) */
            {
                if (stmt->u.call.callee->kind == AST_IDENTIFIER) {
                    char *tname = cg_tmp(c);
                    char argbuf[1024]; argbuf[0] = '\0';
                    for (size_t i = 0; i < stmt->u.call.argc; ++i) {
                        char *a = cg_emit_expr(c, stmt->u.call.args[i]);
                        char tmpbuf[128]; snprintf(tmpbuf, sizeof(tmpbuf), "%s %s", "i32", a);
                        if (i) strncat(argbuf, ", ", sizeof(argbuf)-strlen(argbuf)-1);
                        strncat(argbuf, tmpbuf, sizeof(argbuf)-strlen(argbuf)-1);
                        free(a);
                    }
                    fprintf(c->out, "  %s = call i32 @%s(%s)\n", tname, stmt->u.call.callee->u.ident.name, argbuf);
                    return 0;
                }
            }
            return 0;
        }
        default:
            return 0;
    }
}

/* EXPRESSIONS */
static char *cg_emit_expr(cg_ctx *c, ast_node_t *expr) {
    if (!expr) return strdup("0");
    switch (expr->kind) {
        case AST_LITERAL: {
            if (expr->u.literal.lit_kind == LIT_INT) {
                long long v = parse_int_literal(expr->u.literal.value);
                char *buf = malloc(32); snprintf(buf, 32, "%lld", v); return buf;
            }
            if (expr->u.literal.lit_kind == LIT_STRING) {
                size_t len = 0;
                char *gname = emit_global_string(c, expr->u.literal.value, &len);
                if (!gname) return strdup("0");
                char *tmp = cg_tmp(c);
                fprintf(c->out, "  %s = getelementptr inbounds [%zu x i8], [%zu x i8]* %s, i32 0, i32 0\n",
                        tmp, len, len, gname);
                free(gname);
                return tmp;
            }
            if (expr->u.literal.lit_kind == LIT_FLOAT) {
                char *buf = malloc(64);
                snprintf(buf, 64, "%s", expr->u.literal.value);
                return buf;
            }
            if (expr->u.literal.lit_kind == LIT_CHAR) {
                const char *s = expr->u.literal.value;
                if (s && s[0] == '\'') {
                    char ch = s[1];
                    char *buf = malloc(8); snprintf(buf, 8, "%d", (int)ch); return buf;
                }
                return strdup("0");
            }
            break;
        }
        case AST_IDENTIFIER: {
            /* special names: cli::stdout, cli::stderr -> small integer handles */
            if (expr->u.ident.name && strcmp(expr->u.ident.name, "cli::stdout") == 0) return strdup("1");
            if (expr->u.ident.name && strcmp(expr->u.ident.name, "cli::stderr") == 0) return strdup("2");

            sym_t *s = sym_get(c, expr->u.ident.name);
            if (!s) {
                char *r = malloc(strlen(expr->u.ident.name)+2);
                strcpy(r, expr->u.ident.name);
                return r;
            }
            if (s->llname[0] == '%' || s->llname[0] == '@') {
                char *tmp = cg_tmp(c);
                fprintf(c->out, "  %s = load %s, %s* %s\n", tmp, s->lltype, s->lltype, s->llname);
                return tmp;
            } else {
                /* immediate literal (enum value stored as \"0\") -> return it */
                return strdup(s->llname);
            }
        }
        case AST_CALL_EXPR: {
            /* handle cli::in when used in generic expression context (fallback) */
            ast_node_t *callee = expr->u.call.callee;
            if (callee->kind == AST_IDENTIFIER) {
                const char *fname = callee->u.ident.name;
                if (strcmp(fname, "cli::in") == 0) {
                    /* generic fallback: return i32 via lena_cli_in_i32(prompt) */
                    ast_node_t *pa = expr->u.call.argc > 0 ? expr->u.call.args[0] : NULL;
                    size_t plen = 0;
                    char *gptr = NULL;
                    if (pa && pa->kind == AST_LITERAL && pa->u.literal.lit_kind == LIT_STRING) {
                        char *g = emit_global_string(c, pa->u.literal.value, &plen);
                        if (g) {
                            char *tmpgep = cg_tmp(c);
                            fprintf(c->out, "  %s = getelementptr inbounds [%zu x i8], [%zu x i8]* %s, i32 0, i32 0\n",
                                    tmpgep, plen, plen, g);
                            gptr = tmpgep;
                        }
                    } else if (pa) {
                        gptr = cg_emit_expr(c, pa);
                    }
                    char *calltmp = cg_tmp(c);
                    if (gptr) {
                        fprintf(c->out, "  %s = call i32 @lena_cli_in_i32(i8* %s, i64 %zu)\n", calltmp, gptr, plen ? plen : 0);
                        free(gptr);
                    } else {
                        fprintf(c->out, "  %s = call i32 @lena_cli_in_i32(i8* null, i64 0)\n", calltmp);
                    }
                    return calltmp;
                }
            }
            /* fallback to calling generic function expecting i32 args */
            if (callee->kind == AST_IDENTIFIER) {
                char *tname = cg_tmp(c);
                char argbuf[1024]; argbuf[0] = '\0';
                for (size_t i = 0; i < expr->u.call.argc; ++i) {
                    char *a = cg_emit_expr(c, expr->u.call.args[i]);
                    char tmpbuf[128]; snprintf(tmpbuf, sizeof(tmpbuf), "%s %s", "i32", a);
                    if (i) strncat(argbuf, ", ", sizeof(argbuf)-strlen(argbuf)-1);
                    strncat(argbuf, tmpbuf, sizeof(argbuf)-strlen(argbuf)-1);
                    free(a);
                }
                fprintf(c->out, "  %s = call i32 @%s(%s)\n", tname, callee->u.ident.name, argbuf);
                return tname;
            }
            break;
        }
        case AST_BINARY_EXPR: {
            char *l = cg_emit_expr(c, expr->u.binary.left);
            char *r = cg_emit_expr(c, expr->u.binary.right);
            char *res = cg_tmp(c);
            const char *op = expr->u.binary.op;
            if (strcmp(op, "+") == 0) fprintf(c->out, "  %s = add i32 %s, %s\n", res, l, r);
            else if (strcmp(op, "-") == 0) fprintf(c->out, "  %s = sub i32 %s, %s\n", res, l, r);
            else if (strcmp(op, "*") == 0) fprintf(c->out, "  %s = mul i32 %s, %s\n", res, l, r);
            else if (strcmp(op, "/") == 0) fprintf(c->out, "  %s = sdiv i32 %s, %s\n", res, l, r);
            else if (strcmp(op, "==") == 0) {
                fprintf(c->out, "  %s = icmp eq i32 %s, %s\n", res, l, r);
                char *ext = cg_tmp(c);
                fprintf(c->out, "  %s = zext i1 %s to i32\n", ext, res);
                free(res); res = ext;
            } else {
                fprintf(c->out, "  %s = add i32 %s, %s\n", res, l, r);
            }
            free(l); free(r);
            return res;
        }
        default:
            break;
    }
    return strdup("0");
}

/* MODULE EMISSION */
int codegen_emit_module(ast_node_t *root, const char *out_path) {
    if (!root) return -1;

    FILE *f = fopen(out_path, "w");
    if (!f) return -1;

    cg_ctx ctx = {
        .out = f,
        .tmp_counter = 0,
        .label_counter = 0,
        .str_index = 0,
        .symtab = NULL
    };

    fprintf(f, "; Lena generated LLVM IR\n\n");

    /* declare our runtime helpers and string type */
    fprintf(f, "%%str_t = type { i8*, i64 }\n\n");
    fprintf(f, "declare void @lena_cli_out(i8*, i64)\n");
    fprintf(f, "declare void @lena_cli_err(i8*, i64)\n");
    fprintf(f, "declare %%str_t @lena_cli_in_str(i8*, i64)\n");
    fprintf(f, "declare i32 @lena_cli_in_i32(i8*, i64)\n");
    fprintf(f, "declare i64 @lena_cli_in_i64(i8*, i64)\n");
    fprintf(f, "declare void @lena_cli_flush(i32)\n");
    fprintf(f, "declare i32 @printf(i8*, ...)\n\n");



    /* prepass: register top-level enums and nested inline enums within structs (unchanged) */
    for (size_t i = 0; i < root->u.block.stmtc; ++i) {
        ast_node_t *st = root->u.block.stmts[i];
        if (st->kind == AST_ENUM_DECL) {
            const char *ename = st->u.enum_decl.name;
            for (size_t mi = 0; mi < st->u.enum_decl.memberc; ++mi) {
                char valbuf[32]; snprintf(valbuf, sizeof(valbuf), "%zu", mi);
                const char *member = st->u.enum_decl.members[mi];
                sym_put(&ctx, member, valbuf, "i32");
                if (ename) { char fullname[256]; snprintf(fullname, sizeof(fullname), "%s::%s", ename, member); sym_put(&ctx, fullname, valbuf, "i32"); }
                char gname[256]; snprintf(gname, sizeof(gname), "::%s", member); sym_put(&ctx, gname, valbuf, "i32");
            }
            fprintf(f, "; enum %s {", ename ? ename : "(anon)");
            for (size_t mi=0; mi<st->u.enum_decl.memberc;++mi) { if (mi) fputs(", ", f); fprintf(f, "%s=%zu", st->u.enum_decl.members[mi], mi); }
            fprintf(f, " }\n");
        } else if (st->kind == AST_STRUCT_DECL) {
            const char *struct_name = st->u.struct_decl.name ? st->u.struct_decl.name : "(anon)";
            for (size_t fi = 0; fi < st->u.struct_decl.fieldc; ++fi) {
                ast_field_t *fld = st->u.struct_decl.fields[fi];
                if (fld->inline_type && fld->inline_type->kind == AST_ENUM_DECL) {
                    ast_node_t *ed = fld->inline_type;
                    for (size_t mi = 0; mi < ed->u.enum_decl.memberc; ++mi) {
                        char valbuf[32]; snprintf(valbuf, sizeof(valbuf), "%zu", mi);
                        const char *member = ed->u.enum_decl.members[mi];
                        char qn[256]; snprintf(qn, sizeof(qn), "%s::%s::%s", struct_name, fld->name, member);
                        sym_put(&ctx, qn, valbuf, "i32");
                        sym_put(&ctx, member, valbuf, "i32");
                        char gname[64]; snprintf(gname, sizeof(gname), "::%s", member); sym_put(&ctx, gname, valbuf, "i32");
                    }
                    fprintf(f, "; inline enum for %s.%s\n", struct_name, fld->name);
                }
            }
        }
    }


    /* emit functions */
    for (size_t i = 0; i < root->u.block.stmtc; ++i) {
        ast_node_t *st = root->u.block.stmts[i];

        if (st->kind == AST_FUNC_DECL) {

            const char *fname = st->u.func.name;
            const char *ret = map_type(st->u.func.ret_type);

            char params_buf[512];
            params_buf[0] = '\0';

            for (size_t pi = 0; pi < st->u.func.paramc; ++pi) {
                if (pi)
                    strncat(params_buf, ", ", sizeof(params_buf)-strlen(params_buf)-1);

                strncat(params_buf, "i32 %", sizeof(params_buf)-strlen(params_buf)-1);

                char ptmp[64];
                snprintf(ptmp, sizeof(ptmp), "p%zu", pi);

                strncat(params_buf, ptmp, sizeof(params_buf)-strlen(params_buf)-1);
            }

            fprintf(f, "define %s @%s(%s) {\n", ret, fname, params_buf);

            ctx.tmp_counter = 0;
            ctx.label_counter = 0;

            int has_return = 0;

            ast_node_t *body = st->u.func.body;
            lena_logf("codegen: emitting function %s, body stmt count = %zu", fname, body ? body->u.block.stmtc : 0);
            if (body && body->kind == AST_BLOCK) {
                for (size_t si = 0; si < body->u.block.stmtc; ++si) {

                    ast_node_t *stmt = body->u.block.stmts[si];

                    if (stmt->kind == AST_RETURN)
                        has_return = 1;

                    cg_emit_stmt(&ctx, stmt);
                }
            }

            if (!has_return) {
                if (strcmp(ret, "void") == 0)
                    fprintf(f, "  ret void\n");
                else
                    fprintf(f, "  ret i32 0\n");
            }

            fprintf(f, "}\n\n");
            lena_logf("codegen: emitted function %s", fname);
        }
    }

    fclose(f);
    return 0;
}
