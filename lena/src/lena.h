#ifndef __LENA_MAIN_H__
#define __LENA_MAIN_H__

/**************************************************************************//**
 * @file     lena.h
 * @brief    Project L - Lena programming language main library
 * @version  V0.1.2
 * @date     5. Jan 2024
 ******************************************************************************/

/* Check C standard */
#if __STDC_VERSION__ >= 201112L

/* Types */
#include "ltypes/ltypes.h"

/* Util libraires */
#include "util/lapp.h"
#include "util/lconverter.h"

/* Libraries */
#include "stdconsole/stdconsole.h"
#include "stdconsole/stdconsole_color.h"

#include "lfiles/lfiles.h"
#include "lthreads/lthreads.h"
#include "ldelay/ldelay.h"


/* Interpreter libraries */
#include "interpreter/version.h"
#include "interpreter/lconfig/lconfig.h"
#include "interpreter/llabels/llabels.h"
#include "interpreter/lerrors/lerror.h"
#include "interpreter/llogs/llogs.h"
#include "interpreter/ldebug/ldebug.h"
#include "interpreter/lmessages/lmessages.h"

/* Libraries error lists */
#include "lfiles/lfiles_errors.h"
#include "interpreter/largs/largs_errors.h"
 
/* Executable libraries */
#include "interpreter/largs/largs.h"


#else /* ERROR (__STDC_VERSION__ >= 201112L) */
#error [lena.h]: Requires at least version C 2011 (__STDC_VERSION__ >= 201112L)
#endif
#endif // __LENA_MAIN_H__