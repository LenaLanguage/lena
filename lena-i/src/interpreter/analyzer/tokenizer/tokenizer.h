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

/* core */
#include "interpreter/core/lencoders/lencoder.h"

/* non-core */
#include "ltypes/lchar.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* -------- Data types -------- */

/* Types of token */
typedef enum {

    /* End */
    LENA_TOKEN_EOF, // = 0 / '\0'

    /* -------- Simple tokens -------- */

    /* Symbols */
    LENA_TOKEN_COMMA,     /* , */
    LENA_TOKEN_COLON,     /* : */

    /* Comments */
    LENA_TOKEN_C_SEMICOLON, /* ; */

    /* Multiline comments */
    LENA_TOKEN_MC_BEGIN,    // /* 
    LENA_TOKEN_MC_END,      // */

    /* Arithmetic */
    LENA_TOKEN_AC_EQU,      /* = */

    LENA_TOKEN_AC_PLUS,     /* + */
    LENA_TOKEN_AC_MINUS,    /* - */
    LENA_TOKEN_AC_MUL,      /* * */
    LENA_TOKEN_AC_DIV,      /* / */
    LENA_TOKEN_AC_MOD,      /* % */

    /* Comparison */
    LENA_TOKEN_CMP_E,       /* == */
    LENA_TOKEN_CMP_G,       /* > */
    LENA_TOKEN_CMP_L,       /* < */
    LENA_TOKEN_CMP_GE,      /* >= */
    LENA_TOKEN_CMP_LE,      /* <= */


    /* Binary */
    LENA_TOKEN_BIN_NOT,   /* ! */
    LENA_TOKEN_BIN_AND,   /* & */
    LENA_TOKEN_BIN_OR,    /* | */
    LENA_TOKEN_BIN_XOR,   /* ^ */

    /* -------- Multisymbols tokens -------- */
    
    /* Streams */
    LENA_TOKEN_LSTREAM,     /* << */
    LENA_TOKEN_RSTREAM,     /* >> */

    /* Сonsequences */
    LENA_TOKEN_LCONS,       /* <- */
    LENA_TOKEN_RCONS,       /* -> */

    /* Logic */

    LENA_TOKEN_LOGIC_IF,    /* if */
    LENA_TOKEN_LOGIC_ELSE,  /* else */
    LENA_TOKEN_LOGIC_ELIF,  /* elif */

    LENA_TOKEN_LOGIC_NOT,   /* not */
    LENA_TOKEN_LOGIC_AND,   /* and */
    LENA_TOKEN_LOGIC_OR,    /* or */
    LENA_TOKEN_LOGIC_XOR,   /* xor */

    /* -------- Data type identifers  -------- */

    LENA_TOKEN_IDENTIFIER_DTYPE_BOOL,   /* bool */

    LENA_TOKEN_IDENTIFIER_DTYPE_I8,     /* i8 */
    LENA_TOKEN_IDENTIFIER_DTYPE_U8,     /* u8 */
    LENA_TOKEN_IDENTIFIER_DTYPE_I16,    /* i16 */
    LENA_TOKEN_IDENTIFIER_DTYPE_U16,    /* u16 */
    LENA_TOKEN_IDENTIFIER_DTYPE_I32,    /* i32 */
	LENA_TOKEN_IDENTIFIER_DTYPE_U32,    /* u32 */
    LENA_TOKEN_IDENTIFIER_DTYPE_I64,    /* i64 */
    LENA_TOKEN_IDENTIFIER_DTYPE_U64,    /* u64 */

    LENA_TOKEN_IDENTIFIER_DTYPE_F32,    /* f32 */
    LENA_TOKEN_IDENTIFIER_DTYPE_F64,    /* f64 */

    LENA_TOKEN_IDENTIFIER_DTYPE_STR,    /* "" or '' */

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

    /* Logic */
    LENA_TOKEN_KW_TRUE,
    LENA_TOKEN_KW_FALSE,

    /* Other keywords */

    LENA_TOKEN_KW_AS,
    LENA_TOKEN_KW_WITH,
    LENA_TOKEN_KW_DEFAULT,

    LENA_TOKEN_KW_REPEAT,
    LENA_TOKEN_KW_TIMES,

    LENA_TOKEN_KW_TRY,
    LENA_TOKEN_KW_EXCEPT,

    /* New line */
    LENA_TOKEN_NEWLINE,

    /* Only errors after LENA_TOKEN_ERROR_SYNTAX */

    /* Error */
    LENA_TOKEN_ERROR_SYNTAX,
    LENA_TOKEN_ERROR_INVALID_SYMBOL,
} ltoken_type_t;

/* Struct of every token */
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

/* -------- Functions -------- */

/**
 * @brief Initialization of buffer token
*/
extern lerror_t ltoken_buffer_init(ltoken_buffer_t* buffer);
/**
 * @brief Free memory that was allocated for buffer
*/
extern void ltoken_buffer_deinit(ltoken_buffer_t* buffer);
/**
 * @brief Main function to recognize tokens from data lchar_t pointer
*/
extern void ltoken_get(lchar_t* input[], ltoken_buffer_t* buffer);


#endif // __LENA_INTERPRETOR_TOKENIZER_H__