#ifndef __LENA_CORE_ARGSNO_H__
#define __LENA_CORE_ARGSNO_H__

/**************************************************************************//**
 * @file     largs.h
 * @brief    Project L - Lena programming language args library
 * @version  V0.0.1
 * @date     17. Jan 2024
 ******************************************************************************/

/* Standard libraries */
#include <stdint.h>

typedef uint32_t core_argsno_index_t;
extern core_argsno_index_t ore_argsno_index;

typedef enum {
    /* Double hyphen */
    LENA_ARGS_HELP = 0,
    /* Single hyphen */

    /* Simple arg */
} core_argsno_t;

#endif // __LENA_CORE_ARGSNO_H__