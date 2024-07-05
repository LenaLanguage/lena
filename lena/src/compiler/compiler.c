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
 * @brief Target executable file buffer
*/
lc* exe = NULL;
#endif

lerr compile_files (    
                lu8 num_files,
                lc* filenames[],
                lbool non_abstract,
                lc* targetfile,
                lu8 num_flags,
                compiler_flag_t flags[]
                ) {
    
    return L_OK;
}
