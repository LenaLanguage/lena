#ifndef LENA_COMPILER_INFO_H_
#define LENA_COMPILER_INFO_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     error.enum.h
 * @brief    Project L - Lena programming language / compiler information header
 * @version  V0.4.0
 * @date     30. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* Lena's version */
#define LENA_VERSION 40UL
#define LENA_VERSION_STR X("0.4.0")

/* Prints current Lena's version */
extern void version(void);

/* Prints full Lena's version information */
extern void version_extented(void);

/* Prints Lena's license */
extern void license(void);

/* Prints help message */
extern void help(void);

#endif // LENA_COMPILER_INFO_H_