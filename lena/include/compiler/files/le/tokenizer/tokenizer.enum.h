#ifndef LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_
#define LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_


/**************************************************************************//**
 * @file     tokenizer.enum.h
 * @brief    Project L - Lena programming language / compiler files '.le' header
 * @version  V0.4.0
 * @date     5. Jule 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Limits */

/* One symbol tokens */
#define LE_TOKEN_ONE_SYMBOL_BEGIN 1
#define LE_TOKEN_ONE_SYMBOL_END

/* Multi-characters tokens */
#define LE_TOKEN_MULTI_SYMBOL_BEGIN (LE_TOKEN_ONE_SYMBOL_END + 1)
#define LE_TOKEN_MULTI_SYMBOL_END

/* Undefined value tokens */
#define LE_TOKEN_UNDEF_SYMBOL_BEGIN 1
#define LE_TOKEN_UNDEF_SYMBOL_END

// to use like: for(i = _BEGIN; i <= _END; ++i)

/** 
 * @brief Token type
*/
typedef enum {

    LE_TOKEN_EOF = 0x00, // end of file

    /* Comments */
    LE_TOKEN_ONE_COMMENT = 0 + LE_TOKEN_ONE_SYMBOL_BEGIN, // ';'
    LE_TOKEN_MULTILINE_COMMENT_L = 0 + LE_TOKEN_MULTI_SYMBOL_BEGIN, // '/*'
    LE_TOKEN_MULTILINE_COMMENT_R = 1 + LE_TOKEN_MULTI_SYMBOL_BEGIN, // '*/'

    /* Math */
    LE_TOKEN_MATH_EQU   = 1 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* = */

    LE_TOKEN_MATH_PLUS  = 2 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* + */
    LE_TOKEN_MATH_MINUS = 3 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* - */
    LE_TOKEN_MATH_MUL   = 4 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* * */
    LE_TOKEN_MATH_DIV   = 5 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* / */
    LE_TOKEN_MATH_CDIV  = 2 + LE_TOKEN_MULTI_SYMBOL_BEGIN,  /* // */
    LE_TOKEN_MATH_MOD   = 6 + LE_TOKEN_ONE_SYMBOL_BEGIN,    /* % */
    

    /* Comparison */
    LE_TOKEN_CMP_E  = 3 + LE_TOKEN_MULTI_SYMBOL_BEGIN,      /* == */
    LE_TOKEN_CMP_G  = 7 + LE_TOKEN_ONE_SYMBOL_BEGIN,        /* > */
    LE_TOKEN_CMP_L  = 8 + LE_TOKEN_ONE_SYMBOL_BEGIN,        /* < */
    LE_TOKEN_CMP_GE = 4 + LE_TOKEN_MULTI_SYMBOL_BEGIN,      /* >= */
    LE_TOKEN_CMP_LE = 5 + LE_TOKEN_MULTI_SYMBOL_BEGIN,      /* <= */

    /* Logic */
    LE_TOKEN_LOGIC_IF   = 6 + LE_TOKEN_MULTI_SYMBOL_BEGIN,  /* if */
    LE_TOKEN_LOGIC_ELSE = 7 + LE_TOKEN_MULTI_SYMBOL_BEGIN,  /* else */
    LE_TOKEN_LOGIC_ELIF = 8 + LE_TOKEN_MULTI_SYMBOL_BEGIN,  /* elif */

    LE_TOKEN_LOGIC_NOT  = 9 + LE_TOKEN_MULTI_SYMBOL_BEGIN,  /* not */
    LE_TOKEN_LOGIC_AND  = 10 + LE_TOKEN_MULTI_SYMBOL_BEGIN, /* and */
    LE_TOKEN_LOGIC_OR   = 11 + LE_TOKEN_MULTI_SYMBOL_BEGIN, /* or */
    LE_TOKEN_LOGIC_XOR  = 12 + LE_TOKEN_MULTI_SYMBOL_BEGIN, /* xor */

} le_token_t;

#endif // LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_