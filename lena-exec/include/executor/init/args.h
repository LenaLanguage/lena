#ifndef PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__
#define PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__

/**************************************************************************//**
 * @file     args.h
 * @brief    Project L - Lena programming language executor / init / args.h
 * @version  V0.0.1
 * @date     27. Mar 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>

/**
 * @brief Args token list.
 * 
 * `TOKEN_XX` - argument with `--`
 * `TOKEN_X` - argument with `-`
 * `TOKEN_` - argument without prefix
*/
typedef enum {

    /* Recognized tokens */
    TOKEN_XX_HELP,     // `--help`
    TOKEN_XX_VERSION,  // `--version`
    TOKEN_XX_LICENSE,  // `--license`

    TOKEN_X_COLOR_TRUE,     // `-color=true`
    TOKEN_X_COLOR_FALSE,    // `-color=false`

    /* Unrecognized tokens */
    TOKEN_FILE,     // `"file.x"`

    /* Invalid tokens */
    TOKEN_INVALID,

} args_token_t;

/**
 * @brief Recognize input arguments for Lena executor.
*/
extern args_token_t args_token_recognize(lc* arg);

#endif // PRIVATE_LENA_EXECUTOR_INIT_ARGS_H__