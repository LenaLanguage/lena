#include <lena.h>

lthread_func_t LENA_API myThreadTest(LTHREAD_ARGS) {
    for (int i = 0; i < 100; ++i){
        lstdout_str(l("Call func!\n"), 12);
    }
    lstdout_str(l("END!\n"), 4);
    return LTHREAD_CALLBACK;
}

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    lstdout_set_color(LENA_ERROR_COLOR);
    lstdout_str(l("Hello Lena API in Linux!\n\n"), 26);

    lthread_t myThread = lthread_create(myThreadTest);
    
    lthread_join(&myThread, LTHREAD_WAIT_INFINITE);

    lstdout_set_color(LENA_LABEL_COLOR);
    lstdout_str(l("Nice!, we see.\n"), 16);

    lexit(LENA_EXIT_SUCCESS);
}
