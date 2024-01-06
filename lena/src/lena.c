#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstderr_str(l("Hello World!"), 13);
    lstderr_set_color(LENA_LABEL_COLOR);
    lstderr_u64(16254126);
    lexit(LENA_EXIT_SUCCESS);
}
