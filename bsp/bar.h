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
	BSC0_BAR = 	0x20205000,
	BSC1_BAR = 	0x20804000,
	BSC2_BAR = 	0x20805000 // Not available on RPi
};

#endif /* BAR_H_ */
