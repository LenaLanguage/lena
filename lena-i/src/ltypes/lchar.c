/* Include libraries */
#include <stdbool.h>

#include "lchar.h"

bool is_ldigit(lchar_t sym) {
    return (bool)(sym >= l('0') && sym <= l('9'));
}

bool is_lletter(lchar_t sym) {
    return (bool)(((sym) >= l('a') && (sym) <= l('z')) 
        || ((sym) >= l('A') && (sym) <= l('Z')));
}