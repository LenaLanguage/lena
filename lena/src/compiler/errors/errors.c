/* Include specific libraries */
#include <compiler/errors/errors.h>

void greeting(void) {
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("["));
    lccol(LC_COLOR_RED, LC_COLOR_BLACK);
    lcout(X("Lena"));
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("]: "));
}

/* General greeting function, prints "[Lena]: " */
void greeting_extended(const lc* str) {
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("["));
    lccol(LC_COLOR_RED, LC_COLOR_BLACK);
    lcout(X("Lena"));
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("]["));
    lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
    lcout(str);
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("]: "));
}
