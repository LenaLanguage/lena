
/* Standard libraries */
#include <stdint.h>

/* Libraries */

/* core */
#include "largs.h"

/* non-core */
#include "ltypes/ltypes.h"
#include "lconsole/lconsole.h"


/* Finders for different arguments */

/* Double hyphen */
void lena_args_dh(lchar_t argv[]);

/* Single hyphen */
void lena_args_sh(lchar_t argv[]);

/* Simple arg */
void lena_args_sa(lchar_t argv[]);

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
        if (c_arg_len >= 3) { /* --x (3)*/
            if (argv[i][0] == l('-') && argv[i][1] == l('-')) {
                lena_args_dh((lchar_t *)(argv[i] + 2));
            } else {
                goto sh_arg; /* Go to single hyphen */
            }
        } else if (c_arg_len >= 2) { /* -x (2)*/
        sh_arg:
            if (argv[i][0] == l('-')) {
                lena_args_sh((lchar_t *)(argv[i] + 1));
            } else {
                goto s_arg; /* Go to simple arg (without hyphen) */
            }
        } else if (c_arg_len > 0) { /* x > 0 */
        s_arg:
            lena_args_sa(argv[i]);
        }
    }
}