/*
 * timeUtils.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: jonathanhendrix
 */
#include "timeUtils.h"

#ifdef __BARE_METAL__

enum { USECS_TO_CYCLES=100 }; // just a guess

void udelay(uint32_t useconds)
{
	busyloop(useconds * USECS_TO_CYCLES);
}

#endif

void busyloop(unsigned int n)
{
	for(volatile unsigned i=0; i<n; i++);
}
