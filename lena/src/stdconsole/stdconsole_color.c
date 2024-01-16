#include <stdbool.h>

#include "stdconsole_color.h"

/* Use colors global variable */
static bool _use_lstdout_set_color = true;
static bool _use_lstderr_set_color = true;

#ifdef _WIN32
#include <windows.h>
#endif 

#ifdef _WIN32

inline
void lstdout_set_color(lena_stdcolor_t color) {
    if (_use_lstdout_set_color)
        SetConsoleTextAttribute(hConsoleOut, (WORD)(color));
}

inline
void lstderr_set_color(lena_stdcolor_t color) {
    if (_use_lstderr_set_color)
        SetConsoleTextAttribute(hConsoleErr, (WORD)(color));
}

#else /* UNIX */

/* ANSI codes for changing colors */
static const lchar_t* _lstdconsole_color_codes[] = {
    l("\x1b[30m"), l("\x1b[31m"),
    l("\x1b[32m"), l("\x1b[33m"),
    l("\x1b[34m"), l("\x1b[34m"),
    l("\x1b[35m"), l("\x1b[36m"),
    l("\x1b[37m"), l("\x1b[38m"),
    l("\x1b[39m") };

inline
void lstdout_set_color(lena_stdcolor_t color){
    if (_use_lstdout_set_color) {
        lstdout_str((lchar_t *)(_lstdconsole_color_codes[(int)(color)]),
        __LSTDCONSOLE_CODE_LENGHT);
    }
}

inline
void lstderr_set_color(lena_stdcolor_t color){
    if (_use_lstderr_set_color) {
        lstderr_str((lchar_t *)(_lstdconsole_color_codes[(int)(color)]),
        __LSTDCONSOLE_CODE_LENGHT);
    }
}

#endif