#ifndef __LENA_FILES_ERRORS_H__
#define __LENA_FILES_ERRORS_H__

/**************************************************************************//**
 * @file     lfiles_errors.h
 * @brief    Project L - Lena programming language lerror
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Check lerror.h library */
#ifdef __LENA_ERROR_H__

lerror_func_t lena_open_file_error(lchar_t* filename, size_t len) {
   
}

#else
#error [lena.h]: lerror.h was not included!
#endif
#endif // __LENA_FILES_ERRORS_H__