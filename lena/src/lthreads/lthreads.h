#ifndef __LENA_THREADS_H__
#define __LENA_THREADS_H__

/**************************************************************************//**
 * @file     lthreads.h
 * @brief    Project L - Lena programming language lthreads 
 * @version  V0.0.1
 * @date     7. Jan 2024
 ******************************************************************************/


#ifdef _WIN32

#include <windows.h>

typedef HANDLE lthread_t;

void lthread_create();

#else

#include <pthread.h>

typedef pthread_t lthread_t;

void lthread_create();

#endif
#endif // __LENA_THREADS_H__