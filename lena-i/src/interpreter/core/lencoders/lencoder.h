#ifndef __LENA_CORE_ENCODER_H__
#define __LENA_CORE_ENCODER_H__

/**************************************************************************//**
 * @file     lconverter.h
 * @brief    Project L - Lena programming language lconverter
 * @version  V0.0.1
 * @date     9. Feb 2024
 ******************************************************************************/

/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>

/* Libraries */
#include "ltypes/lchar.h"
#include "ltypes/lerror.h"

enum lencode_error_codes {
    LENA_ENCODE_ERROR_INVALID_SEP   = 0x02,
    LENA_ENCODE_ERROR_SIZE_EXCEEDED = 0x03,

    LENA_ENCODE_SUCCESS_BIN = 0x04,
    LENA_ENCODE_SUCCESS_OCT = 0x05,
    LENA_ENCODE_SUCCESS_DEC = 0x06,
    LENA_ENCODE_SUCCESS_HEX = 0x07,
};

/* Functions */

/* Temporary solution for tokenizer.c */

/* For encoding different types of number: 0x00 0b00 0o00 */
extern lerror_t lencode_lchar(lchar_t* input, lchar_t* restrict result, size_t* restrict len);

#endif // __LENA_CORE_ENCODER_H__