#ifndef __LENA_CORE_ARGS_H__
#define __LENA_CORE_ARGS_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language args library
 * @version  V0.0.1
 * @date     17. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdint.h>

/* Libraries */

/* core */
#include "largsno.h"

/* non-core */
#include "ltypes/ltypes.h"
#include "lconsole/lconsole.h"

/* Finders for different arguments */

/* Double hyphen */
extern void lena_args_dh(lnchar_t argv[]);

/* Single hyphen */
extern void lena_args_sh(lnchar_t argv[]);

/* Simple arg */
extern void lena_args_sa(lnchar_t argv[]);

bool core_args_exist(int argc);
void core_args_receiver(int argc, lnchar_t* argv[]);

/* DH SA SH funcitons (--args -args args) */

#endif // __LENA_CORE_ARGS_H__