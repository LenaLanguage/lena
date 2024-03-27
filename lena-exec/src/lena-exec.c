#include <lena-exec.h>

lm lmain(lu32 argc, lc* argv[]) {
    /* Check Llibs initialization */
    if (llibs_init() != L_OK) {
        return L_EXIT_FAILURE;
    }
    /* If args don't exist */
    if (argc <= 1) {
        return L_EXIT_FAILURE;
    }
    /* Execute file */
    return lena_execute(argc, argv);
}