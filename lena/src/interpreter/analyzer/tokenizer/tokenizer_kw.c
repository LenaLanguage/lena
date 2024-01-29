/* Include libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* non-core */
#include "ltypes/lchar.h"

/* interpreter */
#include "../config/conf_tokenizer.h"

/* tokenizer */
#include "tokenizer.h"

/* Functions for keywords */

bool __token_identifier_kw(lchar_t* input[], ltoken_buffer_t* buffer) {
    lchar_t* identifier = (*input);


    while (is_lletter(*identifier) || is_ldigit(*identifier)) {
        
        

        identifier++;
    }

    return true;
}