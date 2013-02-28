/*
 * timeutils.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include <time.h>
#include <sys/types.h> // C99 problem in gcc -std=C99
#include "mytypes.h"


void udelay(uint32_t microseconds)
{
	struct timespec ts = {
			(microseconds/1000),
			(microseconds%1000)*1000
	};
	nanosleep(ts);
}
