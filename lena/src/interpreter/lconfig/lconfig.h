#ifndef __LENA_MAIN_CONF_H__
#define __LENA_MAIN_CONF_H__

/**************************************************************************//**
 * @file     lconfig.h
 * @brief    Project L - Lena programming language largs
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Errors */
#define LENA_MAX_ERROR_BUFFER_LENGHT (int)256
#define LMXEBL LENA_MAX_ERROR_BUFFER_LENGHT

/* Logs */
#define LENA_LOGS_LABEL_LENGHT 2
#define LLLL LENA_LOGS_LABEL_LENGHT
#define LENA_MAX_LOGS_STR_LENGHT 16 + LENA_LOGS_LABEL_LENGHT
#define LMXLSL LENA_MAX_LOGS_STR_LENGHT

#endif // __LENA_MAIN_CONF_H__