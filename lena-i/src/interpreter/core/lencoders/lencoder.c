/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>

/* Libraries */
#include "ltypes/lchar.h"
#include "ltypes/lerror.h"

#include "lencoder.h"

/* Functions */

/* Private */

static int64_t _binpow(int64_t a, int64_t n) {
    int64_t res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

/* ---------------- Binary ---------------- */

static inline bool _is_bin_sym(lchar_t sym) {
    return (bool)((sym == l('0') || sym == l('1')));
}

static lerror_t _lencode_lchar_bin(lchar_t* input, lchar_t* restrict result, size_t* restrict len) {
    /* pass '0b' */
    input += 2;
    while (_is_bin_sym(*input)) {
        ++input; ++(*len);
    }
    if ((*len) > 8) {
        return LENA_ENCODE_ERROR_SIZE_EXCEEDED;
    }
    --input;
    for (size_t i = 0; i < (*len); ++i) {
        (*result) = (~(1 << i) & (*result))|((bool)((*input) - l('0')) << i);
        --input;
    }
    input += (*len) + 1;
    return LENA_ENCODE_SUCCESS_BIN;
}

/* ---------------- Octal ---------------- */

static inline bool _is_oct_sym(lchar_t sym) {
    return (bool)(sym >= l('0') && sym <= l('7'));
}

static lerror_t _lencode_lchar_oct(lchar_t* input, lchar_t* restrict result, size_t* restrict len) {
    /* pass '0o' */
    input += 2;
    while (_is_oct_sym(*input)) {
        ++input; ++(*len);
    }
    if ((*len) > 3) {
        return LENA_ENCODE_ERROR_SIZE_EXCEEDED;
    }
    --input;
    lchar_t shift = 0;
    for (size_t i = 0; i < (*len); ++i) {
        (*result) += (((*input) - l('0')) * _binpow(8, shift));
        --input;
    }
    input += (*len) + 1;
    return LENA_ENCODE_SUCCESS_OCT;
}

/* ---------------- Hexadecimal ---------------- */

static inline bool _is_hex_sym(lchar_t sym) {
    return (bool)((sym >= l('0') && sym <= l('9')) 
        || (sym >= l('A') && sym <= l('F'))
        || (sym >= l('a') && sym <= l('f')));
}

static inline uint8_t _get_hex_value(lchar_t sym) {
    if (sym >= l('0') && sym <= l('9')) {
        return (sym - l('0'));
    } else if ((sym >= l('A') && sym <= l('F'))) {
        return (sym - l('A')) + 10;
    } else if ((sym >= l('a') && sym <= l('f'))) {
        return (sym - l('a')) + 10;
    }
    return 0;
}

static lerror_t _lencode_lchar_hex(lchar_t* input, lchar_t* restrict result, size_t* restrict len) {
    /* pass '0x' */
    input += 2;
    while (_is_hex_sym(*input)) {
        ++input; ++(*len);
    }
    if ((*len) > 2) {
        return LENA_ENCODE_ERROR_SIZE_EXCEEDED;
    }
    --input;
    lchar_t shift = 0;
    for (size_t i = 0; i < (*len); ++i) {
        (*result) += (_get_hex_value((*input)) * _binpow(16, shift));
        --input; ++shift;
    }
    input += (*len) + 1;
    return LENA_ENCODE_SUCCESS_HEX;
}

/* ---------------- Decimental ---------------- */

static inline bool _is_dec_sym(lchar_t sym) {
    return (is_ldigit(sym));
}

static lerror_t _lencode_lchar_dec(lchar_t* input, lchar_t* restrict result, size_t* restrict len) {
    /* direct recognition */
    while (_is_dec_sym((*input))) {
        ++input; ++(*len);
    }
    if ((*len) > 3) {
        return LENA_ENCODE_ERROR_SIZE_EXCEEDED;
    }
    --input;
    lchar_t shift = 1;
    for (size_t i = 0; i < (*len); ++i) {
        (*result) += (shift * ((*input) - l('0')));
        --input; shift *= 10;
    }
    input += (*len) + 1;
    return LENA_ENCODE_SUCCESS_DEC;
}

/* Public */

lerror_t lencode_lchar(lchar_t* input, lchar_t* restrict result, size_t* restrict len) {
    if (input[0] == l('0')) {
        /* Translate to the number */
        switch (input[1]) {
            /* ---------------- Binary ---------------- */
            case l('b'): {
                return _lencode_lchar_bin(input, result, len);
            }
            /* ---------------- Octal ---------------- */
            case l('o'): {
                return _lencode_lchar_oct(input, result, len);
            }
            /* ------------- Hexadecimal ------------- */
            case l('x'): {
                return _lencode_lchar_hex(input, result, len);
            }
            default: {
                return LENA_ENCODE_ERROR_INVALID_SEP;
            }
        }
    } else {
        /* ---------------- Decimal ---------------- */
        return _lencode_lchar_dec(input, result, len);
    }
}
