/* Include general file Llibs framework */
#include <llibs.h>

/* Include main Lena compiler header file*/
#include <lena.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>
#include <compiler/compiler.h>

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
            printf("%d", flag);
        }
    } else {
        lcout(X("No flags provided. Please specify flags to compile your program.\n"));
        // continue
    }
    return L_EXIT_SUCCESS;
}