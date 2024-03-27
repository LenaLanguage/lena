#ifndef LENA_EXECUTOR_MAIN_H_
#define LENA_EXECUTOR_MAIN_H_

/**************************************************************************//**
 * @file     lena-exec.h
 * @brief    Project L - Lena programming language executor / main library
 * @version  V0.1.0
 * @date     27. Mar 2024
 * @author   Matvey Rybalkin
 ******************************************************************************/

/*
 * This file is part of Lena programming language executor. Project L.
 * Multilingual, cross-platform framework for robots and embedded systems.
 * 
 * Copyright (C) 2024 Matvey Ryblkin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */



/* Check C standard */
#if __STDC_VERSION__  >= 201112L

/* Include llibs framework (external) */
#include <llibs.h>

/* Include Lena executor libraries */
#include "exec/exec.h"

#else /* ERROR (__STDC_VERSION__ >= 201112L) */
#error [lena-i.h]: Requires at least version C 2011 (__STDC_VERSION__ >= 201112L)
#endif
#endif // LENA_EXECUTOR_MAIN_H_