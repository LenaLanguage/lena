#ifndef __LENA_ERRNO_H__
#define __LENA_ERRNO_H__

/**************************************************************************//**
 * @file     lerrno.h
 * @brief    Project L - Lena programming language lerrno
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Configuration file must be included before */
#ifndef __LENA_MAIN_CONF_H__
#error [lerrno.h]: lconfig.h was not included
#else

/* Error function type */
typedef void lerror_func_t;
typedef uint32_t lerror_index_t;

/* List of errors */
typedef enum {
    LENA_ERROR_NO_ARGS                = 0x0000000000000000,
    LENA_ERROR_NO_INPUT_FILES         = 0x0000000000000001,
    LENA_ERROR_FLAG_DOES_NOT_EXIST    = 0x0000000000000002,
    LENA_ERROR_OPEN_FILE_ERROR        = 0x0000000000000003,
} lerrno_t;

/* Buffer for error list */
lerrno_t lerror_buffer[LMXEBL];
lerror_index_t lerror_index = 0;

#endif
#endif // __LENA_ERRNO_H__