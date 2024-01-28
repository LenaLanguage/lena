#ifndef __LENA_INTERPRETOR_TOKENIZER_H__
#define __LENA_INTERPRETOR_TOKENIZER_H__

/**************************************************************************//**
 * @file     tokenizer.h
 * @brief    Project L - Lena programming language main tokenizer library
 * @version  V0.0.1
 * @date     21. Jan 2024
 ******************************************************************************/

/* Include libraries */

/* Data types */
typedef enum {

    /* Keywords */
    LENA_TOKEN_KW_DEFINE,
    LENA_TOKEN_KW_AS,
    LENA_TOKEN_KW_WITH,
    LENA_TOKEN_KW_DEFAULT,
    LENA_TOKEN_KW_REPEAT,
    LENA_TOKEN_KW_TIMES,

    /* Symbols */
    LENA_TOKEN_COMMA,           /* , */

    /* Comments */
    LENA_TOKEN_C_SEMICOLON,       /* ; */

    /* Multiline comments */
    LENA_TOKEN_MC_BEGIN,        // /* 
    LENA_TOKEN_MC_END,          // */ 

    /* Arithmetic */
    LENA_TOKEN_AC_PLUS,     /* + */
    LENA_TOKEN_AC_MINUS,    /* - */
    LENA_TOKEN_AC_MUL,      /* * */
    LENA_TOKEN_AC_DIV,      /* / */
    LENA_TOKEN_AC_MOD,      /* % */

    /* Logic */
    LENA_TOKEN_LOGIC_NOT,   /* not */
    LENA_TOKEN_LOGIC_AND,   /* and */
    LENA_TOKEN_LOGIC_OR,    /* or */
    LENA_TOKEN_LOGIC_XOR,   /* xor */

    /* Binary */
    LENA_TOKEN_BIN_NOT,   /* ! */
    LENA_TOKEN_BIN_AND,   /* & */
    LENA_TOKEN_BIN_OR,    /* | */
    LENA_TOKEN_BIN_XOR,   /* ^ */


    /* Data type identifers */
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

    /* Brackets */
    LENA_TOKEN_SLBRACKET,       /* [ */
    LENA_TOKEN_SRBRACKET,       /* ] */
    LENA_TOKEN_LPARENTHESIS,    /* ( */
    LENA_TOKEN_RPARENTHESIS,    /* ) */
    LENA_TOKEN_LBRACE,          /* { */
    LENA_TOKEN_RBRACE,          /* } */

} ltoken_type_t;

typedef struct {
    ltoken_type_t type;
    
} ltoken_t;

#endif // __LENA_INTERPRETOR_TOKENIZER_H__