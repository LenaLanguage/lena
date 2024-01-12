#ifndef __LENA_LOGS_H__
#define __LENA_LOGS_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language largs
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Check lerror.h library */
#ifdef __LENA_ERROR_H__

void lena_cout_logs_helper(unsigned int num, lchar_t *str) {
    const int size = LMXLSL -1;
    str[size] = l('\n'); /* it must be a new war crime */

    for (int i = size - 1; i >= LLLL; i--) {
        lchar_t digit = num & 0xF;
        if (digit < 10) {
            str[i] = l('0') + digit;
        } else {
            str[i] = l('A') + (digit - 10);
        }
        num >>= 4;
    }
}

void lena_fout_logs(lchar_t* filename, size_t len) {
    /* later */
}

void lena_cout_logs(void) {
    lstderr_str(l("\n[Lena][logs] "), 15);
    lstderr_set_color(LENA_INFO_COLOR);
    lstderr_str(l("Lena logs list:\n"), 17);
    
    if (lerror_index != 0) {
        lchar_t cerror_buffer[LMXLSL];
        lstderr_set_color(LENA_TEXT_COLOR);
        lstderr_str(l("|-> "), 5);
        lstderr_set_color(LENA_ERROR_COLOR);
        lstderr_str(l("Error index: "), 14);
        lstrcpy(cerror_buffer, l("0x"), LLLL);
        lstderr_set_color(LENA_TEXT_COLOR);
        for (lerror_index_t i = 0; i < lerror_index; ++i) {
            lena_cout_logs_helper(lerror_buffer[i], cerror_buffer);
            lstderr_str(cerror_buffer, LMXLSL);
        }
    } else {
        lstderr_str(l("[Lena][logs]: No output logs."), 30);
    }
}


#else
#error [lena.h]: lerror.h was not included!
#endif
#endif // __LENA_LOGS_H__