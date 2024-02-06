
/* Standard library */
#include <stdlib.h>

#include "lmem.h"

void* lmalloc(size_t size) {
    return malloc(size);
}

void* lcalloc(size_t num, size_t size) {
    return calloc(num, size);
}

void* lrealloc(void* mem, size_t size) {
    return realloc(mem, size);
}

void* lrecalloc(void* mem, size_t num, size_t size) {
    return _recalloc(mem, num, size);
}