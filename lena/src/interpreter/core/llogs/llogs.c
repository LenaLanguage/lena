
/* Libraries */

/* non core */
#include "lconsole/lconsole_color.h"

/* core */
#include "../lconfig/lconf_logs.h"
#include "../lerrors/lerror.h"

/* Variables */


void core_cout_logs_helper(unsigned int num, lchar_t *str) {
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

void core_fout_logs(lchar_t* filename) {
    /* later */
}

void core_cout_logs(void) {
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
            core_cout_logs_helper(lerror_buffer[i], cerror_buffer);
            lstderr_str(cerror_buffer, LMXLSL);
        }
    } else {
        lstderr_str(l("[Lena][logs]: No output logs."), 30);
    }
}
