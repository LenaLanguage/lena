/* Include libraries */
#include <stdbool.h>

#include "lchar.h"

bool is_ldigit(lnchar_t sym) {
    return (bool)(sym >= l('0') && sym <= l('9'));
}

bool is_lletter(lnchar_t sym) {
    return (bool)(((sym) >= l('a') && (sym) <= l('z')) 
        || ((sym) >= l('A') && (sym) <= l('Z')));
}

bool is_lnull(lnchar_t sym) {
    return (bool)((sym) == l('\0'));
}