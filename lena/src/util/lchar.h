#ifndef __LENA_LCHAR_H__
#define __LENA_LCHAR_H__

/**************************************************************************//**
 * @file     lchar.h
 * @brief    Project L - Lena programming language util/lchar library
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/


#ifdef _WIN32 /* WINDOWS */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wchar.h>

typedef wchar_t lchar;
#define llen(str) wcslen(str)
#define l(data) L##data

#else /* UNIX */

#include <string.h>

typedef char lchar;
#define llen(str) strlen(str)
#define l(data) data

#endif

#endif // __LENA_LCHAR_H__