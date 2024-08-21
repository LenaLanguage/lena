#ifndef LENA_COMPILER_ERRORS_H_
#define LENA_COMPILER_ERRORS_H_

/**************************************************************************//**
 * @file     errors.h
 * @brief    Project L - Lena programming language / compiler files '.le' header
 * @version  V0.4.0
 * @date     18. August 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>

/* .le files error codes and labels */

/* ------------------ Error limits ------------------ */

/* --------- Launch errors --------- */

/* Files errors */
#define LE_ERROR_FILES_BEGIN 1
#define LE_ERROR_FILES_END

/* Args errors */
#define LE_ERROR_ARGS_BEGIN (LE_ERROR_FILES_END + 1)
#define LE_ERROR_ARGS_END

/* --------- Compilation errors --------- */

/* Syntax errors */
#define LE_ERROR_SYNTAX_BEGIN (LE_ERROR_ARGS_END + 1)
#define LE_ERROR_SYNTAX_END

typedef enum {

    /* --------- Launch errors --------- */

    /* Files errors */

    LE_ERROR_F_NO_INPUT             = 0 + LE_ERROR_FILES_BEGIN,
    LE_ERROR_F_INVALID_INPUT        = 1 + LE_ERROR_FILES_BEGIN,
    LE_ERROR_F_INVALID_OUT_EXEC     = 2 + LE_ERROR_FILES_BEGIN,
    LE_ERROR_F_INVALID_OUT_NA       = 3 + LE_ERROR_FILES_BEGIN,

    /* Args errors */

    LE_ERROR_A_INVALID_SEQ  = 0 + LE_ERROR_ARGS_BEGIN,

    /* --------- Compilation errors ---------*/
    
    /* Sequences */
    /* Unfinished constructions like [] {} () "" '' and etc "*/
    LE_ERROR_S_INVALID_END_STR = 0

} compiler_errors_t;

/** 
 * @brief Prints certain compilation error
 * 
 * @param[in] index index of the error
 * @param[in] locs number of lines of code variables
*/
extern void compiler_error_print(compiler_errors_t index, lu64* locs);

#endif // LENA_COMPILER_ERRORS_H_