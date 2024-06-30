#ifndef LENA_H_
#define LENA_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     lena.h
 * @brief    Project L - Lena programming language / main header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Check C standard */
#if __STDC_VERSION__  >= 201112L

/* Include llibs framework (external) */
#include <llibs.h>

/* Main function */
extern lm compile(lu32 argc, lc* argv[]);

#else /* ERROR (__STDC_VERSION__ >= 201112L) */
#error [lena.h]: Requires at least version C 2011 (__STDC_VERSION__ >= 201112L)
#endif 

#endif // LENA_H_