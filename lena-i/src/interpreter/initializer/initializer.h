#ifndef __LENA_INTERPRETER_INITIALIZER_H__
#define __LENA_INTERPRETER_INITIALIZER_H__

/**************************************************************************//**
 * @file     initializer.h
 * @brief    Project L - Lena programming language main initializer library
 * @version  V0.0.1
 * @date     21. Jan 2024
 ******************************************************************************/

/* Libraries */

/* non-core */
#include "ltypes/lchar.h"

/* core */
#include "../core/largs/largs.h"

/* Double hyphen */
void lena_args_dh(lchar_t argv[]);

/* Single hyphen */
void lena_args_sh(lchar_t argv[]);

/* Simple arg */
void lena_args_sa(lchar_t argv[]);

#endif // __LENA_INTERPRETER_INITIALIZER_H__