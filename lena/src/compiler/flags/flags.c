/* Include general file Llibs framework */
#include <llibs.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>

/* Flags buffer */
static lc8* flags_buffer[] = {
    [COMPILER_FLAG_D_VERSION] = X("-v"),
    [COMPILER_FLAG_D_VERSION] = X("-v"),
};

compiler_flag_t flags_recognize(lc8* str) {
    /* Check every available flag */
    for (lu8 i = 0; i <= COMPILER_FLAG_MAX; ++i) {
        if (lscmp(str, flags_buffer[i])) {
            return (compiler_flag_t)(i);
        }
    }
    return COMPILER_FLAG_UNRECOGNIZED;
}

lbool is_building_flag(compiler_flag_t flag) {
    return (lbool)(COMPILER_FLAG_D_OUT || COMPILER_FLAG_UNRECOGNIZED);
}