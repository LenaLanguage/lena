/* Standart libraries */
#include <stdint.h>
#include <stdbool.h>

/* Libraries */
#include "ltypes/lchar.h"
#include "ltypes/lerror.h"

/* Functions */

/* Private */

bool _is_sep_sym(lchar_t sym) {
    return (bool)(sym == l('x') 
        || sym == l('o') 
        || sym == l('b'));
}

/* Public */

lerror_t lencode_lchar(lchar_t* input, lchar_t* restrict result) {
    if (input[0] == l('0') && _is_sep_sym(input[1])) {

    } else {
        return LENA_ERROR;
    }
}
