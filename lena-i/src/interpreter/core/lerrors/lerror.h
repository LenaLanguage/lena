#ifndef __LENA_CORE_ERROR_H__
#define __LENA_CORE_ERROR_H__

/**************************************************************************//**
 * @file     lerror.h
 * @brief    Project L - Lena programming language lerror
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* ERRNO list */
#include "lerrno.h"

#define LENA_ERROR(index, func, ...)    func(__VA_ARGS__);\
                                        lerror_buffer[lerror_index] = index;\
                                        lerror_index += 1;

#endif // __LENA_CORE_ERROR_H__