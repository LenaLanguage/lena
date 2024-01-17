#include "ldelay.h"

#ifdef _WIN32

inline 
void ldelay(ldelay_ms_t ms){ 
    Sleep((DWORD)(ms));
}

#else

inline 
void ldelay(ldelay_ms_t ms){ 
    sleep((unsigned int)(ms));
}

#endif