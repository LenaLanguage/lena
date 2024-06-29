#ifndef LENA_COMPILER_FLAGS_ENUM_H_
#define LENA_COMPILER_FLAGS_ENUM_H_

/**************************************************************************//**
 * @file     flags.enum.h
 * @brief    Project L - Lena programming language / compiler flags enum header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* Define enum of flags to compile file in Lena */
typedef enum {
    /* flags with prefix "-" */
    COMPILER_FLAG_D_VERSION,
    COMPILER_FLAG_D_OUT,
    /* flags with prefix "--" */
    COMPILER_FLAG_DD_VERSION,
    COMPILER_FLAG_DD_HELP,
    COMPILER_FLAG_DD_LICENSE,
    COMPILER_FLAG_UNRECOGNIZED = 0xFF,
} compiler_flag_t;

/* The last available flag except COMPILER_FLAG_UNRECOGNIZED */
#define COMPILER_FLAG_MAX COMPILER_FLAG_DD_LICENSE

#endif // LENA_COMPILER_FLAGS_ENUM_H_