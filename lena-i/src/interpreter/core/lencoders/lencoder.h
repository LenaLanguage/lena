#ifndef __LENA_CORE_CONVERTER_H__
#define __LENA_CORE_CONVERTER_H__

/**************************************************************************//**
 * @file     lconverter.h
 * @brief    Project L - Lena programming language lconverter
 * @version  V0.0.1
 * @date     9. Feb 2024
 ******************************************************************************/

/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>

/* Libraries */
#include "ltypes/lchar.h"
#include "ltypes/lerror.h"

/* Functions */

/* For encoding different types of number: 0x00 0b00 0o00 */
extern lchar_t lencode_lchar(lchar_t* input);

#endif // __LENA_CORE_CONVERTER_H__