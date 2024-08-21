#ifndef LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_
#define LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_

/**************************************************************************//**
 * @file     tokenizer.enum.h
 * @brief    Project L - Lena programming language / compiler files '.le' header
 * @version  V0.4.0
 * @date     5. Jule 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* ----- Limits ----- */

/**
 * @warning USE `<=` and `>=`
 */

/* One byte tokens */
#define LE_TOKEN_ONE_BYTE_BEGIN 1
#define LE_TOKEN_ONE_BYTE_END (17 + LE_TOKEN_ONE_BYTE_BEGIN)

/* Multi-byte tokens */
#define LE_TOKEN_MULTI_BYTE_BEGIN (LE_TOKEN_ONE_BYTE_END ) + 1
#define LE_TOKEN_MULTI_BYTE_END (27 + LE_TOKEN_MULTI_BYTE_BEGIN)

/* Undefined value tokens */
#define LE_TOKEN_UNDEF_BYTE_BEGIN (LE_TOKEN_MULTI_BYTE_END) + 1
#define LE_TOKEN_UNDEF_BYTE_END (4 + LE_TOKEN_UNDEF_BYTE_BEGIN)

/* Invalid tokens */
#define LE_TOKEN_INVALID_BYTE_BEGIN 0xFE
#define LE_TOKEN_INVALID_BYTE_END 0xFF

// to use like: for(i = _BEGIN; i <= _END; ++i)

/** 
 * @brief Token type. `(lu8 type) -> max = 0xFF`
*/
typedef enum {

    LE_TOKEN_EOF = 0x00, // end of file

    /* ----- Comments ----- */
    LE_TOKEN_ONE_COMMENT         = 0 + LE_TOKEN_ONE_BYTE_BEGIN,     // ';'
    LE_TOKEN_MULTILINE_COMMENT_L = 0 + LE_TOKEN_MULTI_BYTE_BEGIN,   // '/*'
    LE_TOKEN_MULTILINE_COMMENT_R = 1 + LE_TOKEN_MULTI_BYTE_BEGIN,   // '*/'

    /* ----- Math ----- */
    LE_TOKEN_MATH_EQU   = 1 + LE_TOKEN_ONE_BYTE_BEGIN,    /* = */

    LE_TOKEN_MATH_PLUS  = 2 + LE_TOKEN_ONE_BYTE_BEGIN,    /* + */
    LE_TOKEN_MATH_MINUS = 3 + LE_TOKEN_ONE_BYTE_BEGIN,    /* - */
    LE_TOKEN_MATH_MUL   = 4 + LE_TOKEN_ONE_BYTE_BEGIN,    /* * */
    LE_TOKEN_MATH_DIV   = 5 + LE_TOKEN_ONE_BYTE_BEGIN,    /* / */
    LE_TOKEN_MATH_CDIV  = 2 + LE_TOKEN_MULTI_BYTE_BEGIN,  /* // */
    LE_TOKEN_MATH_MOD   = 6 + LE_TOKEN_ONE_BYTE_BEGIN,    /* % */
    
    LE_TOKEN_MATH_PLUS_EQ  = 28 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* += */
    LE_TOKEN_MATH_MINUS_EQ = 29 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* -= */
    LE_TOKEN_MATH_MUL_EQ   = 30 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* *= */
    LE_TOKEN_MATH_DIV_EQ   = 31 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* /= */
    LE_TOKEN_MATH_CDIV_EQ  = 32 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* //= */
    LE_TOKEN_MATH_MOD_EQ   = 33 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* %= */

    /* ----- Comparison ----- */
    LE_TOKEN_CMP_E  = 3 + LE_TOKEN_MULTI_BYTE_BEGIN,      /* == */
    LE_TOKEN_CMP_G  = 7 + LE_TOKEN_ONE_BYTE_BEGIN,        /* > */
    LE_TOKEN_CMP_L  = 8 + LE_TOKEN_ONE_BYTE_BEGIN,        /* < */
    LE_TOKEN_CMP_GE = 4 + LE_TOKEN_MULTI_BYTE_BEGIN,      /* >= */
    LE_TOKEN_CMP_LE = 5 + LE_TOKEN_MULTI_BYTE_BEGIN,      /* <= */

    /* ----- Logic ----- */
    LE_TOKEN_LOGIC_IF   = 6 + LE_TOKEN_MULTI_BYTE_BEGIN,  /* if */
    LE_TOKEN_LOGIC_ELSE = 7 + LE_TOKEN_MULTI_BYTE_BEGIN,  /* else */
    LE_TOKEN_LOGIC_ELIF = 8 + LE_TOKEN_MULTI_BYTE_BEGIN,  /* elif */

    LE_TOKEN_LOGIC_NOT  = 9 + LE_TOKEN_MULTI_BYTE_BEGIN,  /* not */
    LE_TOKEN_LOGIC_AND  = 10 + LE_TOKEN_MULTI_BYTE_BEGIN, /* and */
    LE_TOKEN_LOGIC_OR   = 11 + LE_TOKEN_MULTI_BYTE_BEGIN, /* or */
    LE_TOKEN_LOGIC_XOR  = 12 + LE_TOKEN_MULTI_BYTE_BEGIN, /* xor */

    /* ----- Data types ----- */

    LE_TOKEN_ID_DTYPE_BOOL  = 13 + LE_TOKEN_MULTI_BYTE_BEGIN,     /* bool */

    LE_TOKEN_ID_DTYPE_I8    = 14 + LE_TOKEN_MULTI_BYTE_BEGIN,     /* i8 */
    LE_TOKEN_ID_DTYPE_U8    = 15 + LE_TOKEN_MULTI_BYTE_BEGIN,     /* u8 */
    LE_TOKEN_ID_DTYPE_I16   = 16 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* i16 */
    LE_TOKEN_ID_DTYPE_U16   = 17 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* u16 */
    LE_TOKEN_ID_DTYPE_I32   = 18 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* i32 */
	LE_TOKEN_ID_DTYPE_U32   = 19 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* u32 */
    LE_TOKEN_ID_DTYPE_I64   = 20 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* i64 */
    LE_TOKEN_ID_DTYPE_U64   = 21 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* u64 */

    LE_TOKEN_ID_DTYPE_F32   = 22 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* f32 */
    LE_TOKEN_ID_DTYPE_F64   = 23 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* f64 */

    LE_TOKEN_IDENTIFIER_DTYPE_STR   = 24 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* str */
    LE_TOKEN_IDENTIFIER_DTYPE_CHAR  = 25 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* char */

    /* ----- Keywords (all MULTI_BYTE) ----- */

    /* Logic type */
    LE_TOKEN_KW_TRUE    = 26 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* true */
    LE_TOKEN_KW_FALSE   = 27 + LE_TOKEN_MULTI_BYTE_BEGIN,    /* false */


    /* ----- Brackets (all ONE_BYTE) ----- */

    LE_TOKEN_SLBRACKET    = 9 + LE_TOKEN_ONE_BYTE_BEGIN,        /* [ */
    LE_TOKEN_SRBRACKET    = 10 + LE_TOKEN_ONE_BYTE_BEGIN,       /* ] */
    LE_TOKEN_LPARENTHESIS = 11 + LE_TOKEN_ONE_BYTE_BEGIN,       /* ( */
    LE_TOKEN_RPARENTHESIS = 12 + LE_TOKEN_ONE_BYTE_BEGIN,       /* ) */
    LE_TOKEN_LBRACE       = 13 + LE_TOKEN_ONE_BYTE_BEGIN,       /* { */
    LE_TOKEN_RBRACE       = 14 + LE_TOKEN_ONE_BYTE_BEGIN,       /* } */

    /* ----- Values and identifiers (all UNDEF_BYTE) ----- */

    LE_TOKEN_INTEGER    = 0 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* like: 100 */
    LE_TOKEN_DECIMAL    = 1 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* like: 100.5 */
    LE_TOKEN_STRING     = 2 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* like: "lena" */
    LE_TOKEN_CHAR       = 3 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* like: 'l' */

    LE_TOKEN_IDENTIFIER_UNDEF   = 4 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* source code ids like func() and etc. */
    // LE_TOKEN_IDENTIFIER_STD     = 5 + LE_TOKEN_UNDEF_BYTE_BEGIN,  /* source code stdlib ids */

    /* ----- Other general tokens (all ONE_BYTE) ----- */
    LE_TOKEN_COLON      = 15 + LE_TOKEN_ONE_BYTE_BEGIN,   // ':'
    LE_TOKEN_PERIOD     = 16 + LE_TOKEN_ONE_BYTE_BEGIN,   // '.'
    LE_TOKEN_COMMA      = 17 + LE_TOKEN_ONE_BYTE_BEGIN,   // ','

    /* ---------- SPECIFIC TOKENS ---------- */

    /* ----- Specific token (can be ONE_BYTE and MULTI_BYTE) ----- */
    LE_TOKEN_NEWLINE    = 0xFD,

    /* Invalid tokens */
    LE_TOKEN_INVALID_CHARACTER  = 0xFE,
    LE_TOKEN_SYNTAX_ERROR       = 0xFF,

} le_token_type_t;

/** 
 * @brief Token struct.
*/
typedef struct {
    le_token_type_t type;
    lc* value;
    lsz size; // not sure... but size in bytes looks more effective.
} le_token_t;

/** 
 * @brief Struct of tokens buffer.
*/
typedef struct {
    le_token_t* token;  // token buffer token
    lsz num;            // number of tokens
    lsz i;              // counter.
    lu64 loc;           // lines of code 
} le_token_buffer_t;

/** IMPORTANT INFORMATION!
 * 
 *  if `le_token_type_t type` = LE_TOKEN_SYNTAX_ERROR:
 *      `lc* value` must be used as brief of the error.
 *      `lsz size` in this case always = 0
 * 
 */

#endif // LENA_COMPILER_FILES_LE_TOKENIZER_ENUM_H_