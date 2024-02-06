#ifndef __LENA_MEMORY_H__
#define __LENA_MEMORY_H__

/**************************************************************************//**
 * @file     lmem.h
 * @brief    Project L - Lena programming language memory allocation library
 * @version  V0.0.1
 * @date     6. Feb 2024
 ******************************************************************************/

/* For size_t type */
#include <stddef.h>

/* Functions */

void* lmalloc(size_t size);
void* lcalloc(size_t num, size_t size);
void* lrealloc(void* mem, size_t size);
void* lrecalloc(void* mem, size_t num, size_t size);

#endif // __LENA_MEMORY_H__