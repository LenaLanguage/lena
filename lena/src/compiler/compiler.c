/* Include specific libraries */
#include <compiler/compiler.h>

lerr compile_files (    
                lu8 num_files,
                lc* filenames[],
                lbool non_abstract,
                lc* targetfile,
                lu8 num_flags,
                compiler_flag_t flags[]
                ) {
    if (num_files == 0) {
        return L_COMPILER_NO_INPUT_FLAGS;
    }
    for (lu8 i = 0; i < num_files; ++i) {
        if (filenames[i] == NULL) {
            return L_COMPILER_INVALID_FILENAME;
        } else {
            /* here we have a full name of file -> */
            // compilation.....
        }
    }
    return L_OK;
}
