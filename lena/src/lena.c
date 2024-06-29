/* Include general file Llibs framework */
#include <llibs.h>

/* Include main Lena compiler header file*/
#include <lena.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>
#include <compiler/compiler.h>

lm compile(lu32 argc, lc8* argv[]) {
    if (llibs_init() != L_OK) {
        return L_EXIT_FAILURE;
    }
    if (argc > 1) {
        /* We should recognize all flags here ->*/
        if (argc > 2) {

        } else {
            /* One flag (no compilation)*/
            compiler_flag_t flag = flags_recognize(argv[2]);
            if (!is_building_flag(flag)) {

            } else {
                /* Error (compilation must be longer than 1 flag) */
                
            }
        }
    } else {
        lcout(X("No flags provided. Please specify flags to compile your program.\n"));
        // continue
    }
    return L_EXIT_SUCCESS;
}