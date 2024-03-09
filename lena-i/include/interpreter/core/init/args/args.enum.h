#ifndef LENA_INTERPRETER_CORE_INIT_ARGS_ENUM_H_
#define LENA_INTERPRETER_CORE_INIT_ARGS_ENUM_H_

/**************************************************************************//**
 * @file     args.h
 * @brief    Project L - Lena programming language interpreter / core / init / args enum
 * @version  V0.0.1
 * @date     29. Feb 2024
 * @author   Matvey Rybalkin
******************************************************************************/

typedef enum {
    LENA_I_FLAG_HELP,
    LENA_I_FLAG_VERSION,
    LENA_I_FLAG_LICENSE,
    LENA_I_FLAG_VERBOSE,
    LENA_I_FLAG_QUIET,
    LENA_I_FLAG_CONFIG,
    LENA_I_FLAG_OUTPUT,
    LENA_I_FLAG_FORCE,
    LENA_I_FLAG_DRY_RUN,
    LENA_I_FLAG_INTERACTIVE,
} args_list_t;

#endif // LENA_INTERPRETER_CORE_INIT_ARGS_ENUM_H_