#ifndef __LENA_STDCONSOLE_COLOR_H__
#define __LENA_STDCONSOLE_COLOR_H__

/**************************************************************************//**
 * @file     stdconsole_color.h
 * @brief    Project L - Lena programming language stdconsole_color
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* stdconsole_color.h is required */
#ifndef __LENA_STDCONSOLE_H__
#error [stdconsole_color.h]: stdconsole.h was not included!
#else

#ifdef _WIN32
#include <windows.h>
#else
#endif 

/* lena_stdcolor_t */

typedef enum {
#ifdef _WIN32
    LENA_TEXT_COLOR     = 0x0F,
    LENA_ERROR_COLOR    = FOREGROUND_RED    | FOREGROUND_INTENSITY,
    LENA_WARNING_COLOR  = FOREGROUND_RED    | FOREGROUND_GREEN,
    LENA_INFO_COLOR     = FOREGROUND_BLUE   | FOREGROUND_INTENSITY,
    LENA_HELP_COLOR     = FOREGROUND_GREEN  | FOREGROUND_INTENSITY,
    LENA_LABEL_COLOR    = FOREGROUND_BLUE   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
#else
    LENA_TEXT_COLOR     = 0,
    LENA_ERROR_COLOR    = 1,
    LENA_WARNING_COLOR  = 2,
    LENA_INFO_COLOR     = 3,
    LENA_HELP_COLOR     = 4,
    LENA_LABEL_COLOR    = 5,
#endif 
} lena_stdcolor_t;


#ifdef _WIN32

inline
void lstdout_set_color(lena_stdcolor_t color) {
     SetConsoleTextAttribute(hConsoleOut, (WORD)(color));
}

inline
void lstderr_set_color(lena_stdcolor_t color) {
     SetConsoleTextAttribute(hConsoleErr, (WORD)(color));
}

#else /* UNIX */

inline
void lstdout_set_color(lena_stdcolor_t color);

inline
void lstderr_set_color(lena_stdcolor_t color);

#endif 

#endif // __LENA_STDCONSOLE_H__
#endif // __LENA_STDCONSOLE_COLOR_H__