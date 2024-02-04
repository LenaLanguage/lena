#ifndef __LENA_CORE_LOGS_H__
#define __LENA_CORE_LOGS_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language largs
 * @version  V0.0.1
 * @date     10. Jan 2024
 ******************************************************************************/

/* Libraries */

/* non-core */
#include "lconsole/lconsole_color.h"

/* core */
#include "../lconfig/lconf_logs.h"
#include "../lerrors/lerror.h"

void core_cout_logs_helper(unsigned int num, lchar_t *str);

void core_fout_logs(lchar_t* filename);
void core_cout_logs(void);

#endif // __LENA_CORE_LOGS_H__