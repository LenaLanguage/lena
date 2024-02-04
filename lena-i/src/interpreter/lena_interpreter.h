#ifndef __LENA_INTERPRETER_H__
#define __LENA_INTERPRETER_H__

/**************************************************************************//**
 * @file     lena_interpreter.h
 * @brief    Project L - Lena programming language main interpreter library
 * @version  V0.0.1
 * @date     16. Jan 2024
 ******************************************************************************/

/* Version */
#include "version.h"

/* Include core libraries */
#include "core/lconfig/lconfig.h"
#include "core/llabels/llabels.h"
#include "core/lerrors/lerror.h"
#include "core/llogs/llogs.h"
#include "core/ldebug/ldebug.h"
#include "core/lmessages/lmessages.h"
#include "core/largs/largs.h"

/* Include initializer libraries (lena core, threads ...) */
#include "initializer/initializer.h"

/* Include executor libraries for analyzer (based on threads and initializer) */
#include "executor/executor.h"

/* Include analyzer libraries (parser, tokenizator ...) */
#include "analyzer/analyzer.h"

/**
 *  Lena language construction:
 * 
 * 1 -> initializer downloads all files and functions
 * 2 -> executor is a tool for analyzer
 * 3 -> analyzer explore code and calls functions from 1 and 2 (in loop)
 * 
*/

#endif // __LENA_INTERPRETER_H__