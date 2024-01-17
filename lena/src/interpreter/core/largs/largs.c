
/* Standard libraries */
#include <stdint.h>

/* Libraries */

/* core */
#include "largs.h"

/* non-core */
#include "ltypes/ltypes.h"
#include "lconsole/lconsole.h"

/* Unvisible functions */

/* Double hyphen */
void __core_args_dh(lchar_t argv[]) {

}

/* Single hyphen */
void __core_args_sh(lchar_t argv[]) {

}

/* Simple arg */
void __core_args_sa(lchar_t argv[]) {

}

/* Visible functions */

bool core_args_exist(int argc) {
    if (argc <= 1) {
        return false;
    } else {
        return true;
    }
}

void core_args_receiver(int argc, lchar_t* argv[]) {
    /* argv[0] always equ 'lena' */
    for (int i = 1; i < argc; ++i) {
        size_t c_arg_len = llen(argv[i]);

        /* --arg */
        if (c_arg_len >= 3) {
            if (argv[i][0] == l('-') && argv[i][1] == l('-')) {
                __core_args_dh((lchar_t *)(argv[i] + 2 * sizeof(lchar_t)));
            } else {
                goto sh_arg; /* Go to single hyphen */
            }
        }

        /* -arg */
        if (c_arg_len >= 1) {
        sh_arg:
            if (argv[i][0] == l('-')) {
                __core_args_sh((lchar_t *)(argv[i] + 1 * sizeof(lchar_t)));
            } else {
                goto s_arg; /* Go to simple arg (without hyphen) */
            }
        }

        /* arg */
        if (c_arg_len > 0) {
        s_arg:
            __core_args_sa(argv[i]);
        }
    }
}