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
	nanosleep(ts);
}
