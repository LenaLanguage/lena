/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>

/* Libraries */
#include "ltypes/lchar.h"
#include "ltypes/lerror.h"

#include "lencoder.h"

/* Functions */

/* Private */

bool _is_sep_sym(lchar_t sym) {
    return (bool)(sym == l('x') 
        || sym == l('o') 
        || sym == l('b'));
}

/* ---------------- Binary ---------------- */

static lerror_t _lencode_lchar_bin(lchar_t* input, lchar_t* restrict result) {

}

/* ---------------- Octal ---------------- */

static lerror_t _lencode_lchar_oct(lchar_t* input, lchar_t* restrict result) {

}

/* ---------------- Hexadecimal ---------------- */

static lerror_t _lencode_lchar_hex(lchar_t* input, lchar_t* restrict result) {

}

/* ---------------- Decimental ---------------- */

static lerror_t _lencode_lchar_dec(lchar_t* input, lchar_t* restrict result) {
    printf("ENCODING!:");
    /* direct recognition */
    size_t len = 0;
    while ((*input) != l('}')) {
        printf("%c", (*input));
        if (is_lnull((*input)) || !is_ldigit((*input))) {
            return LENA_ERROR;
        }
        ++input; ++len;
    }
    if (len > 3) {
        return LENA_ENCODE_ERROR_SIZE_EXCEEDED;
    }
    --input;
    lchar_t shift = 1;
    for (size_t i = 0; i < len; ++i) {
        (*result) += (shift * ((*input) - l('0')));
        --input; shift *= 10;
    }
    return LENA_OK;
}

/* Public */

lerror_t lencode_lchar(lchar_t* input, lchar_t* restrict result) {
    if (input[0] == l('0')) {
        /* Translate to the number */
        switch (input[1]) {
            /* ---------------- Binary ---------------- */
            case l('b'): {
                return _lencode_lchar_bin(input, result);
            }
            /* ---------------- Octal ---------------- */
            case l('o'): {
                return _lencode_lchar_oct(input, result);
            }
            /* ------------- Hexadecimal ------------- */
            case l('x'): {
                return _lencode_lchar_hex(input, result);
            }
            default: {
                return LENA_ENCODE_ERROR_INVALID_SEP;
            }
        }
    } else {
        /* ---------------- Decimal ---------------- */
        return _lencode_lchar_dec(input, result);
    }
}
