#include <lena.h>


LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    if(!largs_check(LENA_ARGC)) {lexit(LENA_EXIT_FAILURE);}
    lexit(LENA_EXIT_SUCCESS);
}
