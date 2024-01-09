#include <lena.h>


LMAIN(LENA_ARGC, LENA_ARGV){
    if(!lstd_init()){ lexit(LENA_EXIT_FAILURE); };
    
    lchar_t* const_str = l("Hello Lena API!");
    lchar_t mystr[20];

    lstrcpy(mystr, const_str, 16);
    lstdout_str(mystr, 16);

    lchar_t* my_new_str = l("Hello AAAAAAA");

    if (lstrcmp(mystr, my_new_str, 5) == LSTRING_EQUAL) {
        lstdout_set_color(LENA_WARNING_COLOR);
    } else {
        lstdout_set_color(LENA_TEXT_COLOR);
    }

    lstdout_str("\nGood work!", 12);

    lexit(LENA_EXIT_SUCCESS);
}
