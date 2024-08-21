#ifndef LENA_COMPILER_H_
#define LENA_COMPILER_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     compiler.h
 * @brief    Project L - Lena programming language / compiler main header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/**
 * @warning Current version of the compiler you can find in info/info.h
 */

/**
 * IN ANY CASE:
 *  "SIZE" - means bytes.
 *  "LEN" - means number of characters.
 * 
 * Lena usually uses SIZE for optimization, but in some cases uses LEN.
 */

/* Include llibs framework (external) */
#include <llibs.h>

/* Compiler main function use an enum of flags */
#include "flags/flags.enum.h"

/* Define error index */
#define L_ERROR_COMPILER_NO_INPUT_FLAGS   2
#define L_ERROR_COMPILER_INVALID_FILENAME 3

/** 
 * @brief Compile multiple files with number of parameters.
 * 
 * 
 * @param[in] num_files number of files
 * @param[in] filenames filenames buffer
 * @param[in] non_abstract generate .na files
 * @param[in] targetfile target filename
 * @return compilation status L_OK or error index
*/
extern lerr compile_files   (    
                            lu8 num_files,
                            lc* filenames[],
                            lbool non_abstract,
                            lc* targetfile,
                            lu8 num_flags,
                            compiler_flag_t flags[]
                            );


#endif // LENA_COMPILER_H_