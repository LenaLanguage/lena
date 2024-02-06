#ifndef __LENA_TYPES_ERROR_H__
#define __LENA_TYPES_ERROR_H__

/**************************************************************************//**
 * @file     lerror.h
 * @brief    Project L - Lena programming language lerror/general
 * @version  V0.0.1
 * @date     6. Feb 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdint.h>

/* Type */
typedef uint8_t lerror_t;

typedef enum {
    LENA_OK = 1,
    LENA_ERROR = 0,
    // ... other codes
} lerror_codes_t;

#endif // __LENA_TYPES_ERROR_H__