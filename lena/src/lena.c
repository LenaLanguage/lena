#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV) {
    if (!lstd_init()) { lexit(LENA_EXIT_FAILURE); };
    if (!core_args_exist(LENA_ARGC)) {
        lexit(LENA_EXIT_FAILURE);
    }
    ltoken_buffer_t buffer;
    if (!ltoken_buffer_init(&buffer)) {
        lexit(LENA_EXIT_FAILURE);
    }
    lchar_t* string = l("General 234235235 32424.525324 234234.5234 23434");
    ltoken_get(&string, &buffer);
    core_args_receiver(LENA_ARGC, LENA_ARGV); 

    for(size_t i = 0; i < buffer.index; ++i) {
        printf("%d ", buffer.token[i].type);
    }

    ltoken_buffer_deinit(&buffer);
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