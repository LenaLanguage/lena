#include "util/greeting.h"

const lc* LENA_SUBNAME = X("Executor");

void greeting_lena() {
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("["));
    lccol(LC_COLOR_RED, LC_COLOR_BLACK);
    lcout(X("Lena"));
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("]["));
    lccol(LC_COLOR_RED, LC_COLOR_BLACK);
    lcout(LENA_SUBNAME);
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("]: "));
}