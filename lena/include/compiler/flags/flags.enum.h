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

    COMPILER_FLAG_DD_NON_ABSTRACT,

    /* Compiler filenames */
    COMPILER_FLAG_FILENAME_E,   // "app.e"
    COMPILER_FLAG_FILENAME_EXE, // "app.exe"
    COMPILER_FLAG_FILENAME_LE,  // "app.le"
    COMPILER_FLAG_FILENAME,     // empty file format like "app"

    COMPILER_FLAG_FILENAME_OTHER, // unrecognized file formats...

    COMPILER_FLAG_UNRECOGNIZED,
} compiler_flag_t;

/* The last available flag with single dash */
#define COMPILER_D_FLAG_MAX COMPILER_FLAG_D_OUT

/* The last available flag with double dash */
#define COMPILER_DD_FLAG_MAX COMPILER_FLAG_DD_NON_ABSTRACT

/* Is filename macros */
#define COMPILER_IS_FILENAME(file) (file >= COMPILER_FLAG_FILENAME_E && file <= COMPILER_FLAG_FILENAME)

#endif // LENA_COMPILER_FLAGS_ENUM_H_