#include <stdio.h>
#include <lena-i.h>

void print_t_data(ltoken_t token) {
    if (token.data != NULL) {
        for (size_t i = 0; i < token.len; ++i) {
            putchar(token.data[i]);
        }
    } else {
        printf("NULL");
    }
}

LMAIN(LENA_ARGC, LENA_ARGV) {
    if (!lstd_init()) {
        lexit(LENA_EXIT_FAILURE);
    }
    if (!core_args_exist(LENA_ARGC)) {
        lexit(LENA_EXIT_FAILURE);
    }

    lfile_t src_file;
    lfile_status_t stat = lfopen(&src_file, LENA_ARGV[1]);
    if (stat != LFILE_SUCCESS) {
        printf("%d", stat);
        lstdout_str(LENA_ARGV[1], llen(LENA_ARGV[1]));
        return LENA_EXIT_FAILURE;
    }


    /* Try to understand UTF-8 */

    lnchar_t* string = lfget_pointer(&src_file);

    while ((*string) != l('\0')) {
        printf("%c", (char)(*string));
        ++string;
    }

    lexit(LENA_EXIT_SUCCESS);
}


/*

void print_t_data(ltoken_t token) {
    if (token.data != NULL) {
        for (size_t i = 0; i < token.len; ++i) {
            putchar(token.data[i]);
        }
    } else {
        printf("NULL");
    }
}

LMAIN(LENA_ARGC, LENA_ARGV) {
    if (!lstd_init()) {
        lexit(LENA_EXIT_FAILURE);
    }
    if (!core_args_exist(LENA_ARGC)) {
        lexit(LENA_EXIT_FAILURE);
    }

    lfile_t src_file;
    lfile_status_t stat = lfopen(&src_file, LENA_ARGV[1]);
    if (stat != LFILE_SUCCESS) {
        printf("%d", stat);
        lstdout_str(LENA_ARGV[1], llen(LENA_ARGV[1]));
        return LENA_EXIT_FAILURE;
    }


    ltoken_buffer_t buffer;
    if (!ltoken_buffer_init(&buffer)) {
        lexit(LENA_EXIT_FAILURE);
    }

    lnchar_t* string = lfget_pointer(&src_file);
    //printf("%s", string);
    ltoken_get(&string, &buffer);
    core_args_receiver(LENA_ARGC, LENA_ARGV); 
    
    
    for(size_t i = 0; i < buffer.index; ++i) {
        printf("Current token:%ld\n\t ID:%d\n", i, buffer.token[i].type);
        printf("\t data:"); 
        print_t_data(buffer.token[i]); putchar('\n');
        printf("\t len:%ld\n", buffer.token[i].len);
    }

    ltoken_buffer_deinit(&buffer);
    lexit(LENA_EXIT_SUCCESS);
}

*/


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