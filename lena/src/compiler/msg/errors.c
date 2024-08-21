/* Include specific libraries */
#include <compiler/msg/errors.h>

/* Private types */

/// @brief Struct for
typedef struct {
    lsz num;                // Number of loc messages 
    lc** error_messages;    // Error message(s)
    lc* help_message;       // Help message
} compiler_error_out_t;

static const compiler_error_out_t compiler_error_buffer_t[] = {

    /* --------- No input files --------- */
    [LE_ERROR_F_NO_INPUT] = (compiler_error_out_t)
    {
        2, 
        {
            X(""),
            X("")
        },
        X("")
    },
};


/*

static const lc* compiler_errors_msg_str[] = {
    /* --------- Launch errors --------- */

    /* Files errors 
    [LE_ERROR_F_NO_INPUT_FILE] = X(""),

    /* Args errors 
};
*/


/* Error output examples: */

/* error without loc */

/**
 * [Lena]:[ERROR](F1): Invalid input file. And other information is here.
 * 
 * [Lena]:[HELP]:
 *          Try to ......
 */

/* error with loc */

/**
 * [Lena]:[ERROR](S0): Unfinished sequence:
 *                            
 *          [main.le][12][2]:   my_str = "my Lena string
 * 
 * [Lena]:[HELP]:
 *          Try to ......
 */

// unfinished 
void compiler_error_print(compiler_errors_t index, lu64* locs) {

}
