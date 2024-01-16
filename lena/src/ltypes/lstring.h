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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

/* Libraries */
#include "lchar.h"

/* lstring macroses */

#define LSTRING_EQUAL 0

/* IF LCHAR == WCHAR (Windows) */
#if LCHAR_MAX == WCHAR_MAX

#include <wchar.h>

#ifdef WINAPI_FAMILY_PARTITION

#undef lstrcpy
#undef lstrcat
#undef lstrcmp

#endif // undef lstr... functions


lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src, size_t len);
lchar_t* lstrcat(lchar_t* dest, const lchar_t* src);
int lstrcmp(lchar_t* str1, lchar_t* str2, size_t len);

#else

lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src, size_t len);
lchar_t* lstrcat(lchar_t* dest, const lchar_t* src);
int lstrcmp(lchar_t* str1, lchar_t* str2, size_t len);

/* Only with buffers when len % 8 = 0*/
void lstrcpy_fast(void* data1, void* data2, size_t len);

#endif
/* lstren -> llen [lchar.h]*/

#endif // __LENA_STRING_H__