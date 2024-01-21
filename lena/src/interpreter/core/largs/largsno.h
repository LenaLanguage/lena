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

/* core */
#include "../lconfig/lconf_args.h"

/* largsno index */
extern core_argsno_index_t core_argsno_index;

/* largsno buffer and list */

/**
 * LENA_ARGS_DH_ADR - 1.5 byte
 * LENA_ARGS_SH_ADR - 1.5 byte
 * LENA_ARGS_SA_ADR - 1 byte
*/

#define LENA_ARGS_DH_ADR 0x00000000
#define LENA_ARGS_SH_ADR 0x00000FFF
#define LENA_ARGS_SA_ADR 0x00FFFFFF

typedef enum {
    /* Double hyphen */
    LENA_ARGS_VERSION       = LENA_ARGS_DH_ADR + 0x00,
    LENA_ARGS_HELP          = LENA_ARGS_DH_ADR + 0x01,
    LENA_ARGS_HELP_ALL      = LENA_ARGS_DH_ADR + 0x02,
    /* Single hyphen */
    LENA_ARGS_V             = LENA_ARGS_SH_ADR + 0x00,
    /* Simple arg */
} core_argsno_t;

/* Args buffer */
extern core_argsno_t core_argsno[LMABL];

#endif // __LENA_CORE_ARGSNO_H__