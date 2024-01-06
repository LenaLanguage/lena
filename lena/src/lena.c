#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstdout_str(l("Hello World!"), 13);
    lexit(LENA_EXIT_SUCCESS);
}
