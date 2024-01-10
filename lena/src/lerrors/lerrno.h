#ifndef __LENA_ERRNO_H__
#define __LENA_ERRNO_H__

/**************************************************************************//**
 * @file     lerrno.h
 * @brief    Project L - Lena programming language lerrno
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

typedef void lerror_func_t;

typedef enum {
    LENA_NO_ARGS        = 0x00,
    LENA_NO_INPUT_FILES = 0x01,
} errno_t;

#endif // __LENA_ERRNO_H__