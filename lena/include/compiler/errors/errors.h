#ifndef LENA_COMPILER_ERRORS_H_
#define LENA_COMPILER_ERRORS_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     error.enum.h
 * @brief    Project L - Lena programming language / compiler errors header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* General greeting function, prints "[Lena]: " */
extern void greeting(void);

/* Extended greeting function, prints "[Lena][str]: " */
extern void greeting_extended(const lc* str);

#endif // LENA_COMPILER_ERRORS_H_