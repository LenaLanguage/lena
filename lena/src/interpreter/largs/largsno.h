#ifndef __LENA_ARGSNO_H__
#define __LENA_ARGSNO_H__

/**************************************************************************//**
 * @file     largsno.h
 * @brief    Project L - Lena programming language largsno
 * @version  V0.0.1
 * @date     13. Jan 2024
 ******************************************************************************/

/* Configuration file must be included before */
#ifndef __LENA_MAIN_CONF_H__
#error [largsno.h]: lconfig.h was not included
#else

/* Largs list */

typedef uint8_t largsno_index_t;

typedef enum {
    LENA_ARG_DH_VERSION         = 0x00,  // --version
    LENA_ARG_DH_HELP_GENERAL    = 0x01,  // --help
    LENA_ARG_DH_HELP_ALL        = 0x02,  // --help-all
} largsno_t; // uint8_t

/* Buffer for largs list */
largsno_t largs_buffer[LMABL];
largsno_index_t largs_index = 0;

/* Find functions */

void largs_find(int argc, lchar_t* argv[]);

#endif
#endif // __LENA_ARGSNO_H__