#ifndef LENA_INTEPRETER_MAIN_H_
#define LENA_INTEPRETER_MAIN_H_

/**************************************************************************//**
 * @file     lena-i.h
 * @brief    Project L - Lena programming language interpreter / main library
 * @version  V0.3.0
 * @date     5. Jan 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Check C standard */
#if __STDC_VERSION__  >= 201112L

/* Include llibs framework (external) */
#include <llibs.h>

/* Inlucde main interpreter library */
#include "interpreter/interpreter.h"

#else /* ERROR (__STDC_VERSION__ >= 201112L) */
#error [lena-i.h]: Requires at least version C 2011 (__STDC_VERSION__ >= 201112L)
#endif
#endif // LENA_INTEPRETER_MAIN_H_