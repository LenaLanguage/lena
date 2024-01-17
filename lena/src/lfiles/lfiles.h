#ifndef __LENA_LFILES_COLOR_H__
#define __LENA_LFILES_COLOR_H__

/**************************************************************************//**
 * @file     lfiles.h
 * @brief    Project L - Lena programming language lfiles
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

/* CAN BE REWRITTEN */

/* Standard libraies */
#include <stdint.h>

/* Libraries */
#include "ltypes/ltypes.h"

/* For Windows */
#ifdef _WIN32

#include <windows.h>

HANDLE llibs_GetFileHandle(lchar_t filename[]);

HANDLE llibs_GetMapHandle(HANDLE fileHandle);

LPCVOID llibs_GetMapView(HANDLE mapHandle);

LONGLONG llibs_GetFileSize(HANDLE fileHandle);

typedef struct {
    HANDLE fileHandle;
    HANDLE mapHandle;
    LPCVOID mapView;
    int64_t size;
} lfile_t;

typedef uint8_t lfile_status_t;

enum lfile_status{
    LFILE_SUCCESS               = 0,
    LFILE_OPEN_FAILURE          = 1,
    LFILE_MAP_HANDLE_FAILURE    = 2,
    LFILE_MAP_VIEW_FAILURE      = 3,
    LFILE_SIZE_FAILURE          = 4
};

/* lfiles cross-platform functions */

lfile_status_t lfopen(lfile_t* lfile, lchar_t* filename);
lchar_t* lfget_pointer(lfile_t* lfile);
size_t lfget_len(lfile_t* lfile);
void lfclose(lfile_t* lfile);

#else  /* Linux */

#include <fcntl.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <stdlib.h>

typedef struct {
    lchar_t* data;  // data pointer
    int64_t size;   // size in bytes
} lfile_t;


enum lfile_status{
    LFILE_SUCCESS               = 0,
    LFILE_OPEN_FAILURE          = 1,
    LFILE_MEMORY_FAILURE        = 2,
    LFILE_READING_FAILURE       = 3,
    LFILE_SIZE_FAILURE          = 4
};

typedef uint8_t lfile_status_t;

/* lfiles cross-platform functions */

lfile_status_t lfopen(lfile_t* lfile, lchar_t* filename);
lchar_t* lfget_pointer(lfile_t* lfile);
size_t lfget_len(lfile_t* lfile);
void lfclose(lfile_t* lfile);

#endif
#endif // __LENA_LFILES_COLOR_H__