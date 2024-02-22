#ifndef __LENA_TYPES_LCHAR_H__
#define __LENA_TYPES_LCHAR_H__

/**************************************************************************//**
 * @file     lnchar_t.h
 * @brief    Project L - Lena programming language util/lnchar_t library
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* from llibs framework */

/* Include libraries */
#include <stdbool.h>
#include <stdint.h>

/* Types for different UTF */
typedef uint32_t lchar32_t;
typedef uint16_t lchar16_t;
typedef uint8_t  lchar8_t;

/* General type (Using UTF-8) */
typedef lchar8_t lchar_t;

#ifdef _WIN32 /* WINDOWS */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wchar.h>

#define LCHAR_MAX WCHAR_MAX
typedef wchar_t lnchar_t;
#define llen(str) wcslen(str)
#define l(data) L##data

#else /* LINUX */

#include <string.h>

#define LCHAR_MAX INT8_MAX
typedef lchar8_t lnchar_t;
#define llen(str) strlen(str)
#define l(data) data

#endif

/* Functions */

/**
 * @brief Determining whether a character is a digit
*/
extern bool is_ldigit(lnchar_t sym);
/**
 * @brief Determining whether a character is a letter
*/
extern bool is_lletter(lnchar_t sym);

/**
 * @brief Determining whether a character is a null '\0'
*/
extern bool is_lnull(lnchar_t sym);

/**
 * @brief Calculating lenght of the string
*/
extern size_t llen(lnchar_t* sym);

#endif // __LENA_TYPES_LCHAR_H__