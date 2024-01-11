#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if (!lstd_init()) { lexit(LENA_EXIT_FAILURE); };
    if (!largs_check(LENA_ARGC)) { 
        printf("Error!\n");
        for (lerror_index_t i = 0; i < lerror_index; ++i) {
            printf("0x%04x\n", lerror_buffer[i]);
        }
        lexit(LENA_EXIT_FAILURE);
    }
    largs_handler(LENA_ARGC, LENA_ARGV);
    lexit(LENA_EXIT_SUCCESS);
}
