/* Standard libraies */
#include <stdint.h>

/* Libraries */
#include "ltypes/ltypes.h"
#include "lfiles.h"

/* For Windows */
#ifdef _WIN32

#include <windows.h>

HANDLE llibs_GetFileHandle(lnchar_t filename[]) {
    return CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

HANDLE llibs_GetMapHandle(HANDLE fileHandle) {
    return CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
}

LPCVOID llibs_GetMapView(HANDLE mapHandle) {
    return MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0);
}

LONGLONG llibs_GetFileSize(HANDLE fileHandle) {
    LARGE_INTEGER size;
    if (!GetFileSizeEx(fileHandle, &size)) {
        return -1;
    }
    return size.QuadPart;
}

lfile_status_t lfopen(lfile_t* lfile, lnchar_t* filename){
    lfile->fileHandle = llibs_GetFileHandle(filename);
    if (lfile->fileHandle == NULL) { 
        CloseHandle(lfile->fileHandle);
        return LFILE_OPEN_FAILURE; 
    }
    lfile->mapHandle = llibs_GetMapHandle(lfile->fileHandle);
    if (lfile->mapHandle == NULL) {
        CloseHandle(lfile->mapHandle);
        CloseHandle(lfile->fileHandle);
        return LFILE_MAP_HANDLE_FAILURE;
    };
    lfile->mapView = llibs_GetMapView(lfile->mapHandle);
    if (lfile->mapView == NULL) {
        UnmapViewOfFile(lfile->mapView);
        CloseHandle(lfile->mapHandle);
        CloseHandle(lfile->fileHandle);
        return LFILE_MAP_VIEW_FAILURE;
    };
    lfile->size = llibs_GetFileSize(lfile->fileHandle);
    if (lfile->size == -1) {
        UnmapViewOfFile(lfile->mapView);
        CloseHandle(lfile->mapHandle);
        CloseHandle(lfile->fileHandle);
        return LFILE_SIZE_FAILURE; 
    };
    return LFILE_SUCCESS;
}

lnchar_t* lfget_pointer(lfile_t* lfile){
    return (lnchar_t *)(lfile->mapView);
}

void lfclose(lfile_t* lfile){
    UnmapViewOfFile(lfile->mapView);
    CloseHandle(lfile->mapHandle);
    CloseHandle(lfile->fileHandle);
    lfile->size = 0;
}

#else  /* Linux */

#include <fcntl.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <stdlib.h>

lfile_status_t lfopen(lfile_t* lfile, lnchar_t* filename) {
    int file_descriptor;
    size_t size;
    struct stat file_stat;
    char* buffer = NULL;

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor < 0) {
        return LFILE_OPEN_FAILURE;
    }

    if (fstat(file_descriptor, &file_stat) < 0) {
        close(file_descriptor);
        return LFILE_SIZE_FAILURE;
    }

    size = file_stat.st_size;
    buffer = (lnchar_t*)malloc(size);
    if (buffer == NULL) {
        close(file_descriptor);
        return LFILE_MEMORY_FAILURE;
    }

    if (read(file_descriptor, buffer, size) < 0) {
        free(buffer);
        close(file_descriptor);
        return LFILE_READING_FAILURE;
    }

    close(file_descriptor);

    lfile->data = buffer;
    lfile->size = size;

    return LFILE_SUCCESS;
}

lnchar_t* lfget_pointer(lfile_t* lfile){
    return (lnchar_t *)(lfile->data);
}

void lfclose(lfile_t* lfile) {
    free(lfile->data);
    lfile->size = 0;
}

#endif


/* Cross-platform funcrion */
size_t lfget_len(lfile_t* lfile){
    return (size_t)(lfile->size * sizeof(lnchar_t));
}