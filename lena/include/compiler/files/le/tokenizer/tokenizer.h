#ifndef LENA_COMPILER_FILES_LE_TOKENIZER_H_
#define LENA_COMPILER_FILES_LE_TOKENIZER_H_

/* PUBLIC HEADER FILE */

/**************************************************************************//**
 * @file     tokenizer.h
 * @brief    Project L - Lena programming language / compiler files '.le' header
 * @version  V0.4.0
 * @date     5. Jule 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include enum header */
#include "tokenizer.enum.h"

/** 
 * @brief Reads the source code of the format ".le" and returns the buffer of tokens.
 * 
 * 
 * @param[in] src_code source code pointer in UTF-8 encode.
 * @param[out] buffer le_token buffer pointer
 * @return buffer of tokens
*/
extern lerr le_token_get(lc* src_code, le_token_buffer_t* buffer);

#endif // LENA_COMPILER_FILES_LE_TOKENIZER_H_