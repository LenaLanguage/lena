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

/* lthread basics */

typedef struct {
    HANDLE hThread;
    DWORD IdThread;
} lthread_t;

typedef DWORD lthread_func_t;
#define LENA_API WINAPI
#define LTHREAD_ARGS        LPVOID lpParam
#define LTHREAD_CALLBACK    0

/* lthread create */

lthread_t lthread_create(LPTHREAD_START_ROUTINE func){
    lthread_t ans = {NULL, 0};
    ans.hThread = CreateThread(NULL, 0, (func), NULL, 0, &ans.IdThread);
    return ans;
}

/* lthread join */

#define LTHREAD_WAIT_INFINITE (DWORD)(INFINITE)
typedef DWORD lthread_wait_t;

void lthread_join(lthread_t* thread, lthread_wait_t wait_ms){
    WaitForSingleObject(thread->hThread, wait_ms);
    CloseHandle(thread->hThread);
    thread = (lthread_t *){NULL, 0};
}

#else

#include <pthread.h>

typedef struct {
    pthread_t pThread;
} lthread_t;

lthread_t lthread_create(void* func){

}

#endif
#endif // __LENA_THREADS_H__