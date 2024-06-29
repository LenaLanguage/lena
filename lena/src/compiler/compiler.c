/* Include specific libraries */
#include <compiler/compiler.h>

lerr compile_file (    
                lu8 num_files, 
                lc8* filenames[], 
                lu8 num_options, 
                compiler_flag_t* options_buffer
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
