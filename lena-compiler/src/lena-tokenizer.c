/* lena-tokenizer.c
   Updated: added keywords, light logging
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "lena-tokenizer.h"
#include "lena-util.h"

/* ------------------- internal helpers ------------------- */

static void list_init(token_list_t *l) {
    l->data = NULL;
    l->len = 0;
    l->cap = 0;
}

static void list_push(token_list_t *l, token_t t) {
    if (l->len + 1 > l->cap) {
        size_t newcap = l->cap ? l->cap * 2 : 16;
        token_t *arr = realloc(l->data, newcap * sizeof(token_t));
        if (!arr) { perror("realloc"); exit(1); }
        l->data = arr;
        l->cap = newcap;
    }
    l->data[l->len++] = t;
}

static char *strndup_local(const char *s, size_t n) {
    char *r = malloc(n + 1);
    if (!r) return NULL;
    memcpy(r, s, n);
    r[n] = '\0';
    return r;
}

static int is_ident_start(unsigned char c) {
    return (c == '_') || (isalpha(c) != 0) || (c >= 0x80);
}
static int is_ident_part(unsigned char c) {
    return (c == '_') || (isalnum(c) != 0) || (c >= 0x80);
}

/* ------------------- tokenizer core ------------------- */

token_list_t tokenize(const char *src) {
    lena_logf("tokenize: starting tokenization");
    token_list_t out;
    list_init(&out);
    size_t i = 0;
    size_t line = 1, column = 1;

    while (1) {
        char c = src[i];
        if (c == '\0') {
            token_t t = { .type = TOK_EOF, .lexeme = strndup_local("<eof>", 5), .line = line, .column = column };
            list_push(&out, t);
            lena_logf("tokenize: emitted EOF at %zu:%zu", line, column);
            break;
        }

        /* whitespace */
        if (c == ' ' || c == '\t' || c == '\r') {
            i++; column++;
            continue;
        }
        if (c == '\n') {
            token_t t = { .type = TOK_NEWLINE, .lexeme = strndup_local("\n", 1), .line = line, .column = column };
            list_push(&out, t);
            i++; line++; column = 1;
            continue;
        }

        /* comments start with # ; block comments start with "#=" and end with "=#" */
        if (c == '#') {
            if (src[i+1] == '=') {
                size_t start = i;
                i += 2; column += 2;
                const char *startptr = src + start;
                while (src[i] != '\0') {
                    if (src[i] == '=' && src[i+1] == '#') {
                        i += 2; column += 2;
                        break;
                    }
                    if (src[i] == '\n') { i++; line++; column = 1; continue; }
                    i++; column++;
                }
                size_t len = (src + i) - startptr;
                token_t t = { .type = TOK_COMMENT, .lexeme = strndup_local(startptr, len), .line = line, .column = column };
                list_push(&out, t);
                lena_logf("tokenize: block comment at line %zu", line);
                continue;
            } else {
                size_t start = i;
                const char *startptr = src + start;
                while (src[i] != '\0' && src[i] != '\n') { i++; column++; }
                size_t len = (src + i) - startptr;
                token_t t = { .type = TOK_COMMENT, .lexeme = strndup_local(startptr, len), .line = line, .column = column };
                list_push(&out, t);
                lena_logf("tokenize: line comment at line %zu", line);
                continue;
            }
        }

        /* strings */
        if (c == '"') {
            size_t start = i;
            i++; column++;
            while (src[i] != '\0') {
                if (src[i] == '\\') {
                    i += 2; column += 2;
                    continue;
                }
                if (src[i] == '"') {
                    i++; column++;
                    break;
                }
                if (src[i] == '\n') { i++; line++; column = 1; continue; }
                unsigned char uc = (unsigned char)src[i];
                if (uc >= 0x80) {
                    i++; column++;
                    while ((unsigned char)src[i] >= 0x80) { i++; column++; }
                    continue;
                }
                i++; column++;
            }
            size_t len = (src + i) - (src + start);
            token_t t = { .type = TOK_STRING, .lexeme = strndup_local(src + start, len), .line = line, .column = column };
            list_push(&out, t);
            lena_logf("tokenize: string token at %zu:%zu -> %.*s", t.line, t.column, (int)len, src+start);
            continue;
        }

        /* char literal 'a' */
        if (c == '\'') {
            size_t start = i;
            i++; column++;
            if (src[i] == '\\') {
                i += 2; column += 2;
            } else {
                i++; column++;
            }
            if (src[i] == '\'') { i++; column++; }
            size_t len = (src + i) - (src + start);
            token_t t = { .type = TOK_CHAR, .lexeme = strndup_local(src + start, len), .line = line, .column = column };
            list_push(&out, t);
            continue;
        }

        /* numbers */
        if (isdigit((unsigned char)c) || (c == '.' && isdigit((unsigned char)src[i+1]))) {
            size_t start = i;
            int is_float = 0;
            if (c == '0' && (src[i+1] == 'b' || src[i+1] == 'B')) {
                i += 2; column += 2;
                while (src[i] == '0' || src[i] == '1' || src[i] == '_') { i++; column++; }
            } else if (c == '0' && (src[i+1] == 'x' || src[i+1] == 'X')) {
                i += 2; column += 2;
                while (isxdigit((unsigned char)src[i]) || src[i] == '_') { i++; column++; }
            } else {
                if (c == '.') {
                    is_float = 1; i++; column++;
                    while (isdigit((unsigned char)src[i]) || src[i] == '_') { i++; column++; }
                } else {
                    while (isdigit((unsigned char)src[i]) || src[i] == '_') { i++; column++; }
                    if (src[i] == '.' && src[i+1] != '.' ) {
                        is_float = 1;
                        i++; column++;
                        while (isdigit((unsigned char)src[i]) || src[i] == '_') { i++; column++; }
                    }
                }
                if (src[i] == 'e' || src[i] == 'E') {
                    is_float = 1;
                    i++; column++;
                    if (src[i] == '+' || src[i] == '-') { i++; column++; }
                    while (isdigit((unsigned char)src[i])) { i++; column++; }
                }
            }
            size_t len = (src + i) - (src + start);
            token_t t = { .type = is_float ? TOK_NUMBER_FLOAT : TOK_NUMBER_INT, .lexeme = strndup_local(src + start, len), .line = line, .column = column };
            list_push(&out, t);
            continue;
        }

        /* identifiers and keywords */
        if (is_ident_start((unsigned char)c)) {
            size_t start = i;
            i++; column++;
            while (is_ident_part((unsigned char)src[i])) { i++; column++; }
            size_t len = (src + i) - (src + start);
            char *lex = strndup_local(src + start, len);
            int is_kw = 0;
            const char *keywords[] = { "let", "return", "if", "else", "while", "for", "struct", "enum", "type", "const", "true", "false", "on", NULL };
            for (int k = 0; keywords[k]; ++k) if (strcmp(lex, keywords[k]) == 0) { is_kw = 1; break; }
            token_t t = { .type = is_kw ? TOK_KEYWORD : TOK_IDENTIFIER, .lexeme = lex, .line = line, .column = column };
            list_push(&out, t);
            lena_logf("tokenize: %s '%s' at %zu:%zu", is_kw ? "keyword" : "ident", lex, line, column);
            continue;
        }

        /* multi-char operators/punctuators */
        if (src[i] == '.' && src[i+1] == '.' && src[i+2] == '.') {
            token_t t = { .type = TOK_OPERATOR, .lexeme = strndup_local("...", 3), .line = line, .column = column };
            list_push(&out, t); i += 3; column += 3; continue;
        }
        const char *two_ops[] = { "..", "::", "->", "==", "!=", ">=", "<=", "&&", "||", "<<", ">>", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", "<<=", ">>=" };
        int matched = 0;
        for (size_t tix = 0; tix < sizeof(two_ops)/sizeof(two_ops[0]); ++tix) {
            const char *op = two_ops[tix];
            size_t oplen = strlen(op);
            if (oplen == 2) {
                if (src[i] == op[0] && src[i+1] == op[1]) {
                    token_t t = { .type = TOK_OPERATOR, .lexeme = strndup_local(op, oplen), .line = line, .column = column };
                    list_push(&out, t); i += 2; column += 2; matched = 1; break;
                }
            }
            if (oplen == 3) {
                if (src[i] == op[0] && src[i+1] == op[1] && src[i+2] == op[2]) {
                    token_t t = { .type = TOK_OPERATOR, .lexeme = strndup_local(op, oplen), .line = line, .column = column };
                    list_push(&out, t); i += 3; column += 3; matched = 1; break;
                }
            }
        }
        if (matched) continue;

        /* single-char punct/op */
        char single = src[i];
        const char *single_ops = "(){}[],;:+-*/%<>=!~|^.&"; /* include more as needed */
        if (strchr(single_ops, single)) {
            char buf[2] = { single, '\0' };
            token_t t = { .type = TOK_PUNCT, .lexeme = strndup_local(buf, 1), .line = line, .column = column };
            list_push(&out, t); i++; column++; continue;
        }

        /* fallback: unknown single byte token */
        {
            char buf[2] = { src[i], '\0' };
            token_t t = { .type = TOK_UNKNOWN, .lexeme = strndup_local(buf, 1), .line = line, .column = column };
            list_push(&out, t); i++; column++;
            continue;
        }
    }

    lena_logf("tokenize: finished, %zu tokens emitted", out.len);
    return out;
}

void free_token_list(token_list_t *list) {
    if (!list) return;
    for (size_t i = 0; i < list->len; ++i) {
        free(list->data[i].lexeme);
    }
    free(list->data);
    list->data = NULL;
    list->len = 0;
    list->cap = 0;
}

void print_tokens(const token_list_t *list) {
    if (!list) return;
    for (size_t i = 0; i < list->len; ++i) {
        const token_t *t = &list->data[i];
        const char *tt = "?";
        switch (t->type) {
            case TOK_EOF: tt = "eof"; break;
            case TOK_IDENTIFIER: tt = "ident"; break;
            case TOK_KEYWORD: tt = "keyword"; break;
            case TOK_NUMBER_INT: tt = "int"; break;
            case TOK_NUMBER_FLOAT: tt = "float"; break;
            case TOK_STRING: tt = "string"; break;
            case TOK_CHAR: tt = "char"; break;
            case TOK_OPERATOR: tt = "op"; break;
            case TOK_PUNCT: tt = "punct"; break;
            case TOK_COMMENT: tt = "comment"; break;
            case TOK_NEWLINE: tt = "newline"; break;
            case TOK_UNKNOWN: tt = "unknown"; break;
        }
        printf("%04zu:%04zu %-8s '%s'\n", t->line, t->column, tt, t->lexeme);
    }
}
