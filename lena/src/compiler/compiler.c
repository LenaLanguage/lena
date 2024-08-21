/* Include specific libraries */
#include <compiler/compiler.h>

/* Compilation uses different file formats in "files/" folder */
#include <compiler/files/files.h>

/* Global variables */

/** 
 * @brief Target file buffer, contains output bytecode.
*/
lc* target = NULL;

#if LENA_EXE_FORMAT == true
/** 
 * @brief Target executable file buffer (Windows)
*/
lc* executable_exe = NULL;
#else
/** 
 * @brief Target executable file buffer (Linux)
*/
lc* executable = NULL;
#endif


lerr compile_files (    
                lu8 num_files,
                lc* filenames[],
                lbool non_abstract,
                lc* targetfile,
                lu8 num_flags,
                compiler_flag_t flags[]
                ) {
    
    
    /* --------- Source code ".le" tokenization --------- */

    le_token_buffer_t* token_buffer = lcalloc(num_files, sizeof(le_token_buffer_t) * num_files);

    if (lmemchk(token_buffer) == L_ERROR_MALLOC) {
        printf("Error!");
        return L_ERROR_MALLOC;
    }

    for (lu8 i = 0; i < num_files; ++i) {
        static lfile file;
        if (lfopen(filenames[i], &file) == L_OK) {
            lc* src_code = NULL;
            if (lfget(&src_code, &file) != L_OK) {
                return L_ERROR;
            }
            le_token_get(src_code, &token_buffer[i]);
        } else {
            free(token_buffer);
            return L_ERROR_COMPILER_INVALID_FILENAME;
        }
        
    }

    /* Source code parsing */
    for (lu8 i = 0; i < num_files; ++i) {
        
    }

    /* Converting permanent code to bytecode */
    // ...

    free(token_buffer);
    return L_OK;
}
