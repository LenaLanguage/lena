#include <lena.h>

LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };

    lnchar_t* label = l("Hello Lena API!");
    size_t label_len = llen(label);

    /* Set color (optional)*/
    lstdout_set_color(LENA_LABEL_COLOR);

    /* STDOUT */
    lstdout_str(label, label_len);

    /* Set color (optional)*/
    lstderr_set_color(LENA_ERROR_COLOR);

    /* STDERR */
    lstdout_str(label, label_len);

    /* Buffer */
    lnchar_t buffer[10];

    /* STDIN */
    lstdin_str(buffer, 10);

    lexit(LENA_EXIT_SUCCESS);
}