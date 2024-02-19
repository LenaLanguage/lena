

/* Standard libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

/* Libraries */
#include "lchar.h"
#include "lstring.h"

/* IF LCHAR == WCHAR (Windows) */
#if LCHAR_MAX == WCHAR_MAX

#include <wchar.h>

/* Undef WinAPI functions */
#ifdef WINAPI_FAMILY_PARTITION

#undef lstrcpy
#undef lstrcat
#undef lstrcmp

#endif // undef lstr... functions

/* And define Lena API funcrions */

lnchar_t* lstrcpy(lnchar_t* dest, const lnchar_t* src, size_t len){
    return memcpy(dest, src, len * sizeof(lnchar_t));
}

lnchar_t* lstrcat(lnchar_t* dest, const lnchar_t* src){
    return wcscat(dest, src);
}

int lstrcmp(lnchar_t* str1, lnchar_t* str2, size_t len){
    return memcmp(str1, str2, len * sizeof(lnchar_t));
}

/* -------- Experimental functions -------- */

typedef uint64_t lstring_x4_t;
typedef uint32_t lstring_x2_t;
typedef uint16_t lstring_x1_t;

#define LSTRING_4_CMP(data) (*(lstring_x4_t*)(data))
#define LSTRING_2_CMP(data) (*(lstring_x2_t*)(data))
#define LSTRING_1_CMP(data) (*(lstring_x1_t*)(data))

bool lstrcmp_x64_8(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_4_CMP(str1) == LSTRING_4_CMP(str2)
        && LSTRING_4_CMP(str1 + 8) == LSTRING_4_CMP(str2 + 8));
}

bool lstrcmp_x64_4(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_4_CMP(str1) == LSTRING_4_CMP(str2));
}

bool lstrcmp_x64_2(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_2_CMP(str1) == LSTRING_2_CMP(str2));
}

bool lstrcmp_x64_1(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_1_CMP(str1) == LSTRING_1_CMP(str2));
}

#else

lnchar_t* lstrcpy(lnchar_t* dest, const lnchar_t* src, size_t len){
    return memcpy(dest, src, len * sizeof(lnchar_t));
}

lnchar_t* lstrcat(lnchar_t* dest, const lnchar_t* src){
    return strcat(dest, src);
}

int lstrcmp(lnchar_t* str1, lnchar_t* str2, size_t len){
    return memcmp(str1, str2, len * sizeof(lnchar_t));
}

/* -------- Experimental functions -------- */

typedef uint64_t lstring_x8_t;
typedef uint32_t lstring_x4_t;
typedef uint16_t lstring_x2_t;
typedef uint8_t lstring_x1_t;

#define LSTRING_8_CMP(data) (*(lstring_x4_t*)(data))
#define LSTRING_4_CMP(data) (*(lstring_x4_t*)(data))
#define LSTRING_2_CMP(data) (*(lstring_x2_t*)(data))
#define LSTRING_1_CMP(data) (*(lstring_x1_t*)(data))

bool lstrcmp_x64_8(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_8_CMP(str1) == LSTRING_8_CMP(str2));
}

bool lstrcmp_x64_4(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_4_CMP(str1) == LSTRING_4_CMP(str2));
}

bool lstrcmp_x64_2(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_2_CMP(str1) == LSTRING_2_CMP(str2));
}

bool lstrcmp_x64_1(lnchar_t* str1, lnchar_t* str2) {
    return (bool)(LSTRING_1_CMP(str1) == LSTRING_1_CMP(str2));
}

#endif
