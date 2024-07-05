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
    
    /* Source code tokenization */
    for (lu8 i = 0; i < num_files; ++i) {

    }

    /* Source code parsing */
    for (lu8 i = 0; i < num_files; ++i) {
        
    }

    /* Converting permanent code to bytecode */
    // ...


    return L_OK;
}
