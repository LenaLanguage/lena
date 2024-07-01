/* Include general file Llibs framework */
#include <llibs.h>

/* Include main Lena compiler header file*/
#include <lena.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>
#include <compiler/compiler.h>

/* For information messages */
#include <compiler/errors/errors.h>
#include <compiler/info/info.h>

lm compile(lu32 argc, lc* argv[]) {
    if (llibs_init() != L_OK) {
        return L_EXIT_FAILURE;
    }
    if (argc > 1) {
        /* We should recognize all flags here ->*/
        if (argc >= 4) {
            /* at least 3 flags: "lena main.le -o app.e" */
            /* It must be flags for compilation here -> */
            // Compilation
        } else {
            /* Just read first flag */
            compiler_flag_t flag = flags_recognize(argv[1]);
            if (is_compilation_flag(flag)) {
                /* Error */
                greeting();
                lcout(X("Too few flags to compile."));
                // We can add some details later.....
            } else {
                /* Execute the certain instruction */
                switch (flag) {
                /* Short version information */
                case COMPILER_FLAG_DD_VERSION:
                    version();
                /* Full version information */
                case COMPILER_FLAG_D_VERSION:
                    version_extention();
                    break;

                /* Help information */
                case COMPILER_FLAG_DD_HELP:
                    help();
                    break;

                /* Help information */
                case COMPILER_FLAG_DD_LICENSE:
                    license();
                    break;

                default:
                    // let's try to find out similar flag....
                    greeting();
                    lcout(X("Unrecognized flag, it will be useful for you to read:\n"));
                    help();
                    break;
                }
            }
        }
    } else {
        greeting();
        lcout(X("No flags provided. Please specify flags to compile your program.\n"));
        // continue
    }
    /* Deinitialization */
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    return L_EXIT_SUCCESS;
}