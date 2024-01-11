#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    _use_lstderr_set_color = false;
    if (!lstd_init()) { lexit(LENA_EXIT_FAILURE); };
    if (!largs_check(LENA_ARGC)) { 
        lena_cout_logs();
        lexit(LENA_EXIT_FAILURE);
    }
    largs_handler(LENA_ARGC, LENA_ARGV);
    lexit(LENA_EXIT_SUCCESS);
}
