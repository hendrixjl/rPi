/*
 * bsp.h
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#ifndef BAR_H_
#define BAR_H_


enum bar_t {
	IRQ_BAR =       0x2000B200,
	ARM_TIMER_BAR = 0x2000B400,
	GPIO_BAR =      0x20200000
};

#endif /* BAR_H_ */
