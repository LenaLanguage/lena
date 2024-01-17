#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV) {
    core_args_exist(LENA_ARGC);
    lexit(LENA_EXIT_SUCCESS);
}

/*

    if (!lstd_init()) { lexit(LENA_EXIT_FAILURE); };
    if (!largs_check(LENA_ARGC)) { 
        lexit(LENA_EXIT_FAILURE); 
    }
    largs_handler(LENA_ARGC, LENA_ARGV);


    // Project map

    non-core libs - initialized for core libs (not executable) have names with l..
    core libs - initialized for analyzer and executor (not executable) have names with core_..
    executed libs - using core and non-core libs, executable (analyzer and executor) start with lena_..

    1. Check args
    2. Apply args modifications
    3. Open files in args

    1. Start code analyzer
    2. Start executor threads manager

*/