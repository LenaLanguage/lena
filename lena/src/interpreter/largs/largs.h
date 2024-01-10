#ifndef __LENA_ARGS_H__
#define __LENA_ARGS_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language largs
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Check lerror.h library */
#ifdef __LENA_ERROR_H__

lerror_func_t no_arguments(void) {
    lstderr_set_color(LENA_TEXT_COLOR);
    lstderr_str(LENA_LABEL_NAME, LENA_LABEL_NAME_L);
} 

bool largs_check(int argc){
    if (argc <= 1) {
        LENA_ERROR(LENA_NO_ARGS, no_arguments);
        return false;
    }
}



#else
#error [lena.h]: lerror.h was not included!
#endif
#endif // __LENA_ARGS_H__