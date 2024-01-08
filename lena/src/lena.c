#include <lena.h>

lthread_func_t LENA_API threadFunction(LTHREAD_ARGS) {
    for(int i = 0; i < 20; ++i){
        lstderr_str(l("Call thread!\n"), 13);
        ldelay(100);
    }
    return LTHREAD_CALLBACK;
}

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstderr_set_color(LENA_ERROR_COLOR);
    lstderr_str(l("ERROR COLOR!\n"), 13);
    lstderr_u64(16254126);
    lthread_t myThread = lthread_create(threadFunction);
    lthread_join(&myThread, LTHREAD_WAIT_INFINITE);
    lexit(LENA_EXIT_SUCCESS);
}
