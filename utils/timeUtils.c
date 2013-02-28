/*
 * timeUtils.cpp
 *
 *  Created on: Feb 24, 2013
 *      Author: jonathanhendrix
 */
#include "timeUtils.h"


void busyloop(unsigned int n)
{
	for(volatile unsigned i=0; i<n; i++);
}
