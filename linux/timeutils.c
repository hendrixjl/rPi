/*
 * timeutils.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include <time.h>
#include "mytypes.h"


void udelay(uint32_t microseconds)
{
	struct timespec ts = {
			(microseconds/1000),
			(microseconds%1000)*1000
	};
	struct timespec remaining = {};
	nanosleep(&ts, &remaining);
}

unsigned long long getTime()
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	enum {
		MICROSECONDS_IN_SECOND=1000000U,
		NANOSECONDS_IN_MICROSECOND=1000U
	};
	return tp.tv_sec*MICROSECONDS_IN_SECOND + tp.tv_nsec/NANOSECONDS_IN_MICROSECOND;
}
