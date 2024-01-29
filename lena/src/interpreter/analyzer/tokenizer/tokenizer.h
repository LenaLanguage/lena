#ifndef __LENA_INTERPRETOR_TOKENIZER_H__
#define __LENA_INTERPRETOR_TOKENIZER_H__

/**************************************************************************//**
 * @file     tokenizer.h
 * @brief    Project L - Lena programming language main tokenizer library
 * @version  V0.0.1
 * @date     21. Jan 2024
 ******************************************************************************/

/* Include libraries */
#include <stdlib.h>
#include <stdint.h>

/* non-core */
#include "ltypes/lchar.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* -------- Data types -------- */

/* Types of token */
typedef enum {

    /* End */
    LENA_TOKEN_EOF, // = 0

    /* -------- Simple tokens -------- */

    /* Symbols */
    LENA_TOKEN_COMMA,       /* , */

    /* Comments */
    LENA_TOKEN_C_SEMICOLON, /* ; */

    /* Arithmetic */
    LENA_TOKEN_AC_PLUS,     /* + */
    LENA_TOKEN_AC_MINUS,    /* - */
    LENA_TOKEN_AC_MUL,      /* * */
    LENA_TOKEN_AC_DIV,      /* / */
    LENA_TOKEN_AC_MOD,      /* % */

    /* Binary */
    LENA_TOKEN_BIN_NOT,   /* ! */
    LENA_TOKEN_BIN_AND,   /* & */
    LENA_TOKEN_BIN_OR,    /* | */
    LENA_TOKEN_BIN_XOR,   /* ^ */

    /* -------- Multisymbols tokens -------- */
    
    /* Multiline comments */
    LENA_TOKEN_MC_BEGIN,    // /* 
    LENA_TOKEN_MC_END,      // */

    /* Logic */
    LENA_TOKEN_LOGIC_NOT,   /* not */
    LENA_TOKEN_LOGIC_AND,   /* and */
    LENA_TOKEN_LOGIC_OR,    /* or */
    LENA_TOKEN_LOGIC_XOR,   /* xor */

    /* -------- Data type identifers  -------- */

    LENA_TOKEN_IDENTIFIER_DTYPE_I8,
    LENA_TOKEN_IDENTIFIER_DTYPE_U8,
    LENA_TOKEN_IDENTIFIER_DTYPE_I16,
    LENA_TOKEN_IDENTIFIER_DTYPE_U16,
    LENA_TOKEN_IDENTIFIER_DTYPE_I32,
    LENA_TOKEN_IDENTIFIER_DTYPE_U32,
    LENA_TOKEN_IDENTIFIER_DTYPE_I64,
    LENA_TOKEN_IDENTIFIER_DTYPE_U64,

    LENA_TOKEN_IDENTIFIER_DTYPE_F32,
    LENA_TOKEN_IDENTIFIER_DTYPE_F64,

    LENA_TOKEN_IDENTIFIER_DTYPE_STR,

    /* Data */
    LENA_TOKEN_DATA_INTEGER,
    LENA_TOKEN_DATA_DECIMAL,

    LENA_TOKEN_DATA_STRING,

    /* -------- Brackets -------- */

    LENA_TOKEN_SLBRACKET,       /* [ */
    LENA_TOKEN_SRBRACKET,       /* ] */
    LENA_TOKEN_LPARENTHESIS,    /* ( */
    LENA_TOKEN_RPARENTHESIS,    /* ) */
    LENA_TOKEN_LBRACE,          /* { */
    LENA_TOKEN_RBRACE,          /* } */

    /* -------- General identitier  -------- */
    LENA_TOKEN_IDENTIFIER_GENERAL,

    /* -------- Specific identitiers -------- */
    LENA_TOKEN_KW_DEFINE,
    LENA_TOKEN_KW_AS,
    LENA_TOKEN_KW_WITH,
    LENA_TOKEN_KW_DEFAULT,
    LENA_TOKEN_KW_REPEAT,
    LENA_TOKEN_KW_TIMES,

    /* Error */
    LENA_TOKEN_ERROR_SYNTAX,
} ltoken_type_t;

/* Struct of every token*/
typedef struct {
    ltoken_type_t type;
    lchar_t* data;
    size_t len;
} ltoken_t;

/* Struct of buffer of tokens */
typedef struct {
    ltoken_t* token;
    size_t len;
    size_t index;
} ltoken_buffer_t;

/* Macroses for simple tokens */

typedef enum {

    /* Comma */
    LENA_TOKEN_ST_COMMA = l(','),       /* , */

    /* Comments */
    LENA_TOKEN_ST_C_SEMICOLON  = l(';'),/* ; */

    /* Arithmetic */
    LENA_TOKEN_ST_AC_PLUS  = l('+'),    /* + */
    LENA_TOKEN_ST_AC_MINUS = l('-'),    /* - */
    LENA_TOKEN_ST_AC_MUL   = l('*'),    /* * */
    LENA_TOKEN_ST_AC_DIV   = l('/'),    /* / */
    LENA_TOKEN_ST_AC_MOD   = l('%'),    /* % */

    /* Binary */
    LENA_TOKEN_ST_BIN_NOT  = l('!'),    /* ! */
    LENA_TOKEN_ST_BIN_AND  = l('&'),    /* & */
    LENA_TOKEN_ST_BIN_OR   = l('|'),    /* | */
    LENA_TOKEN_ST_BIN_XOR  = l('^'),    /* ^ */

} ltoken_stoken_list_t;

/* -------- Functions -------- */

/* private */

/**
 *  is_token_valid()
 *  
*/

/* helpers */

/**
 * token_get_new()
*/

/* public */

bool ltoken_buffer_init(ltoken_buffer_t* buffer);
void ltoken_buffer_deinit(ltoken_buffer_t* buffer);

void token_get_new(lchar_t* input[], ltoken_buffer_t* buffer);

void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer);


#endif // __LENA_INTERPRETOR_TOKENIZER_H__