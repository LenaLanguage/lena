/* Libraries */

/* non-core */
#include "lconsole/lconsole.h"

/* interpreter */
#include "interpreter/version.h"

/* core */
#include "../llabels/llabels.h"

void lena_cout_version(void){
    lstdout_set_color(LENA_LABEL_COLOR);
    lstdout_str(l("lena ("), 7);
    lstdout_set_color(LENA_WARNING_COLOR);
    lstdout_str(LENA_BUILD_PLATFORM, llen(LENA_BUILD_PLATFORM));
    lstdout_set_color(LENA_LABEL_COLOR);
    lstdout_str(l(") "), 2);

    lstdout_set_color(LENA_WARNING_COLOR);
    lstdout_str(LENA_VERSION_STR, llen(LENA_VERSION_STR));
    lstdout_str(l("\n"), 1);

    lstdout_set_color(LENA_TEXT_COLOR);
    lstdout_str(LENA_LABEL_AUTHOR, LENA_LABEL_AUTHOR_L);
    lstdout_str(l("\n"), 1);
}
