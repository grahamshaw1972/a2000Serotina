/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * The arduino GOS implementation is similar to the bare metal raw32 gos implementation.
 * It uses cooperative multi-tasking. Be careful
 * 	when writing device drivers not to disturb the assumptions this creates by performing
 * 	call-backs to uGFX code unless you define the INTERRUPTS_OFF() and INTERRUPTS_ON() macros.
 * 	It still requires some C runtime library support...
 * 		enough startup to initialise the stack, interrupts, static data etc and call main().
 * 		setjmp() and longjmp()			- for threading
 * 		memcpy()						- for heap and threading
 * 		malloc(), realloc and free()	- if GOS_RAW_HEAP_SIZE == 0
 *
 * 	You must also define the following routines in your own code so that timing functions will work...
 * 		gTicks gfxSystemTicks(void);
 *		gTicks gfxMillisecondsToTicks(gDelay ms);
 */
#ifndef _GOS_ARDUINO_H
#define _GOS_ARDUINO_H

#if GFX_USE_OS_ARDUINO

#include <Arduino.h>

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

void gfxHalt(const char *msg);
void gfxExit(void);

/*===========================================================================*/
/* Use the generic thread handling and heap handling                         */
/*===========================================================================*/

#define GOS_NEED_X_THREADS	GFXON
#define GOS_NEED_X_HEAP		GFXON

#include "gos_x_threads.h"
#include "gos_x_heap.h"

#endif /* GFX_USE_OS_ARDUINO */
#endif /* _GOS_ARDUINO_H */
