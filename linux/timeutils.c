/*
 * timeutils.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include <unistd.h>



void udelay(uint32_t microseconds)
{
	usleep(microseconds);
}
