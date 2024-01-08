#ifndef __LENA_THREADS_H__
#define __LENA_THREADS_H__

/**************************************************************************//**
 * @file     lthreads.h
 * @brief    Project L - Lena programming language lthreads 
 * @version  V0.0.1
 * @date     7. Jan 2024
 ******************************************************************************/

/* Standard libraires */

#include <stdint.h>
#include <stdbool.h>

#ifndef _WIN32

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
    lthread_t thread = {NULL, 0};
    thread.hThread = CreateThread(NULL, 0, (func), NULL, 0, &thread.IdThread);
    return thread;
}

/* lthread get error */

typedef enum {
    LTHREAD_SUCCESS                 = 0b00000011,
    /* NEXT LINES OF CODE ARE NOT CROSS-PLATFORM */
    LTHREAD_ERROR_INVALID_POINTER   = 0b00000001,
    LTHREAD_ERROR_INVALID_ID        = 0b00000010,
} lthread_error_t;

lthread_error_t lthread_get_error(lthread_t thread){
    uint8_t result = 0;
    result = ((bool)(thread.IdThread) << 1) |((bool)(thread.hThread) << 0);
    return (lthread_error_t)(result);
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

#define _GNU_SOURCE
#include <pthread.h>
#include <sys/time.h>

/* lthread basics */

typedef enum {
    LTHREAD_SUCCESS = 0,
    /* NEXT LINES OF CODE ARE NOT CROSS-PLATFORM */
    /** LTHREAD_ERROR_N
     *  -> N is error code;
     * 
    */
} lthread_error_t;

typedef struct {
    pthread_t pThread;
    int32_t errThread;
} lthread_t;

typedef void* lthread_func_t;
#define LENA_API
#define LTHREAD_ARGS        void* arg
#define LTHREAD_CALLBACK    NULL

/* lthread create */

lthread_t lthread_create(void* func){
    lthread_t result = {0, 0};
    result.errThread = pthread_create(&result.pThread, NULL, func, NULL);
}

/* lthread get error */

// enum lthread_error_t is defined above

lthread_error_t lthread_get_error(lthread_t thread){
    return (lthread_error_t)(thread.errThread);
}

/* lthread join */

#define LTHREAD_WAIT_INFINITE 0
typedef uint32_t lthread_wait_t;

void lthread_join(lthread_t* thread, lthread_wait_t wait_ms){
    struct timespec timeout = {0, (wait_ms * 1000)};
    pthread_timedjoin_np(thread->pThread, NULL, &timeout);
}

#endif
#endif // __LENA_THREADS_H__