#ifndef __LENA_TYPES_STRING_H__
#define __LENA_TYPES_STRING_H__

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

/* -------- Functions -------- */

extern lnchar_t* lstrcpy(lnchar_t* dest, const lnchar_t* src, size_t len);
extern lnchar_t* lstrcat(lnchar_t* dest, const lnchar_t* src);
extern int lstrcmp(lnchar_t* str1, lnchar_t* str2, size_t len);

/* -------- Experimental functions -------- */

extern bool lstrcmp_x64_8(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_4(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_2(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_1(lnchar_t* str1, lnchar_t* str2);

#else

/* -------- Functions -------- */

extern lnchar_t* lstrcpy(lnchar_t* dest, const lnchar_t* src, size_t len);
extern lnchar_t* lstrcat(lnchar_t* dest, const lnchar_t* src);
extern int lstrcmp(lnchar_t* str1, lnchar_t* str2, size_t len);

/* -------- Experimental functions -------- */

extern bool lstrcmp_x64_8(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_4(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_2(lnchar_t* str1, lnchar_t* str2);
extern bool lstrcmp_x64_1(lnchar_t* str1, lnchar_t* str2);


#endif

#endif // __LENA_TYPES_STRING_H__
