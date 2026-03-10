#ifndef LENA_TOKENIZER_H
#define LENA_TOKENIZER_H

#include <stdlib.h>

/* token types used by tokenizer and parser */
typedef enum {
    TOK_EOF,
    TOK_IDENTIFIER,
    TOK_KEYWORD,
    TOK_NUMBER_INT,
    TOK_NUMBER_FLOAT,
    TOK_STRING,
    TOK_CHAR,
    TOK_OPERATOR,
    TOK_PUNCT,
    TOK_COMMENT,
    TOK_NEWLINE,
    TOK_UNKNOWN
} token_type;

/* token */
typedef struct {
    token_type type;
    char *lexeme;
    size_t line;
    size_t column;
} token_t;

/* dynamic token list */
typedef struct {
    token_t *data;
    size_t len;
    size_t cap;
} token_list_t;

/* tokenize a NUL-terminated source string into a token_list_t */
token_list_t tokenize(const char *src);

/* free token list and contained lexemes */
void free_token_list(token_list_t *list);

/* pretty-print tokens to stdout */
void print_tokens(const token_list_t *list);

#endif /* LENA_TOKENIZER_H */
