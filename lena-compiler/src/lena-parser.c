/*
  file: lena_parser.c
  author: Matvey Rybalkin
  date: 08 March 2026
  brief: Recursive-descent parser for Lena language producing AST (version 0.2.1).
  version: 0.2.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lena-ast.h"
#include "lena-tokenizer.h"
#include "lena-util.h"

/* parser state */
typedef struct { token_list_t *tokens; size_t pos; } parser_t;

static token_t *peek_tok(parser_t *p) { if (p->pos < p->tokens->len) return &p->tokens->data[p->pos]; return NULL; }
static token_t *nth_tok(parser_t *p, size_t n) { if (p->pos + n < p->tokens->len) return &p->tokens->data[p->pos + n]; return NULL; }
static token_t *advance(parser_t *p) { token_t *t = peek_tok(p); if (t) p->pos++; return t; }
static int match_tok(parser_t *p, token_type type, const char *lex) { token_t *t = peek_tok(p); if (!t) return 0; if (t->type != type) return 0; if (lex && strcmp(t->lexeme, lex) != 0) return 0; advance(p); return 1; }
static int check_tok(parser_t *p, token_type type, const char *lex) { token_t *t = peek_tok(p); if (!t) return 0; if (t->type != type) return 0; if (lex && strcmp(t->lexeme, lex) != 0) return 0; return 1; }

/* allocate node */
static ast_node_t *ast_alloc(ast_node_type kind) { ast_node_t *n = calloc(1, sizeof(ast_node_t)); n->kind = kind; return n; }

/* forward declarations */
static ast_node_t *parse_expression(parser_t *p, int min_prec);
static ast_node_t *parse_struct_inline(parser_t *p);
static ast_node_t *parse_struct_literal(parser_t *p);
static ast_node_t *parse_func_decl(parser_t *p); /* existing, kept for compatibility */
static ast_node_t *parse_func_decl_strict(parser_t *p); /* new strict variant */

/* parse qualified name */
static char *parse_qualified_name(parser_t *p) {
    size_t cap = 64; char *buf = malloc(cap); buf[0] = '\0';
    token_t *t = peek_tok(p);
    if (t && t->type == TOK_OPERATOR && strcmp(t->lexeme, "::") == 0) {
        if (strlen(buf) + 3 > cap) { cap *= 2; buf = realloc(buf, cap); }
        strcat(buf, "::");
        advance(p);
        t = peek_tok(p);
    }
    int first = 1;
    while (t && t->type == TOK_IDENTIFIER) {
        size_t need = strlen(buf) + (first ? 0 : 2) + strlen(t->lexeme) + 1;
        if (need > cap) { while (need > cap) cap *= 2; buf = realloc(buf, cap); }
        if (!first && buf[strlen(buf)-1] != ':') strcat(buf, "::");
        strcat(buf, t->lexeme);
        first = 0;
        advance(p);
        token_t *next = peek_tok(p);
        if (!next || next->type != TOK_OPERATOR || strcmp(next->lexeme, "::") != 0) break;
        advance(p);
        t = peek_tok(p);
    }
    return buf;
}

/* parse enum declaration (supports anonymous inline enum and top-level) */
static ast_node_t *parse_enum_decl(parser_t *p) {
    if (!check_tok(p, TOK_KEYWORD, "enum")) return NULL;
    lena_logf("parser: parsing enum at pos %zu", p->pos);
    advance(p); /* enum */
    if (!match_tok(p, TOK_PUNCT, "{")) return NULL;
    ast_node_t *n = ast_alloc(AST_ENUM_DECL);
    n->u.enum_decl.name = NULL;
    n->u.enum_decl.members = NULL;
    n->u.enum_decl.memberc = 0;
    while (!check_tok(p, TOK_PUNCT, "}")) {
        token_t *t = peek_tok(p);
        if (!t || t->type != TOK_IDENTIFIER) break;
        n->u.enum_decl.members = realloc(n->u.enum_decl.members, sizeof(char*) * (n->u.enum_decl.memberc + 1));
        n->u.enum_decl.members[n->u.enum_decl.memberc++] = strdup(t->lexeme);
        advance(p);
        if (check_tok(p, TOK_PUNCT, "}")) break;
        match_tok(p, TOK_PUNCT, ",");
    }
    match_tok(p, TOK_PUNCT, "}");
    lena_logf("parser: enum parsed with %zu members", n->u.enum_decl.memberc);
    return n;
}

/* parse a field inside struct (name[:type] = (expr | inline enum | inline struct) ) */
static ast_field_t *parse_field(parser_t *p) {
    token_t *t = peek_tok(p);
    if (!t || t->type != TOK_IDENTIFIER) return NULL;
    ast_field_t *f = calloc(1, sizeof(ast_field_t));
    f->name = strdup(t->lexeme);
    advance(p);
    if (match_tok(p, TOK_PUNCT, ":")) {
        token_t *tn = peek_tok(p);
        if (tn && (tn->type == TOK_IDENTIFIER || tn->type == TOK_KEYWORD)) { f->type_name = strdup(tn->lexeme); advance(p); }
    }
    if (match_tok(p, TOK_OPERATOR, "=") || match_tok(p, TOK_PUNCT, "=")) {
        token_t *nxt = peek_tok(p);
        if (nxt && nxt->type == TOK_KEYWORD && strcmp(nxt->lexeme, "enum") == 0) {
            f->inline_type = parse_enum_decl(p);
            f->default_value = NULL;
        } else if (nxt && nxt->type == TOK_KEYWORD && strcmp(nxt->lexeme, "struct") == 0) {
            advance(p); /* struct */
            f->inline_type = parse_struct_inline(p);
            f->default_value = NULL;
        } else {
            if (check_tok(p, TOK_PUNCT, "{")) {
                f->default_value = parse_struct_literal(p);
            } else {
                f->default_value = parse_expression(p, 0);
            }
        }
    }
    return f;
}

/* parse struct inline body: assumes 'struct' already consumed */
static ast_node_t *parse_struct_inline(parser_t *p) {
    if (!match_tok(p, TOK_PUNCT, "{")) return NULL;
    ast_node_t *n = ast_alloc(AST_STRUCT_DECL);
    n->u.struct_decl.name = NULL;
    n->u.struct_decl.fields = NULL;
    n->u.struct_decl.fieldc = 0;
    while (!check_tok(p, TOK_PUNCT, "}")) {
        ast_field_t *f = parse_field(p);
        if (!f) break;
        n->u.struct_decl.fields = realloc(n->u.struct_decl.fields, sizeof(ast_field_t*) * (n->u.struct_decl.fieldc + 1));
        n->u.struct_decl.fields[n->u.struct_decl.fieldc++] = f;
        if (check_tok(p, TOK_PUNCT, "}")) break;
        match_tok(p, TOK_PUNCT, ",");
    }
    match_tok(p, TOK_PUNCT, "}");
    lena_logf("parser: parsed inline struct with %zu fields", n->u.struct_decl.fieldc);
    return n;
}

/* parse struct literal (value) — { .field = expr, ... } */
static ast_node_t *parse_struct_literal(parser_t *p) {
    if (!match_tok(p, TOK_PUNCT, "{")) return NULL;
    ast_node_t *n = ast_alloc(AST_STRUCT_LITERAL);
    n->u.struct_lit.fields = NULL;
    n->u.struct_lit.fieldc = 0;
    while (!check_tok(p, TOK_PUNCT, "}")) {
        /* allow optional "." before field name */
        if (check_tok(p, TOK_PUNCT, ".")) advance(p);
        token_t *fn = peek_tok(p);
        if (!fn || fn->type != TOK_IDENTIFIER) break;
        ast_field_t *f = calloc(1, sizeof(ast_field_t));
        f->name = strdup(fn->lexeme);
        advance(p);
        match_tok(p, TOK_OPERATOR, "=");
        f->default_value = parse_expression(p, 0);
        n->u.struct_lit.fields = realloc(n->u.struct_lit.fields, sizeof(ast_field_t*) * (n->u.struct_lit.fieldc + 1));
        n->u.struct_lit.fields[n->u.struct_lit.fieldc++] = f;
        if (check_tok(p, TOK_PUNCT, "}")) break;
        match_tok(p, TOK_PUNCT, ",");
    }
    match_tok(p, TOK_PUNCT, "}");
    return n;
}

/* parse primary */
static ast_node_t *parse_primary(parser_t *p) {
    token_t *t = peek_tok(p);
    if (!t) return NULL;
    if (t->type == TOK_NUMBER_INT || t->type == TOK_NUMBER_FLOAT || t->type == TOK_STRING || t->type == TOK_CHAR) {
        ast_node_t *n = ast_alloc(AST_LITERAL);
        ast_literal_t *lit = &n->u.literal;
        lit->base.line = t->line; lit->base.column = t->column;
        lit->value = strdup(t->lexeme);
        if (t->type == TOK_NUMBER_INT) lit->lit_kind = LIT_INT;
        else if (t->type == TOK_NUMBER_FLOAT) lit->lit_kind = LIT_FLOAT;
        else if (t->type == TOK_STRING) lit->lit_kind = LIT_STRING;
        else lit->lit_kind = LIT_CHAR;
        advance(p);
        return n;
    }
    if (t->type == TOK_IDENTIFIER) {
        char *qname = parse_qualified_name(p);
        if (check_tok(p, TOK_PUNCT, "(") ) {
            advance(p);
            ast_node_t *call = ast_alloc(AST_CALL_EXPR);
            ast_call_t *c = &call->u.call;
            c->base.line = t->line; c->base.column = t->column;
            ast_node_t *callee = ast_alloc(AST_IDENTIFIER);
            callee->u.ident.base.line = t->line; callee->u.ident.base.column = t->column;
            callee->u.ident.name = qname;
            c->callee = callee;
            c->argc = 0; c->args = NULL;
            if (!check_tok(p, TOK_PUNCT, ")")) {
                while (1) {
                    ast_node_t *arg = parse_expression(p, 0);
                    if (!arg) break;
                    c->args = realloc(c->args, sizeof(ast_node_t*) * (c->argc + 1));
                    c->args[c->argc++] = arg;
                    if (check_tok(p, TOK_PUNCT, ")")) break;
                    match_tok(p, TOK_PUNCT, ",");
                }
            }
            match_tok(p, TOK_PUNCT, ")");
            return call;
        } else {
            ast_node_t *idn = ast_alloc(AST_IDENTIFIER);
            idn->u.ident.base.line = t->line; idn->u.ident.base.column = t->column;
            idn->u.ident.name = qname;
            return idn;
        }
    }
    if (check_tok(p, TOK_PUNCT, "(")) {
        advance(p);
        ast_node_t *e = parse_expression(p, 0);
        match_tok(p, TOK_PUNCT, ")");
        return e;
    }
    if (check_tok(p, TOK_PUNCT, "{")) {
        return parse_struct_literal(p);
    }
    return NULL;
}

/* precedence climbing */
static int get_prec(const char *op) {
    if (!op) return -1;
    if (strcmp(op, "or") == 0) return 1;
    if (strcmp(op, "and") == 0) return 2;
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) return 3;
    if (strcmp(op, "<") == 0 || strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) return 4;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 5;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) return 6;
    if (strcmp(op, "on") == 0) return 4; /* membership operator */
    return -1;
}

static ast_node_t *parse_expression(parser_t *p, int min_prec) {
    ast_node_t *lhs = NULL;
    token_t *t = peek_tok(p);
    if (!t) return NULL;
    if (t->type == TOK_PUNCT && (strcmp(t->lexeme, "-") == 0 || strcmp(t->lexeme, "~") == 0) ) {
        advance(p);
        ast_node_t *operand = parse_expression(p, 6);
        ast_node_t *un = ast_alloc(AST_UNARY_EXPR);
        un->u.unary.base.line = t->line; un->u.unary.base.column = t->column;
        un->u.unary.op = strdup(t->lexeme);
        un->u.unary.operand = operand;
        lhs = un;
    } else {
        lhs = parse_primary(p);
    }
    while (1) {
        token_t *op_tok = peek_tok(p);
        if (!op_tok) break;
        const char *op_lex = NULL;
        if (op_tok->type == TOK_OPERATOR || op_tok->type == TOK_PUNCT) op_lex = op_tok->lexeme;
        else if (op_tok->type == TOK_KEYWORD && (strcmp(op_tok->lexeme, "and") == 0 || strcmp(op_tok->lexeme, "or") == 0 || strcmp(op_tok->lexeme, "on") == 0)) op_lex = op_tok->lexeme;
        else break;
        int prec = get_prec(op_lex);
        if (prec < 0 || prec < min_prec) break;
        advance(p);
        int next_min = prec + 1;
        ast_node_t *rhs = parse_expression(p, next_min);
        ast_node_t *bin = ast_alloc(AST_BINARY_EXPR);
        bin->u.binary.base.line = op_tok->line; bin->u.binary.base.column = op_tok->column;
        bin->u.binary.op = strdup(op_lex);
        bin->u.binary.left = lhs;
        bin->u.binary.right = rhs;
        lhs = bin;
    }
    return lhs;
}

/* statements */
static ast_node_t *parse_statement(parser_t *p);

static ast_node_t *parse_block(parser_t *p) {
    if (!match_tok(p, TOK_PUNCT, "{")) return NULL;
    ast_node_t *blk = ast_alloc(AST_BLOCK);
    ast_block_t *b = &blk->u.block;
    b->base.line = 0; b->base.column = 0;
    b->stmts = NULL; b->stmtc = 0;
    while (!check_tok(p, TOK_PUNCT, "}")) {
        /* skip blank lines and comments inside blocks */
        if (check_tok(p, TOK_NEWLINE, "\n") || check_tok(p, TOK_COMMENT, "#")) { advance(p); continue; }
        if (check_tok(p, TOK_EOF, "<eof>")) break;
        ast_node_t *st = parse_statement(p);
        if (!st) {
            token_t *tk = peek_tok(p);
            if (!tk) break;
            lena_logf("parser: warning — failed to parse statement at token '%s' (type=%d), skipping", tk->lexeme ? tk->lexeme : "(nil)", tk->type);
            advance(p);
            continue;
        }
        b->stmts = realloc(b->stmts, sizeof(ast_node_t*) * (b->stmtc + 1));
        b->stmts[b->stmtc++] = st;
    }
    match_tok(p, TOK_PUNCT, "}");
    lena_logf("parser: parsed block at pos %zu with %zu stmts", p->pos, b->stmtc);
    return blk;
}

static ast_node_t *parse_var_decl(parser_t *p) {
    token_t *t = peek_tok(p);
    if (!t || t->type != TOK_IDENTIFIER) return NULL;
    ast_node_t *n = ast_alloc(AST_VAR_DECL);
    n->u.vardecl.base.line = t->line; n->u.vardecl.base.column = t->column;
    n->u.vardecl.name = strdup(t->lexeme);
    advance(p);
    n->u.vardecl.type_name = NULL;

    if (match_tok(p, TOK_PUNCT, ":")) {
        token_t *type_t = peek_tok(p);
        if (type_t && (type_t->type == TOK_IDENTIFIER || type_t->type == TOK_KEYWORD)) {
            n->u.vardecl.type_name = strdup(type_t->lexeme);
            advance(p);
            if (check_tok(p, TOK_PUNCT, "[")) {
                advance(p);
                match_tok(p, TOK_PUNCT, "]");
                size_t L = strlen(n->u.vardecl.type_name) + 3;
                n->u.vardecl.type_name = realloc(n->u.vardecl.type_name, L);
                strcat(n->u.vardecl.type_name, "[]");
            }
        }
    }

    if (match_tok(p, TOK_OPERATOR, "=") || match_tok(p, TOK_PUNCT, "=")) {
        /* support struct literal here */
        if (check_tok(p, TOK_PUNCT, "{")) {
            n->u.vardecl.init = parse_struct_literal(p);
        } else {
            n->u.vardecl.init = parse_expression(p, 0);
        }

        /* optional initializer type annotation: ':typename' after the expression */
        if (match_tok(p, TOK_PUNCT, ":")) {
            token_t *tt = peek_tok(p);
            if (tt && (tt->type == TOK_IDENTIFIER || tt->type == TOK_KEYWORD)) {
                /* consume and ignore for now */
                advance(p);
                if (check_tok(p, TOK_PUNCT, "[")) { advance(p); match_tok(p, TOK_PUNCT, "]"); }
            }
        }
    } else {
        n->u.vardecl.init = NULL;
    }

    /* accept either semicolon or newline as statement terminator */
    if (!match_tok(p, TOK_PUNCT, ";")) match_tok(p, TOK_NEWLINE, "\n");
    return n;
}

static ast_node_t *parse_return(parser_t *p) {
    token_t *t = advance(p);
    ast_node_t *n = ast_alloc(AST_RETURN);
    n->u.ret.base.line = t->line; n->u.ret.base.column = t->column;
    n->u.ret.expr = NULL;
    if (!check_tok(p, TOK_PUNCT, ";") && !check_tok(p, TOK_NEWLINE, "\n")) {
        n->u.ret.expr = parse_expression(p, 0);
    }
    if (!match_tok(p, TOK_PUNCT, ";")) match_tok(p, TOK_NEWLINE, "\n");
    return n;
}

static ast_node_t *parse_statement(parser_t *p) {
    token_t *t = peek_tok(p);
    if (!t) return NULL;
    /* skip leading newlines/comments for safety */
    if (check_tok(p, TOK_NEWLINE, "\n") || check_tok(p, TOK_COMMENT, "#")) { advance(p); return NULL; }

    if (t->type == TOK_KEYWORD && strcmp(t->lexeme, "let") == 0) {
        advance(p);
        token_t *n1 = peek_tok(p);
        token_t *n2 = nth_tok(p, 1);
        if (n1 && n1->type == TOK_IDENTIFIER && n2 && (n2->type == TOK_OPERATOR || n2->type == TOK_PUNCT) && strcmp(n2->lexeme, "=") == 0) {
            char *namecopy = strdup(n1->lexeme);
            advance(p); /* consume name */
            match_tok(p, TOK_OPERATOR, "=");
            if (check_tok(p, TOK_KEYWORD, "struct")) {
                advance(p);
                ast_node_t *s = parse_struct_inline(p);
                if (s && s->kind == AST_STRUCT_DECL) {
                    free(s->u.struct_decl.name);
                    s->u.struct_decl.name = namecopy;
                    return s;
                }
                free(namecopy);
            } else if (check_tok(p, TOK_KEYWORD, "enum")) {
                ast_node_t *e = parse_enum_decl(p);
                if (e && e->kind == AST_ENUM_DECL) {
                    e->u.enum_decl.name = namecopy;
                    return e;
                }
                free(namecopy);
            } else {
                /* fallback to var decl created manually */
                ast_node_t *vd = ast_alloc(AST_VAR_DECL);
                vd->u.vardecl.name = namecopy;
                vd->u.vardecl.type_name = NULL;
                vd->u.vardecl.init = parse_expression(p, 0);

                /* consume optional ':type' after initializer */
                if (match_tok(p, TOK_PUNCT, ":")) {
                    token_t *tt = peek_tok(p);
                    if (tt && (tt->type == TOK_IDENTIFIER || tt->type == TOK_KEYWORD)) {
                        vd->u.vardecl.type_name = strdup(tt->lexeme);
                        advance(p);
                        if (check_tok(p, TOK_PUNCT, "[")) { advance(p); match_tok(p, TOK_PUNCT, "]"); size_t L = strlen(vd->u.vardecl.type_name) + 3; vd->u.vardecl.type_name = realloc(vd->u.vardecl.type_name, L); strcat(vd->u.vardecl.type_name, "[]"); }
                    }
                }

                if (!match_tok(p, TOK_PUNCT, ";")) match_tok(p, TOK_NEWLINE, "\n");
                return vd;
            }
        } else {
            return parse_var_decl(p);
        }
    }

    if (t->type == TOK_KEYWORD && strcmp(t->lexeme, "return") == 0) {
        return parse_return(p);
    }
    if (t->type == TOK_PUNCT && strcmp(t->lexeme, "{") == 0) {
        return parse_block(p);
    }
    ast_node_t *e = parse_expression(p, 0);
    /* accept semicolon or newline as terminator */
    if (!match_tok(p, TOK_PUNCT, ";")) match_tok(p, TOK_NEWLINE, "\n");
    return e;
}

/* existing non-strict parse_func_decl (kept for compatibility) */
static ast_node_t *parse_func_decl(parser_t *p) {
    token_t *t = peek_tok(p);
    if (!t || t->type != TOK_IDENTIFIER) return NULL;
    ast_node_t *f = ast_alloc(AST_FUNC_DECL);
    ast_func_decl_t *fd = &f->u.func;
    fd->base.line = t->line; fd->base.column = t->column;
    fd->name = strdup(t->lexeme);
    advance(p);
    fd->params = NULL; fd->paramc = 0;
    match_tok(p, TOK_PUNCT, "(");
    if (!check_tok(p, TOK_PUNCT, ")")) {
        while (1) {
            token_t *pn = peek_tok(p);
            if (!pn || pn->type != TOK_IDENTIFIER) break;
            char buf[256] = {0};
            strncpy(buf, pn->lexeme, sizeof(buf)-1);
            advance(p);
            if (match_tok(p, TOK_PUNCT, ":")) {
                token_t *tt = peek_tok(p);
                if (tt) { strncat(buf, ":", sizeof(buf)-strlen(buf)-1); strncat(buf, tt->lexeme, sizeof(buf)-strlen(buf)-1); advance(p); }
            }
            fd->params = realloc(fd->params, sizeof(char*) * (fd->paramc + 1));
            fd->params[fd->paramc++] = strdup(buf);
            if (check_tok(p, TOK_PUNCT, ")")) break;
            match_tok(p, TOK_PUNCT, ",");
        }
    }
    match_tok(p, TOK_PUNCT, ")");
    fd->ret_type = NULL;
    if (match_tok(p, TOK_PUNCT, ":")) {
        token_t *rt = peek_tok(p);
        if (rt && (rt->type == TOK_IDENTIFIER || rt->type == TOK_KEYWORD)) { fd->ret_type = strdup(rt->lexeme); advance(p); }
    }
    fd->body = parse_block(p);
    return f;
}

/* strict function header+body parser: always consumes body or rolls back */
static ast_node_t *parse_func_decl_strict(parser_t *p) {
    size_t start_pos = p->pos;
    token_t *t = peek_tok(p);
    if (!t || t->type != TOK_IDENTIFIER) return NULL;

    /* parse name */
    char *name = strdup(t->lexeme);
    advance(p);

    /* parse params */
    if (!match_tok(p, TOK_PUNCT, "(")) { free(name); p->pos = start_pos; return NULL; }
    char **params = NULL; size_t paramc = 0;
    if (!check_tok(p, TOK_PUNCT, ")")) {
        while (1) {
            token_t *pn = peek_tok(p);
            if (!pn || pn->type != TOK_IDENTIFIER) break;
            char buf[256] = {0};
            strncpy(buf, pn->lexeme, sizeof(buf)-1);
            advance(p);
            if (match_tok(p, TOK_PUNCT, ":")) {
                token_t *tt = peek_tok(p);
                if (tt) { strncat(buf, ":", sizeof(buf)-strlen(buf)-1); strncat(buf, tt->lexeme, sizeof(buf)-strlen(buf)-1); advance(p); }
            }
            params = realloc(params, sizeof(char*) * (paramc + 1));
            params[paramc++] = strdup(buf);
            if (check_tok(p, TOK_PUNCT, ")")) break;
            if (!match_tok(p, TOK_PUNCT, ",")) break;
        }
    }
    match_tok(p, TOK_PUNCT, ")");

    /* optional return type */
    char *ret_type = NULL;
    if (match_tok(p, TOK_PUNCT, ":")) {
        token_t *rt = peek_tok(p);
        if (rt && (rt->type == TOK_IDENTIFIER || rt->type == TOK_KEYWORD)) { ret_type = strdup(rt->lexeme); advance(p); }
    }

    /* body is required for strict parse: must be a block */
    if (!check_tok(p, TOK_PUNCT, "{")) {
        /* rollback and fail */
        for (size_t i = 0; i < paramc; ++i) free(params[i]);
        free(params);
        free(name);
        if (ret_type) free(ret_type);
        p->pos = start_pos;
        return NULL;
    }

    ast_node_t *body = parse_block(p);
    if (!body) {
        /* rollback on failure */
        for (size_t i = 0; i < paramc; ++i) free(params[i]);
        free(params);
        free(name);
        if (ret_type) free(ret_type);
        p->pos = start_pos;
        return NULL;
    }

    /* build function node */
    ast_node_t *f = ast_alloc(AST_FUNC_DECL);
    ast_func_decl_t *fd = &f->u.func;
    fd->base.line = 0; fd->base.column = 0;
    fd->name = name;
    fd->params = params;
    fd->paramc = paramc;
    fd->ret_type = ret_type;
    fd->body = body;
    return f;
}

ast_node_t *parse_program(token_list_t *tokens) {
    parser_t pstate = { .tokens = tokens, .pos = 0 };
    ast_node_t *root = ast_alloc(AST_PROGRAM);
    ast_block_t *prog = &root->u.block;
    prog->stmts = NULL; prog->stmtc = 0;
    while (!check_tok(&pstate, TOK_EOF, "<eof>")) {
        if (check_tok(&pstate, TOK_NEWLINE, "\n") || check_tok(&pstate, TOK_COMMENT, "#")) { advance(&pstate); continue; }
        token_t *t = peek_tok(&pstate);
        if (!t) break;

        /* function detection: ident + '(' => try strict parse (ensures body attached) */
        if (t->type == TOK_IDENTIFIER) {
            token_t *n1 = nth_tok(&pstate, 1);
            if (n1 && n1->type == TOK_PUNCT && strcmp(n1->lexeme, "(") == 0) {
                ast_node_t *fn = parse_func_decl_strict(&pstate);
                if (fn) {
                    prog->stmts = realloc(prog->stmts, sizeof(ast_node_t*) * (prog->stmtc + 1));
                    prog->stmts[prog->stmtc++] = fn;
                    continue;
                }
                /* fallback: try non-strict parse (older behavior) */
                fn = parse_func_decl(&pstate);
                if (fn) {
                    /* defensive attach if next token is a block */
                    if (fn->kind == AST_FUNC_DECL && fn->u.func.body == NULL && check_tok(&pstate, TOK_PUNCT, "{")) {
                        lena_logf("parser: attaching block to function %s after parse_func_decl (fallback)", fn->u.func.name ? fn->u.func.name : "(nil)");
                        fn->u.func.body = parse_block(&pstate);
                    }
                    prog->stmts = realloc(prog->stmts, sizeof(ast_node_t*) * (prog->stmtc + 1));
                    prog->stmts[prog->stmtc++] = fn;
                    continue;
                }
            }
        }

        /* try top-level let with struct/enum */
        if (t->type == TOK_KEYWORD && strcmp(t->lexeme, "let") == 0) {
            ast_node_t *st = parse_statement(&pstate);
            if (st) { prog->stmts = realloc(prog->stmts, sizeof(ast_node_t*) * (prog->stmtc + 1)); prog->stmts[prog->stmtc++] = st; continue; }
        }

        ast_node_t *st = parse_statement(&pstate);
        if (st) {
            prog->stmts = realloc(prog->stmts, sizeof(ast_node_t*) * (prog->stmtc + 1));
            prog->stmts[prog->stmtc++] = st;
            continue;
        }

        advance(&pstate);
    }
    lena_logf("parser: finished, program has %zu top-level stmts", prog->stmtc);
    return root;
}

/* free_node — extend to handle new nodes */
static void free_node(ast_node_t *n) {
    if (!n) return;
    switch (n->kind) {
        case AST_LITERAL:
            free(n->u.literal.value);
            break;
        case AST_IDENTIFIER:
            free(n->u.ident.name);
            break;
        case AST_CALL_EXPR:
            free_node(n->u.call.callee);
            for (size_t i=0;i<n->u.call.argc;++i) free_node(n->u.call.args[i]);
            free(n->u.call.args);
            break;
        case AST_BINARY_EXPR:
            free(n->u.binary.op);
            free_node(n->u.binary.left);
            free_node(n->u.binary.right);
            break;
        case AST_UNARY_EXPR:
            free(n->u.unary.op);
            free_node(n->u.unary.operand);
            break;
        case AST_VAR_DECL:
            free(n->u.vardecl.name); free(n->u.vardecl.type_name); free_node(n->u.vardecl.init);
            break;
        case AST_FUNC_DECL:
            free(n->u.func.name); free(n->u.func.ret_type);
            for (size_t i=0;i<n->u.func.paramc;++i) free(n->u.func.params[i]);
            free(n->u.func.params);
            free_node(n->u.func.body);
            break;
        case AST_BLOCK:
            for (size_t i=0;i<n->u.block.stmtc;++i) free_node(n->u.block.stmts[i]);
            free(n->u.block.stmts);
            break;
        case AST_RETURN:
            free_node(n->u.ret.expr);
            break;
        case AST_ENUM_DECL:
            free(n->u.enum_decl.name);
            for (size_t i=0;i<n->u.enum_decl.memberc;++i) free(n->u.enum_decl.members[i]);
            free(n->u.enum_decl.members);
            break;
        case AST_STRUCT_DECL:
            free(n->u.struct_decl.name);
            for (size_t i=0;i<n->u.struct_decl.fieldc;++i) {
                ast_field_t *f = n->u.struct_decl.fields[i];
                free(f->name); free(f->type_name); free_node(f->inline_type); free_node(f->default_value); free(f);
            }
            free(n->u.struct_decl.fields);
            break;
        case AST_STRUCT_LITERAL:
            for (size_t i=0;i<n->u.struct_lit.fieldc;++i) { ast_field_t *f = n->u.struct_lit.fields[i]; free(f->name); free_node(f->default_value); free(f); }
            free(n->u.struct_lit.fields);
            break;
        default:
            break;
    }
    free(n);
}

void free_ast(ast_node_t *root) { free_node(root); }

/* pretty-print minimal */
static void pad(int indent) { for (int i=0;i<indent;++i) putchar(' '); }

void print_ast(const ast_node_t *root, int indent) {
    if (!root) return;
    switch (root->kind) {
        case AST_PROGRAM:
            pad(indent); printf("program\n");
            for (size_t i=0;i<root->u.block.stmtc;++i) print_ast(root->u.block.stmts[i], indent+2);
            break;
        case AST_FUNC_DECL:
            pad(indent); printf("func %s() -> %s\n", root->u.func.name, root->u.func.ret_type ? root->u.func.ret_type : "(nil)");
            print_ast(root->u.func.body, indent+2);
            break;
        case AST_VAR_DECL:
            pad(indent); printf("var %s : %s\n", root->u.vardecl.name, root->u.vardecl.type_name ? root->u.vardecl.type_name : "(nil)");
            if (root->u.vardecl.init) print_ast(root->u.vardecl.init, indent+2);
            break;
        case AST_STRUCT_DECL:
            pad(indent); printf("struct %s\n", root->u.struct_decl.name ? root->u.struct_decl.name : "(anon)");
            for (size_t i=0;i<root->u.struct_decl.fieldc;++i) {
                ast_field_t *f = root->u.struct_decl.fields[i]; pad(indent+2); printf("field %s : %s\n", f->name, f->type_name ? f->type_name : "(inline)");
            }
            break;
        case AST_ENUM_DECL:
            pad(indent); printf("enum %s {", root->u.enum_decl.name ? root->u.enum_decl.name : "(anon)");
            for (size_t i=0;i<root->u.enum_decl.memberc;++i) { if (i) printf(", "); printf("%s", root->u.enum_decl.members[i]); }
            printf("}\n");
            break;
        case AST_STRUCT_LITERAL:
            pad(indent); printf("struct-literal\n");
            for (size_t i=0;i<root->u.struct_lit.fieldc;++i) { ast_field_t *f = root->u.struct_lit.fields[i]; pad(indent+2); printf(". %s = ...\n", f->name); }
            break;
        case AST_LITERAL:
            pad(indent); printf("lit %s\n", root->u.literal.value); break;
        case AST_IDENTIFIER:
            pad(indent); printf("ident %s\n", root->u.ident.name); break;
        case AST_CALL_EXPR:
            pad(indent); printf("call\n"); print_ast(root->u.call.callee, indent+2); for (size_t i=0;i<root->u.call.argc;++i) print_ast(root->u.call.args[i], indent+2); break;
        case AST_BINARY_EXPR:
            pad(indent); printf("binary %s\n", root->u.binary.op); print_ast(root->u.binary.left, indent+2); print_ast(root->u.binary.right, indent+2); break;
        default:
            pad(indent); printf("(unhandled ast node)\n"); break;
    }
}
