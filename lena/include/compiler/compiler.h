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

/* Include llibs framework (external) */
#include <llibs.h>

/* Compiler main function use an enum of flags */
#include "flags/flags.enum.h"

/* Define error index */
#define L_COMPILER_NO_INPUT_FLAGS   2
#define L_COMPILER_INVALID_FILENAME 3

/** 
 * @brief Compile multiple files with number of parameters.
 * 
 * 
 * @param[in] num_files number of files
 * @param[in] filenames filenames buffer
 * @param[in] num_options number of options
 * @param[in] options_buffer options buffer
 * @return compilation status L_OK or error index
*/
extern lerr compile_file (
                        lu8 num_files,
                        lc8* filenames[],
                        lu8 num_options,
                        compiler_flag_t* options_buffer
                        );

#endif // LENA_COMPILER_H_