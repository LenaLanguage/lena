#ifndef __LENA_LCONVERTER_H__
#define __LENA_LCONVERTER_H__

/**************************************************************************//**
 * @file     lconverter.h
 * @brief    Project L - Lena programming language util/lconverter library
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

void uint16_to_hex_string(unsigned int num, lchar_t *str) {
    const int size = 16;
    str[size] = l('\0');
    
    for (int i = size - 1; i >= 0; i--) {
        lchar_t digit = num & 0xF;
        if (digit < 10) {
            str[i] = l('0') + digit;
        } else {
            str[i] = l('A') + (digit - 10);
        }
        num >>= 4;
    }
}

#endif // __LENA_LCONVERTER_H__