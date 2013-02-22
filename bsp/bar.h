/*
 * bsp.h
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#ifndef BAR_H_
#define BAR_H_

extern volatile unsigned* IRQ_BAR;
extern volatile unsigned* ARM_TIMER_BAR;
extern volatile unsigned* GPIO_BAR;
extern volatile unsigned* BSC0_BAR;
extern volatile unsigned* BSC1_BAR;
extern volatile unsigned* BSC2_BAR;
extern volatile unsigned* PWM_BAR;

#ifdef __cplusplus
extern "C"
{
#endif

void init_bars();

#ifdef __cplusplus
}
#endif

#endif /* BAR_H_ */
