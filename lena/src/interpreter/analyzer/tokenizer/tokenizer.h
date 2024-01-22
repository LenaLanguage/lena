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

    /* Data (Positive and Negative) */
    LENA_TOKEN_DATA_PINTEGER,
    LENA_TOKEN_DATA_NINTEGER,

    LENA_TOKEN_DATA_PDOUBLE,
    LENA_TOKEN_DATA_NDOUBLE,

    /* Brackets */
    LENA_TOKEN_SLBRACKET,       /* [ */
    LENA_TOKEN_SRBRACKET,       /* ] */
    LENA_TOKEN_LPARENTHESIS,    /* ( */
    LENA_TOKEN_RPARENTHESIS,    /* ) */
    LENA_TOKEN_LBRACE,          /* { */
    LENA_TOKEN_RBRACE,          /* } */

} ltoken_t;

#endif // __LENA_INTERPRETOR_TOKENIZER_H__