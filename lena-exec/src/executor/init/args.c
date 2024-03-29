/* Include args library */
#include "executor/init/args.h"

/**
 * @brief Args list.
*/
const lc* ARGS_LIST[] = {
    [TOKEN_XX_HELP] = X("--help"),
    [TOKEN_XX_VERSION] = X("--version"),
    [TOKEN_XX_LICENSE] = X("--license"),

    [TOKEN_X_COLOR_TRUE] = X("-color=true"),
    [TOKEN_X_COLOR_FALSE] = X("-color=false"),
};

/**
 * @brief Args list len.
*/
const lsz ARGS_LIST_LEN = 5;

args_token_t args_token_recognize(lc* arg) {
    lsz len = lslen(arg);
    if (len < 3) {
        return (args_token_t)(TOKEN_INVALID);
    } else {
        range(i, 0, ARGS_LIST_LEN) {
            if (lscmp(arg, ARGS_LIST[i])) {
                lcout(X("FOUND!"));
            }
        }
    }
}