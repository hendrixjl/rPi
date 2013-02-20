/*
 * bsp.h
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#ifndef BAR_H_
#define BAR_H_

volatile unsigned* IRQ_BAR;
volatile unsigned* ARM_TIMER_BAR;
volatile unsigned* GPIO_BAR;
volatile unsigned* BSC0_BAR;
volatile unsigned* BSC1_BAR;
volatile unsigned* BSC2_BAR;
volatile unsigned* PWM_BAR;

#ifdef __cplusplus
extern "C"
{
#endif

void init_bars();

#ifdef __cplusplus
}
#endif

#endif /* BAR_H_ */
