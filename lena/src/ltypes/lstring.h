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

/* lstring macroses */

#define LSTRING_EQUAL 0

/* IF LCHAR == WCHAR (Windows) */
#if LCHAR_MAX == WCHAR_MAX

#include <wchar.h>

lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src){
    return wcscpy(dest, src);
}

lchar_t* lstrcat(lchar_t* dest, const lchar_t* src){
    return wcscat(dest, src);
}

int lstrcmp(lchar_t* str1, lchar_t* str2){
    return wcscmp(str1, str2);
}

#else

lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src){
    return strcpy(dest, src);
}

lchar_t* lstrcat(lchar_t* dest, const lchar_t* src){
    return strcat(dest, src);
}

int lstrcmp(lchar_t* str1, lchar_t* str2){
    return strcmp(str1, str2);
}

#endif

/* lstren -> llen [lchar.h]*/

#endif // __LENA_STRING_H__