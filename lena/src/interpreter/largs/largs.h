#ifndef __LENA_ARGS_H__
#define __LENA_ARGS_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language largs
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Check lerror.h library */
#ifdef __LENA_ERROR_H__

#include "largsno.h"

lerror_func_t lena_no_arguments(void) {
    lstderr_set_color(LENA_TEXT_COLOR);
    lstderr_str(LENA_LABEL_NAME, LENA_LABEL_NAME_L);
    lstderr_set_color(LENA_INFO_COLOR);
    lstderr_str(l("Info: No input files or flags.\n"), 32);

    lstderr_set_color(LENA_TEXT_COLOR);
    lstderr_str(LENA_LABEL_NAME, LENA_LABEL_NAME_L);
    lstderr_set_color(LENA_HELP_COLOR);
    lstderr_str(l("Help: You can run the file with construct:\n"), 44);

    lstderr_set_color(LENA_TEXT_COLOR);
    lstderr_str(l("|-> "), 5);

    lstderr_set_color(LENA_LABEL_COLOR);
    lstderr_str(l("lena "), 6);
    lstderr_set_color(LENA_WARNING_COLOR);
    lstderr_str(l("[main file path] "), 18);
    lstderr_set_color(LENA_TEXT_COLOR);
    lstderr_str(l("-[flags]"), 9);

    lstderr_str(l("\n"), 1);
}

bool largs_check(int argc){
    if (argc <= 1) {
        LENA_ERROR(LENA_NO_ARGS, lena_no_arguments);
        return false;
    }
    return true;
}

void largs_handler(int argc, lchar_t* argv[]){
    for (int i = 0; i < argc; ++i) {
        lstdout_str(argv[i], llen(argv[i]));
        lstdout_str("\n", 1);
    }
}

#else
#error [lena.h]: lerror.h was not included!
#endif
#endif // __LENA_ARGS_H__