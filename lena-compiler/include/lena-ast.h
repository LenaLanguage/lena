#ifndef LENA_AST_H
#define LENA_AST_H

#include <lena-tokenizer.h>
#include <stddef.h>

/* Basic AST node kinds */
typedef enum {
    AST_PROGRAM,
    AST_FUNC_DECL,
    AST_VAR_DECL,
    AST_BLOCK,
    AST_RETURN,
    AST_LITERAL,
    AST_IDENTIFIER,
    AST_CALL_EXPR,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_ENUM_DECL,
    AST_STRUCT_DECL,
    AST_STRUCT_LITERAL,
    /* add other node kinds as needed */
} ast_node_type;

/* base location for nodes */
typedef struct {
    size_t line;
    size_t column;
} ast_node_base_t;

/* literal kinds */
typedef enum {
    LIT_INT,
    LIT_FLOAT,
    LIT_STRING,
    LIT_CHAR
} ast_lit_kind_t;

/* forward declaration */
typedef struct ast_node ast_node_t;

/* AST node definitions (minimal set used by parser/codegen) */

typedef struct {
    ast_node_base_t base;
    char *value;         /* raw lexeme, e.g. "123", "\"hello\"" */
    ast_lit_kind_t lit_kind;
} ast_literal_t;

typedef struct {
    ast_node_base_t base;
    char *name; /* may contain qualification like :: or a::b */
} ast_identifier_t;

typedef struct {
    ast_node_base_t base;
    ast_node_t *callee;
    ast_node_t **args;
    size_t argc;
} ast_call_t;

typedef struct {
    ast_node_base_t base;
    char *op;
    ast_node_t *left;
    ast_node_t *right;
} ast_binary_t;

typedef struct {
    ast_node_base_t base;
    char *op;
    ast_node_t *operand;
} ast_unary_t;

/* struct field (used for struct declarations and literals) */
typedef struct {
    char *name;
    char *type_name;        /* textual type if present, e.g. "i32" or "piano" */
    ast_node_t *inline_type;/* if field type is inline (enum/struct) */
    ast_node_t *default_value; /* optional initializer expression or literal */
} ast_field_t;

/* enum declaration */
typedef struct {
    int line, column;
    char *name;      /* optional name for named enums (NULL if anonymous) */
    char **members;  /* array of member names */
    size_t memberc;
} ast_enum_decl_t;

/* struct declaration (type) */
typedef struct {
    int line, column;
    char *name;       /* type name, may be NULL for anonymous inline structs */
    ast_field_t **fields;
    size_t fieldc;
} ast_struct_decl_t;

/* struct literal (value) */
typedef struct {
    ast_field_t **fields;
    size_t fieldc;
} ast_struct_literal_t;

/* variable declaration */
typedef struct {
    ast_node_base_t base;
    char *name;
    char *type_name;     /* textual type, may include [] */
    ast_node_t *init;    /* optional initializer */
} ast_var_decl_t;

/* function declaration */
typedef struct {
    ast_node_base_t base;
    char *name;
    char **params; /* textual param descriptors like "p:i32" */
    size_t paramc;
    char *ret_type; /* textual return type */
    ast_node_t *body; /* block */
} ast_func_decl_t;

/* block */
typedef struct {
    ast_node_base_t base;
    ast_node_t **stmts;
    size_t stmtc;
} ast_block_t;

/* return */
typedef struct {
    ast_node_base_t base;
    ast_node_t *expr; /* optional */
} ast_return_t;

/* unify AST node */
struct ast_node {
    ast_node_type kind;
    union {
        ast_literal_t literal;
        ast_identifier_t ident;
        ast_call_t call;
        ast_binary_t binary;
        ast_unary_t unary;
        ast_var_decl_t vardecl;
        ast_func_decl_t func;
        ast_block_t block;
        ast_return_t ret;
        ast_enum_decl_t enum_decl;
        ast_struct_decl_t struct_decl;
        ast_struct_literal_t struct_lit;
        /* extend with more variants as needed */
    } u;
};

/* API: parse program from token list (defined in parser .c) */
ast_node_t *parse_program(token_list_t *tokens);

/* free AST and children */
void free_ast(ast_node_t *root);

/* pretty-print AST for debugging */
void print_ast(const ast_node_t *root, int indent);

#endif /* LENA_AST_H */
