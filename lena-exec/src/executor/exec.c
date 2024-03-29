/* Include executor and Llibs libraries */
#include "executor/exec.h"
#include "util/greeting.h"

lm lena_no_input_flags(void) {
    greeting_lena();
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("No input files or flags!\nProcess terminated."));
    return L_EXIT_FAILURE;
}

/* Lena executor main function */
lm lena_execute(lu32 argc, lc* argv[]) {

    return L_EXIT_SUCCESS;
}