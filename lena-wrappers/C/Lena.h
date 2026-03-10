#ifndef LENA_WRAPPER_H_
#define LENA_WRAPPER_H_

#include <stdint.h>
#include <stdbool.h>

typedef bool lena_bool;

typedef uint8_t  lena_u8;
typedef int8_t   lena_i8;
typedef uint16_t lena_u16;
typedef int16_t  lena_i16;
typedef uint32_t lena_u32;
typedef int32_t  lena_i32;
typedef uint64_t lena_u64;
typedef int64_t  lena_i64;

typedef float   lena_f32;
typedef double  lena_f64;

typedef struct {
    char* ptr;
    lena_u64 len;
} lena_str;

typedef enum {
    LENA_BOOL_TYPE,
    LENA_U8_TYPE,
    LENA_I8_TYPE,
    LENA_U16_TYPE,
    LENA_I16_TYPE,
    LENA_U32_TYPE,
    LENA_I32_TYPE,
    LENA_U64_TYPE,
    LENA_I64_TYPE,
    LENA_F32_TYPE,
    LENA_F64_TYPE,
    LENA_CHAR_TYPE,
} lena_array_elem_type;

typedef struct {
    void* ptr;
    lena_array_elem_type elem_type;
    lena_u64 len;
    lena_u64 capacity;
} lena_array;

static inline size_t lena_type_size(lena_array_elem_type type) {
    switch(type) {
        case LENA_U8_TYPE:  return 1;
        case LENA_I8_TYPE:  return 1;
        case LENA_U16_TYPE: return 2;
        case LENA_I16_TYPE: return 2;
        case LENA_I32_TYPE: return 4;
        case LENA_U32_TYPE: return 4;
        case LENA_I64_TYPE: return 8;
        case LENA_U64_TYPE: return 8;
        case LENA_F32_TYPE: return 4;
        case LENA_F64_TYPE: return 8;
        case LENA_BOOL_TYPE: return 1;
        default: return 0;
    }
}

#endif // LENA_WRAPPER_H_