#ifndef __LENA_DELAY_H__
#define __LENA_DELAY_H__

/**************************************************************************//**
 * @file     ldelay.h
 * @brief    Project L - Lena programming language ldelay
 * @version  V0.0.1
 * @date     8. Jan 2024
 ******************************************************************************/


#ifdef _WIN32

#include <windows.h>

typedef DWORD ldelay_ms_t;

extern inline void ldelay(ldelay_ms_t ms);

#else

#include <unistd.h>

typedef unsigned int ldelay_ms_t;

extern inline void ldelay(ldelay_ms_t ms);


#endif
#endif // __LENA_DELAY_H__