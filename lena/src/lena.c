#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstderr_set_color(LENA_ERROR_COLOR);
    lstderr_str(l("ERROR COLOR!\n"), 13);
    lstderr_u64(16254126);
    lexit(LENA_EXIT_SUCCESS);
}
