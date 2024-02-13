#ifndef __LENA_LAPP_H__
#define __LENA_LAPP_H__

/**************************************************************************//**
 * @file     lapp.h
 * @brief    Project L - Lena programming language util/lapp library
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdlib.h>

/* Exit codes */
enum lexit_codes {
    LENA_EXIT_SUCCESS = 0x00,
    LENA_EXIT_FAILURE = 0x01,
};

#define lexit(exit_status) exit(exit_status)

#define LENA_ARGC argc
#define LENA_ARGV argv

#ifdef _WIN32 /* WINDOWS */
#include <windows.h>
#define LMAIN(argc, argv) int wmain(int argc, lchar_t* argv[])
#else /* LINUX */
#define LMAIN(argc, argv) int main(int argc, lchar_t* argv[])
#endif

#endif // __LENA_LAPP_H__
