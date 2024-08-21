#ifndef LENA_COMPILER_MESSAGES_H_
#define LENA_COMPILER_MESSAGES_H_

/**************************************************************************//**
 * @file     errors.h
 * @brief    Project L - Lena programming language / compiler files '.le' header
 * @version  V0.4.0
 * @date     18. August 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>


/* General greeting function, prints "[Lena]: " */
extern void greeting(void);

/* Extended greeting function, prints "[Lena][str]: " */
extern void greeting_extended(const lc* str);


#endif // LENA_COMPILER_MESSAGES_H_