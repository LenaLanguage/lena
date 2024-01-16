

/* Standard libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "lchar.h"
#include "lstring.h"

/* IF LCHAR == WCHAR (Windows) */
#if LCHAR_MAX == WCHAR_MAX

#include <wchar.h>

#ifdef WINAPI_FAMILY_PARTITION

#undef lstrcpy
#undef lstrcat
#undef lstrcmp

#endif // undef lstr... functions


lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src, size_t len){
    return memcpy(dest, src, len * sizeof(lchar_t));
}

lchar_t* lstrcat(lchar_t* dest, const lchar_t* src){
    return wcscat(dest, src);
}

int lstrcmp(lchar_t* str1, lchar_t* str2, size_t len){
    return memcmp(str1, str2, len * sizeof(lchar_t));
}

#else

lchar_t* lstrcpy(lchar_t* dest, const lchar_t* src, size_t len){
    return memcpy(dest, src, len * sizeof(lchar_t));
}

lchar_t* lstrcat(lchar_t* dest, const lchar_t* src){
    return strcat(dest, src);
}

int lstrcmp(lchar_t* str1, lchar_t* str2, size_t len){
    return memcmp(str1, str2, len * sizeof(lchar_t));
}

/* Only with buffers when len % 8 = 0*/
void lstrcpy_fast(void* data1, void* data2, size_t len) {
    len /= 8;
    size_t shift = 0;
    for (uint64_t i = 0; i < len; ++i) {
        (*(int64_t*)(data1 + shift)) = (int64_t)(int64_t*)(data2 + shift);
        shift += 8;
    }
}
#endif
/* lstren -> llen [lchar.h]*/