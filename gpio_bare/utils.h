/*
 * utils.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jonathanhendrix
 */


#ifndef UTILS_H_
#define UTILS_H_

inline void PUT32(unsigned int* addr, unsigned int val)
{
	*addr = val;
}

inline unsigned int GET32(unsigned int* addr)
{
	return *addr;
}

inline void busy_loop(unsigned int dly)
{
	for (volatile unsigned int i=0; i<dly; ++i);
}

#endif
