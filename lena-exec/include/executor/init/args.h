#ifndef PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__
#define PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__

/**************************************************************************//**
 * @file     args.h
 * @brief    Project L - Lena programming language executor / init / args.h
 * @version  V0.0.1
 * @date     27. Mar 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include executor libraries */
#include "executor/exec.h"

typedef enum {

    /* Recognized tokens */
    TOKEN_HELP,     // --help
    TOKEN_VERSION,  // --version
    TOKEN_LICENSE,  // --license

    /* Unrecognized tokens */
    TOKEN_FILE,     // "file.x"

} args_token_t;

#endif // PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__