/* Include libraries */
#include <stdint.h>
#include <stdbool.h>

/* non-core */
#include "ltypes/lchar.h"
#include "ltypes/lstring.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* tokenizer */
#include "tokenizer.h"

/* Extern funcrions */
size_t __token_identifier_get_len(lchar_t* input[]) {
    /* Clean function doesn't change (*input) pointer */
    lchar_t* identifier = (*input); size_t len = 0;
    while (is_lletter(*identifier) || is_ldigit(*identifier)) {
        ++len; ++identifier;
    }
    return len;
}

/* Functions for keywords */

/**
 * list:
 * 2 symbols:
 *      i8
 *      u8
 *      as
 *      or
 *      if
 * 
 * 3 symbols:
 *  LENA_TOKEN_LOGIC_NOT,   
    LENA_TOKEN_LOGIC_AND,
    LENA_TOKEN_LOGIC_XOR,

 *  LENA_TOKEN_KW_TRY,

 *  LENA_TOKEN_IDENTIFIER_DTYPE_I16,
    LENA_TOKEN_IDENTIFIER_DTYPE_U16,
    LENA_TOKEN_IDENTIFIER_DTYPE_I32,
	LENA_TOKEN_IDENTIFIER_DTYPE_U32,
    LENA_TOKEN_IDENTIFIER_DTYPE_I64,
    LENA_TOKEN_IDENTIFIER_DTYPE_U64,

    LENA_TOKEN_IDENTIFIER_DTYPE_F32,
    LENA_TOKEN_IDENTIFIER_DTYPE_F64,

    LENA_TOKEN_IDENTIFIER_DTYPE_STR,

 * 4 symbols:
    LENA_TOKEN_KW_WITH,
    LENA_TOKEN_LOGIC_ELSE,  
    LENA_TOKEN_LOGIC_ELIF, 

   5 symbols:
    LENA_TOKEN_KW_TIMES

   6 symbols:
    LENA_TOKEN_KW_REPEAT

   7 symbols:
    LENA_TOKEN_KW_DEFAULT

    n + lenof(real)

 *      
*/

/* -------- Private data type -------- */

/* Data types of token ids */
typedef enum {
    LENA_TOKEN_IDENTIFIER_DTYPE_ID_8    = LENA_TOKEN_IDENTIFIER_DTYPE_I8,
    LENA_TOKEN_IDENTIFIER_DTYPE_ID_16   = LENA_TOKEN_IDENTIFIER_DTYPE_I16,
    LENA_TOKEN_IDENTIFIER_DTYPE_ID_32   = LENA_TOKEN_IDENTIFIER_DTYPE_I32,
    LENA_TOKEN_IDENTIFIER_DTYPE_ID_64   = LENA_TOKEN_IDENTIFIER_DTYPE_I64,
} ltoken_type_data_id_t;

/* ---------------- Different size functions ---------------- */
/* (private and unsafe) */

/* ---------------- 2 ----------------*/

ltoken_type_t __token_identifier_separate_2(lchar_t* id) {
    /* -------- this is 8 bit identifier -------- */
    if (id[1] == l('8')) {
        if (id[0] == l('i') || id[0] == l('u')) {
            return (ltoken_type_t)(LENA_TOKEN_IDENTIFIER_DTYPE_ID_8 + (int)(id[0] == l('u')));
        } else {
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }
    } else {
        /* -------- 'as', 'or', 'if' keywords -------- */
        if (id[0] == l('a') && id[1] == l('s')) {
            return LENA_TOKEN_KW_AS;
        } else if (id[0] == l('o') && id[1] == l('r')) {
            return LENA_TOKEN_LOGIC_OR;
        } else if (id[0] == l('i') && id[1] == l('f')) {
            return LENA_TOKEN_LOGIC_IF;
        } 
        // else {
            /* -------- Other 2-symbols keywords don't exist -------- */
        // }
    }
    return LENA_TOKEN_IDENTIFIER_GENERAL;
}

/* ---------------- 3 ----------------*/

ltoken_type_t __token_identifier_separate_3(lchar_t* id) {
    /* it can be 16, 32 or 64 bir identidtifier */
    if (id[1] == l('1')) {
        if (id[2] == l('6')) {
            /* -------- this is 16 bit identifier -------- */
            return (ltoken_type_t)(LENA_TOKEN_IDENTIFIER_DTYPE_ID_16 + (int)(id[0] == l('u')));
        } else {
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }
    } else if (id[1] == l('3')) {
        if (id[2] == l('2')) {
            /* -------- this is 32 bit identifier -------- */
            return (ltoken_type_t)(LENA_TOKEN_IDENTIFIER_DTYPE_ID_32 + (int)(id[0] == l('u')));
        } else {
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }
    } else if (id[1] == l('6')) {
        if (id[2] == l('4')) {
            /* -------- this is 64 bit identifier -------- */
            return (ltoken_type_t)(LENA_TOKEN_IDENTIFIER_DTYPE_ID_64 + (int)(id[0] == l('u')));
        } else {
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }
    } else {
        /* -------- this is logic operator -------- */
        if (id[1] == l('o')) {
            if (id[0] == l('n') && id[2] == l('t')) {
                /* -------- 'xor' keyword -------- */
                return LENA_TOKEN_LOGIC_NOT;
            } else if (id[0] == l('x') && id[2] == l('r')) {
                return LENA_TOKEN_LOGIC_XOR;
            } else {
                /* -------- 'try' keyword -------- */
                if (id[0] == l('t') && id[1] == l('r') && id[2] == l('y')) {
                    return LENA_TOKEN_KW_TRY;
                } else {
                    return LENA_TOKEN_IDENTIFIER_GENERAL;
                }
            }
        } else {
            /* -------- Other 3-symbols keywords don't exist -------- */
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }
    }
}

/* ---------------- 4 ----------------*/

ltoken_type_t __token_identifier_separate_4(lchar_t* id) {

    if (lstrcmp(id, (lchar_t *)(l("else")), 4) == 0) {
        /* -------- 'else' keyword -------- */
        return LENA_TOKEN_LOGIC_ELSE;
    } else if (lstrcmp(id, (lchar_t *)(l("elif")), 4) == 0) {
        /* -------- 'elif' keyword -------- */
        return LENA_TOKEN_LOGIC_ELIF;
    } else if (lstrcmp(id, (lchar_t *)(l("with")), 4) == 0) {
        /* -------- 'with' keyword -------- */
        return LENA_TOKEN_KW_WITH;
    } else {
        /* -------- Other 4-symbols keywords don't exist -------- */
        return LENA_TOKEN_IDENTIFIER_GENERAL;
    }
}

/* ---------------- 5 ----------------*/

ltoken_type_t __token_identifier_separate_5(lchar_t* id) {
    if (lstrcmp(id, (lchar_t *)(l("times")), 5) == 0) {
        /* -------- 'with' keyword -------- */
        return LENA_TOKEN_KW_TIMES;
    } else {
        /* -------- Other 5-symbols keywords don't exist -------- */
        return LENA_TOKEN_IDENTIFIER_GENERAL;
    }
}

/* ---------------- 6 ----------------*/

ltoken_type_t __token_identifier_separate_6(lchar_t* id) {
    if (lstrcmp(id, (lchar_t *)(l("repeat")), 5) == 0) {
        /* -------- 'with' keyword -------- */
        return LENA_TOKEN_KW_REPEAT;
    } else {
        /* -------- Other 6-symbols keywords don't exist -------- */
        return LENA_TOKEN_IDENTIFIER_GENERAL;
    }
}

/* ---------------- 7 ----------------*/

ltoken_type_t __token_identifier_separate_7(lchar_t* id) {
    if (lstrcmp(id, (lchar_t *)(l("repeat")), 7) == 0) {
        /* -------- 'with' keyword -------- */
        return LENA_TOKEN_KW_DEFAULT;
    } else {
        /* -------- Other 7-symbols keywords don't exist -------- */
        return LENA_TOKEN_IDENTIFIER_GENERAL;
    }
}


/* This is clear but unsecure function */
ltoken_type_t __token_identifier_separator(lchar_t* input[], size_t len) {

    lchar_t* id = (*input);

    switch (len) {
        case 2:{
            return __token_identifier_separate_2(id);
        }
        case 3:{
            return __token_identifier_separate_3(id);
        }
        case 4:{
            return __token_identifier_separate_4(id);
        }
        case 5:{  
            return __token_identifier_separate_5(id);
            break;
        }
        case 6:{
            return __token_identifier_separate_6(id);
            break;
        }
        case 7:{ 
            return __token_identifier_separate_7(id);
            break;
        }
        default:{
            /* -------- Unrecognized identifier (or user's identifier) -------- */
            return LENA_TOKEN_IDENTIFIER_GENERAL;
        }   
    }
}

/* -------- Pass used symbols -------- */
void __token_identifier_pass(lchar_t* input[], size_t len) { 
    while (len) {
        ++(*input); --len;
    }
}

void __token_identifier(lchar_t* input[], ltoken_buffer_t* buffer) {

    size_t len = __token_identifier_get_len(input);
    ltoken_type_t type = __token_identifier_separator(input, len);

    buffer->token[buffer->index].type = type;
    buffer->token[buffer->index].data = (*input);
    buffer->token[buffer->index].len = len;

    __token_identifier_pass(input, len);

}