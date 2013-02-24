/*
 * bsp.h
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#ifndef BAR_H_
#define BAR_H_

#include <stdint.h>

extern volatile uint32_t* IRQ_BAR;
extern volatile uint32_t* ARM_TIMER_BAR;
extern volatile uint32_t* GPIO_BAR;
extern volatile uint32_t* BSC0_BAR;
extern volatile uint32_t* BSC1_BAR;
extern volatile uint32_t* BSC2_BAR;
extern volatile uint32_t* PWM_BAR;
extern volatile uint32_t* CLOCK_BAR;

#ifdef __cplusplus
extern "C"
{
#endif

void init_bars();

#ifdef __cplusplus
}
#endif

#endif /* BAR_H_ */
