
/* Standard libs */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "ltypes/ltypes.h"
#include "stdconsole.h"

#ifdef _WIN32

#include <windows.h>


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

/* STDOUT */

inline
lstdio_t lstdout_str(lchar_t *str, size_t len){
    return (lstdio_t)(WriteConsole(hConsoleOut, str, len, &ConsoleOutLen, NULL));
}

lstdio_t lstdout_u64(uint64_t num){
    /* 21 characters for UINT64_MAX */
    static lchar_t __l_stdout_u64_buffer[21] = {0};
    static size_t __prev_u64_buffer_len = 21;

    memset(__l_stdout_u64_buffer, 0, sizeof(lchar_t) * __prev_u64_buffer_len);
    _ui64tow(num, __l_stdout_u64_buffer, 10);
    __prev_u64_buffer_len = llen(__l_stdout_u64_buffer);

    return (lstdio_t)(WriteConsole(hConsoleOut, __l_stdout_u64_buffer, __prev_u64_buffer_len, &ConsoleOutLen, NULL));
}

/* STDERR */

inline
lstdio_t lstderr_str(lchar_t *str, size_t len){
    return WriteConsole(hConsoleErr, str, len, &ConsoleErrLen, NULL);
}

lstdio_t lstderr_u64(uint64_t num){
    /* 21 characters for UINT64_MAX */
    static lchar_t __l_stderr_u64_buffer[21] = {0};
    static size_t __prev_u64_buffer_len = 21;

    memset(__l_stderr_u64_buffer, 0, sizeof(lchar_t) * __prev_u64_buffer_len);
    _ui64tow(num, __l_stderr_u64_buffer, 10);
    __prev_u64_buffer_len = llen(__l_stderr_u64_buffer);

    return (lstdio_t)(WriteConsole(hConsoleErr, __l_stderr_u64_buffer, __prev_u64_buffer_len, &ConsoleErrLen, NULL));
}

/* STDIN */

inline
lstdio_t lstdin_str(lchar_t *buffer, size_t len){
    return (lstdio_t)(ReadConsole(hConsoleErr, buffer, len, &ConsoleInLen, NULL));
}



#else /* UNIX */

#include <unistd.h>


/* Unix doesn't requre initialization */
bool lstd_init(void) {
    return true;
}

/* Basic functions */

/* STDOUT */

inline 
lstdio_t lstdout_str(lchar_t* str, size_t len) {
    return write(STDOUT_FILENO, str, len);
}

/* STDERR */

inline 
lstdio_t lstderr_str(lchar_t* str, size_t len) {
    return write(STDERR_FILENO, str, len);
}

/* STDERR */

inline 
lstdio_t lstdin_str(lchar_t* buffer, size_t len) {
    return read(STDIN_FILENO, buffer, len);
}

#endif