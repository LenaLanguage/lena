#ifndef __LENA_LFILES_COLOR_H__
#define __LENA_LFILES_COLOR_H__

/**************************************************************************//**
 * @file     lfiles.h
 * @brief    Project L - Lena programming language lfiles
 * @version  V0.0.1
 * @date     6. Jan 2024
 ******************************************************************************/

#include <stdint.h>

/* For Windows */
#ifdef _WIN32

#include <windows.h>

HANDLE llibs_GetFileHandle(lchar fillibsme[]) {
    return CreateFile(fillibsme, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

HANDLE llibs_GetMapHandle(HANDLE fileHandle) {
    return CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
}

LPCVOID llibs_GetMapView(HANDLE mapHandle) {
    return MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0);
}

LONGLONG llibs_GetFileSize(HANDLE fileHandle) {
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(fileHandle, &fileSize)) {
        return -1;
    }
    return fileSize.QuadPart;
}

typedef struct {
    HANDLE fileHandle;
    HANDLE mapHandle;
    LPCVOID mapView;
    int64_t fileSize;
} llibs_file_t;

typedef uint8_t llibs_file_status_t;

enum llibs_file_status{
    LLIBS_FILE_SUCCESS               = 0,
    LLIBS_FILE_OPEN_FAILURE          = 1,
    LLIBS_FILE_MAP_HANDLE_FAILURE    = 2,
    LLIBS_FILE_MAP_VIEW_FAILURE      = 3,
    LLIBS_FILE_SIZE_FAILURE          = 4
};

llibs_file_status_t llibs_OpenFile(llibs_file_t *llibs_file, lchar fillibsme[]){
    llibs_file->fileHandle = llibs_GetFileHandle(fillibsme);
    if (llibs_file->fileHandle == NULL) { 
        CloseHandle(llibs_file->fileHandle);
        return LLIBS_FILE_OPEN_FAILURE; 
    }
    llibs_file->mapHandle = llibs_GetMapHandle(llibs_file->fileHandle);
    if (llibs_file->mapHandle == NULL) {
        CloseHandle(llibs_file->mapHandle);
        CloseHandle(llibs_file->fileHandle);
        return LLIBS_FILE_MAP_HANDLE_FAILURE;
    };
    llibs_file->mapView = llibs_GetMapView(llibs_file->mapHandle);
    if (llibs_file->mapView == NULL) {
        UnmapViewOfFile(llibs_file->mapView);
        CloseHandle(llibs_file->mapHandle);
        CloseHandle(llibs_file->fileHandle);
        return LLIBS_FILE_MAP_VIEW_FAILURE;
    };
    llibs_file->fileSize = llibs_GetFileSize(llibs_file->fileHandle);
    if (llibs_file->fileSize == -1) {
        UnmapViewOfFile(llibs_file->mapView);
        CloseHandle(llibs_file->mapHandle);
        CloseHandle(llibs_file->fileHandle);
        return LLIBS_FILE_SIZE_FAILURE; 
    };
    return LLIBS_FILE_SUCCESS;
}

lchar* llibs_GetFilePointer(llibs_file_t llibs_file){
    return (lchar *)(llibs_file.mapView);
}

void llibs_DeleteFile(llibs_file_t llibs_file){
    UnmapViewOfFile(llibs_file.mapView);
    CloseHandle(llibs_file.mapHandle);
    CloseHandle(llibs_file.fileHandle);
}

#else       /* LINUX / UNIX */

#include <stdio.h>

FILE* llibs_GetfileHandle(lchar fillibsme[]){
    return fopen(fillibsme, "rb");
}

long llibs_GetFileSize(FILE *file){
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

lchar* llibs_GetFileData(int64_t fileSize){
    return malloc(fileSize);
}

typedef struct {
    FILE *fileHandle;
    int64_t fileSize;
    lchar *filePointer;
} llibs_file_t;

typedef uint8_t llibs_file_status_t;

enum llibs_file_status{
    LLIBS_FILE_SUCCESS               = 0,
    LLIBS_FILE_OPEN_FAILURE          = 1,
    LLIBS_FILE_MEMORY_ALLOC_FAILURE  = 2,
};

llibs_file_status_t llibs_OpenFile(llibs_file_t *llibs_file, lchar fillibsme[]){
    llibs_file->fileHandle = llibs_GetfileHandle(fillibsme);
    if (llibs_file->fileHandle == NULL){
        return LLIBS_FILE_OPEN_FAILURE;
    }
    llibs_file->fileSize = llibs_GetFileSize(llibs_file->fileHandle);
    llibs_file->filePointer = llibs_GetFileData(llibs_file->fileSize);
    if (llibs_file->filePointer == NULL){
        fclose(llibs_file->fileHandle);
        return LLIBS_FILE_MEMORY_ALLOC_FAILURE;
    }
    fread(llibs_file->filePointer, 1, llibs_file->fileSize, llibs_file->fileHandle);
    return LLIBS_FILE_SUCCESS;
}


lchar* llibs_GetFilePointer(llibs_file_t llibs_file){
    return (llibs_file.filePointer);
}

void llibs_DeleteFile(llibs_file_t llibs_file){
    fclose(llibs_file.fileHandle);
    free(llibs_file.filePointer);
}

#endif


#endif // __LENA_LFILES_COLOR_H__