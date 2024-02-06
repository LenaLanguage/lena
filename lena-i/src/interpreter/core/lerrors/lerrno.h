#ifndef __LENA_CORE_ERRNO_H__
#define __LENA_CORE_ERRNO_H__

/**************************************************************************//**
 * @file     lerrno.h
 * @brief    Project L - Lena programming language lerrno
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdint.h>

/* Libraries */
#include "../lconfig/lconf_errors.h"

/* Error function type */
typedef void lerror_func_t;
typedef uint32_t lerror_index_t;

/* List of errors */
typedef enum {
    LENA_I_ERROR_NO_ARGS                = 0x0000000000000000,
    LENA_I_ERROR_NO_INPUT_FILES         = 0x0000000000000001,
    LENA_I_ERROR_FLAG_DOES_NOT_EXIST    = 0x0000000000000002,
    LENA_I_ERROR_OPEN_FILE_ERROR        = 0x0000000000000003,
} lerrno_t;

/* Buffer for error list */
extern lerrno_t lerror_buffer[LCMXEBL];
extern lerror_index_t lerror_index;

#endif // __LENA_CORE_ERRNO_H__