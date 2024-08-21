#ifndef LENA_COMPILER_INFO_H_
#define LENA_COMPILER_INFO_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     info.h
 * @brief    Project L - Lena programming language / compiler information header
 * @version  V0.4.0
 * @date     30. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>
#include <lingua.h>

/* Lena's version */
#define LENA_VERSION 40UL
#define LENA_VERSION_STR X("0.4.0")

/* Build information */
#define LENA_C_COMPILER_STR X("GCC")

/* Build information is stored in macros: LENA_BUILD_OS_STR, LENA_BUILD_ARCH_STR */
// Chech JavaScript...
#if !defined(LENA_BUILD_OS_STR) || !defined(LENA_BUILD_ARCH_STR) || !defined(LENA_BUILD_TIME_STR)
#error [info.h]: OS, ARCH and TIME are not defined!
#endif

/* Prints current Lena's version */
extern void version(void);

/* Prints full Lena's version information */
extern void version_extented(void);

/* Prints Lena's license */
extern void license(void);

/* Prints help message */
extern void help(void);

/* Additional help_ functions */
extern void help_about(void);
extern void help_formats(void);
extern void help_flags(void);
extern void help_usage(void);
extern void help_about_she(void);

#endif // LENA_COMPILER_INFO_H_