/* Include general file Llibs framework */
#include <llibs.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>

/* Flags buffer */
static lc* flags_buffer[] = {

    /* Single dash */
    [COMPILER_FLAG_D_VERSION]       = X("v"),
    [COMPILER_FLAG_D_OUT]           = X("o"),

    /* Double dash */
    [COMPILER_FLAG_DD_VERSION]      = X("version"),
    [COMPILER_FLAG_DD_HELP]         = X("help"),
    [COMPILER_FLAG_DD_LICENSE]      = X("license"),
    [COMPILER_FLAG_DD_NON_ABSTRACT] = X("non-abstract"),

};

/* Private function */
lbool is_postfix(lc* str, const lc* postfix) {
    lsz postfix_size = lssize(postfix),
    str_len = lslen(str);
    /* Check their lenght */
    if (str_len <= lslen(postfix)) {
        return false;
    }
    return lscmp(str + lssizen(str, str_len - postfix_size), postfix);
}

/* Unsafe function */
compiler_flag_t flags_recognize(lc* str) {
    if (str[0] == '-') {
        if (str[1] == '-') {
            /* Check every available flag double dasg flag */
            for (lu8 i = COMPILER_D_FLAG_MAX + 1; 
                i <= COMPILER_DD_FLAG_MAX; ++i) {
                /* (str + 2) pass two symbols "--" */
                if (lscmp(str + 2, flags_buffer[i])) {
                    return (compiler_flag_t)(i);
                }
            }
        } else {
            /* Check every available flag single dasg flag */
            for (lu8 i = 0; i <= COMPILER_D_FLAG_MAX; ++i) {
                /* (str + 1) pass first symbol "-" */
                if (lscmp(str + 1, flags_buffer[i])) {
                    return (compiler_flag_t)(i);
                }
            }
        }
    } else {
        /* It doesn't have any prefix */
        /* Check file formats ".le" ".exe" ".e" (postfix) */
        if (is_postfix(str, X(".e"))) {
            return COMPILER_FLAG_FILENAME_E;
        }
        if (is_postfix(str, X(".le"))) {
            return COMPILER_FLAG_FILENAME_LE;
        }
        if (is_postfix(str, X(".exe"))) {
            return COMPILER_FLAG_FILENAME_EXE;
        }
    }
    return COMPILER_FLAG_UNRECOGNIZED;
}

lbool is_building_flag(compiler_flag_t flag) {
    return (lbool)(COMPILER_FLAG_D_OUT || COMPILER_FLAG_UNRECOGNIZED);
}