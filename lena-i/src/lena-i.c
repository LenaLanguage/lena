#include <lena-i.h>

lm lmain(lu32 argc, lc* argv[]) {
    if (llibs_init() != L_OK) {
        return L_EXIT_FAILURE;
    }
    return L_EXIT_SUCCESS;
}

