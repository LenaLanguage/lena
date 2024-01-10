#ifndef __LENA_ERROR_H__
#define __LENA_ERROR_H__

/**************************************************************************//**
 * @file     lerror.h
 * @brief    Project L - Lena programming language lerror
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include "lerrno.h"

#define LENA_ERROR(index, func, ...) func(__VA_ARGS__)

#endif // __LENA_ERROR_H__