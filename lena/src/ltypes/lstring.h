#ifndef __LENA_STRING_H__
#define __LENA_STRING_H__

/**************************************************************************//**
 * @file     lstring.h
 * @brief    Project L - Lena programming language ltypes/strings
 * @version  V0.0.2
 * @date     9. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* lstring_t type */

typedef struct {
    lchar_t* data;
    size_t size;
} lstring_t;


#endif // __LENA_STRING_H__