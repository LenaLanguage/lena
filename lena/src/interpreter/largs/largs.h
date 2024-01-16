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
#include "largs_errors.h"

bool largs_check(int argc){
    if (argc <= 1) {
        LENA_ERROR(LENA_ERROR_NO_ARGS, lena_no_arguments);
        return false;
    }
    return true;
}

void largs_handler(int argc, lchar_t* argv[]){
    for (int i = 0; i < argc; ++i) {
        lstdout_str(l("Args: "), 7);
        lstdout_str(argv[i], llen(argv[i]));
        lstdout_str(l("\n"), 1);
        /* --version --help */
        if (argv[i][0] == l('-') && argv[i][1] == l('-')) {
            size_t c_arg_len = llen(argv[i]) - 2;
            lchar_t* c_arg_data = (lchar_t *)(argv[i] + 2 * sizeof(lchar_t));
            if (lstrcmp(c_arg_data, l("version"), c_arg_len) == LSTRING_EQUAL) {
                lena_cout_version();
            }
        }
    }
}

/*

    if (argv[i][0] == l('-') && argv[i + 1][1] == l('-')) {
            lena_cout_version();
        } else if (argv[i][0] == l('-')) { /* -flag */

        //} else { /* other (files) */
            /*
                llibs_file_t mainfile;
                llibs_file_status_t status = llibs_OpenFile(&mainfile, argv[1]);
                if (status != LLIBS_FILE_SUCCESS) {
                    LENA_ERROR(LENA_OPEN_FILE_ERROR, lena_open_file_error, argv[1], llen(argv[1]));
                    lena_cout_logs();
                } else {
                }
            */
        //}

#else
#error [lena.h]: lerror.h was not included!
#endif
#endif // __LENA_ARGS_H__