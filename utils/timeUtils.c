/*
 * timeUtils.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: jonathanhendrix
 */
#include "timeUtils.h"


void busyloop(uint32_t n)
{
	for(volatile unsigned i=0; i<n; i++);
}
