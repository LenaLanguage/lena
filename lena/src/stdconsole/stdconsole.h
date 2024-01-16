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

bool lstdout_init(void);

bool lstderr_init(void);

bool lstdin_init(void);

bool lstd_init(void);

/* Basic functions */

DWORD   ConsoleOutLen   = 0UL,
        ConsoleErrLen   = 0UL,
        ConsoleInLen    = 0UL;

/* Types */

typedef BOOL lstdio_t;
#define LSTDIO_ERROR (lstdio_t)(0)

/* STDOUT */


lstdio_t lstdout_str(lchar_t *str, size_t len);

lstdio_t lstdout_u64(uint64_t num);

/* STDERR */


lstdio_t lstderr_str(lchar_t *str, size_t len);

lstdio_t lstderr_u64(uint64_t num);

/* STDIN */


lstdio_t lstdin_str(lchar_t *buffer, size_t len);

#else /* UNIX */

#include <unistd.h>


/* Unix doesn't requre initialization */
bool lstd_init(void);

/* Basic functions */

/* Types */
typedef ssize_t lstdio_t;
#define LSTDIO_ERROR (lstdio_t)(-1)

/* STDOUT */

 
lstdio_t lstdout_str(lchar_t* str, size_t len);

/* STDERR */

 
lstdio_t lstderr_str(lchar_t* str, size_t len);

/* STDERR */

 
lstdio_t lstdin_str(lchar_t* buffer, size_t len);


#endif 
#endif // __LENA_STDCONSOLE_H__