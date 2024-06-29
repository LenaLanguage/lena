#ifndef LENA_COMPILER_ERRORS_ENUM_H_
#define LENA_COMPILER_ERRORS_ENUM_H_

/**************************************************************************//**
 * @file     errors.enum.h
 * @brief    Project L - Lena programming language / compiler errors enum header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* Define enum of errors in Lena */
typedef enum {
    /* No flags */
    COMPILER_ERROR_NO_INPUT_FLAGS,
    /* Incomplete sequence of flags for build */
    COMPILER_ERROR_INVALID_FLAGS_SEQUENCE_BUILD,
    
} compiler_error_t;


#endif // LENA_COMPILER_ERRORS_ENUM_H_