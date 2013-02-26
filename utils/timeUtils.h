/*
 * timeutils.h
 *
 *  Created on: Feb 24, 2013
 *      Author: jonathanhendrix
 */

#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif

void busyloop(unsigned int n);

void udelay(uint32_t microseconds);


#ifdef __cplusplus
}
#endif

#endif /* TIMEUTILS_H_ */
