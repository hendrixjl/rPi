/*
 * arm_timer.h
 *
 *  Created on: Jan 13, 2013
 *      Author: jonathanhendrix
 */

#ifndef ARM_TIMER_H_
#define ARM_TIMER_H_

#include "arm_timer.h"

enum prescale_ctrl_t {
	PRESCALE_IS_CLOCK_DIV_1 = 0,
	PRESCALE_IS_CLOCK_DIV_16 = 1,
	PRESCALE_IS_CLOCK_DIV_256 = 2,
	PRESCALE_IS_CLOCK_DIV_1_PRIME = 3 // @TODO don't understand
};

typedef enum {
	SIXTEEN_BITS = 0, TWENTY_THREE_BITS = 1
} timer_size_t;


#ifdef __cplusplus
extern "C" {
#endif

unsigned int arm_timer_val();

unsigned int arm_free_timer_val();

void arm_timer_clear_irq();

void arm_timer_setup(unsigned int timer_load,
		unsigned int timer_reload,
		unsigned int timer_divider,
		unsigned int prescale,
		timer_size_t ts);

unsigned int arm_timer_enable();

void arm_timer_disable();

void arm_timer_irq_enable();

void arm_timer_irq_disable();

int arm_timer_irq_pending_raw();

int arm_timer_irq_pending();

#ifdef __cplusplus
}
#endif

#endif /* ARM_TIMER_H_ */
