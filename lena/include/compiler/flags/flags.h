#ifndef LENA_COMPILER_FLAGS_RECOGNITION_H_
#define LENA_COMPILER_FLAGS_RECOGNITION_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     flags.enum.h
 * @brief    Project L - Lena programming language / compiler flags enum header
 * @version  V0.4.0
 * @date     29. June 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include llibs framework (external) */
#include <llibs.h>

/* Include specific libraries */
#include "flags.enum.h"

/** 
 * @brief Recognize type of flag from str pointer
 *  
 * @param[in] str string pointer
 * @return index of recognized flag
*/
extern compiler_flag_t flags_recognize(lc* str);

/** 
 * @brief Recognize type of flag from str pointer
 * 
 * For example in cases "-o main.le" - it's a building
 * or "--version ..." - just an information
 *  
 * @param[in] str string pointer
 * @return index of recognized flag
*/
extern lbool is_building_flag(compiler_flag_t flag);

#endif // LENA_COMPILER_FLAGS_RECOGNITION_H_