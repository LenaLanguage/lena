/* Include specific libraries */
#include <compiler/info/info.h>

/* Prints current Lena's version */
void version(void) {

}

/* Prints full current Lena's version */
void version_extention(void) {
    lccol(LC_COLOR_RED, LC_COLOR_BLACK);
    lcout(X("Lena compiler "));
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("version "));
    lccol(LC_COLOR_YELLOW, LC_COLOR_BLACK);
    lcout(LENA_VERSION_STR);
}

/* Prints Lena's license */
void license(void) {

}

/* Prints help message */
void help(void) {
    
}