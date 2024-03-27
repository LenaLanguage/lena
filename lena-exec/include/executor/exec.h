#ifndef LENA_EXECUTOR_EXEC_H_
#define LENA_EXECUTOR_EXEC_H_

/**************************************************************************//**
 * @file     exec.h
 * @brief    Project L - Lena programming language executor / exec library
 * @version  V0.0.1
 * @date     27. Mar 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/* Include Llibs framework */
#include <llibs.h>

/** 
  * @brief Lena executor main function.
  * 
  * @param[in] argc argument counter (from lmain)
  * @param[in] argv argument variables (from lmain)
  * @return result of execution
  * 
  */
extern lm lena_execute(lu32 argc, lc* argv[]);

#endif // LENA_EXECUTOR_EXEC_H_