#ifndef __LENA_LCHAR_H__
#define __LENA_LCHAR_H__

/**************************************************************************//**
 * @file     lchar_t.h
 * @brief    Project L - Lena programming language util/lchar_t library
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* Include libraries */
#include <stdbool.h>

#ifdef _WIN32 /* WINDOWS */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wchar.h>

#define LCHAR_MAX sizeof(wchar_t)
typedef wchar_t lchar_t;
#define llen(str) wcslen(str)
#define l(data) L##data

#else /* LINUX */

#include <string.h>

#define LCHAR_MAX sizeof(char)
typedef char lchar_t;
#define llen(str) strlen(str)
#define l(data) data

#endif

/* Functions */

/**
 * @brief Determining whether a character is a digit
*/
bool is_ldigit(lchar_t sym);
/**
 * @brief Determining whether a character is a letter
*/
bool is_lletter(lchar_t sym);

#endif // __LENA_LCHAR_H__