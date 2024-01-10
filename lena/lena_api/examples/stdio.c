#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstdout_str(l("Hello Lena API!"), 16);
    lexit(LENA_EXIT_SUCCESS);
}