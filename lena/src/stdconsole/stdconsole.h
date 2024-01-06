#ifndef __LENA_STDCONSOLE_H__
#define __LENA_STDCONSOLE_H__

/**************************************************************************//**
 * @file     stdconsole.h
 * @brief    Project L - Lena programming language stdconsole 
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* Standard libs */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32

#include <windows.h>

HANDLE  hConsoleOut = NULL, 
        hConsoleErr = NULL, 
        hConsoleIn = NULL;

bool lstdout_init(void){
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsoleOut == INVALID_HANDLE_VALUE) { 
        return false; 
    }
    return true;
}

bool lstderr_init(void){
    hConsoleErr = GetStdHandle(STD_ERROR_HANDLE);
    if (hConsoleErr == INVALID_HANDLE_VALUE) { 
        return false; 
    }
    return true;
}

bool lstdin_init(void){
    hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsoleIn == INVALID_HANDLE_VALUE) { 
        return false; 
    }
    return true;
}

bool lstd_init(void){
    return (bool)(lstdout_init() && lstderr_init() && lstdin_init());
}

/* Basic functions */

DWORD   ConsoleOutLen   = 0UL,
        ConsoleErrLen   = 0UL,
        ConsoleInLen    = 0UL;

/* STDOUT */

inline
bool lstdout_str(lchar *str, size_t len){
    return WriteConsole(hConsoleOut, str, len, &ConsoleOutLen, NULL);
}

bool lstdout_u64(uint64_t num){
    /* 21 characters for UINT64_MAX */
    static lchar __l_stdout_u64_buffer[21] = {0};
    static size_t __prev_u64_buffer_len = 21;

    memset(__l_stdout_u64_buffer, 0, sizeof(lchar) * __prev_u64_buffer_len);
    _ui64tow(num, __l_stdout_u64_buffer, 10);
    __prev_u64_buffer_len = llen(__l_stdout_u64_buffer);

    return WriteConsole(hConsoleOut, __l_stdout_u64_buffer, __prev_u64_buffer_len, &ConsoleOutLen, NULL);
}

/* STDERR */

inline
bool lstderr_str(lchar *str, size_t len){
    return WriteConsole(hConsoleErr, str, len, &ConsoleErrLen, NULL);
}

bool lstderr_u64(uint64_t num){
    /* 21 characters for UINT64_MAX */
    static lchar __l_stderr_u64_buffer[21] = {0};
    static size_t __prev_u64_buffer_len = 21;

    memset(__l_stderr_u64_buffer, 0, sizeof(lchar) * __prev_u64_buffer_len);
    _ui64tow(num, __l_stderr_u64_buffer, 10);
    __prev_u64_buffer_len = llen(__l_stderr_u64_buffer);

    return WriteConsole(hConsoleErr, __l_stderr_u64_buffer, __prev_u64_buffer_len, &ConsoleErrLen, NULL);
}

/* STDIN */

inline
bool lstdin_str(lchar *str, size_t len){
    return ReadConsole(hConsoleErr, str, len, &ConsoleInLen, NULL);
}



#else /* UNIX */
#endif 
#endif // __LENA_STDCONSOLE_H__