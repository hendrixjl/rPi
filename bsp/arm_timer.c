/*
 * arm_timer.c
 *
 *  Created on: Jan 13, 2013
 *      Author: jonathanhendrix
 */

#include "arm_timer.h"
#include "bar.h"

enum {
	ARM_TIMER_LOD = ARM_TIMER_BAR + 0x0000,
	ARM_TIMER_VAL = ARM_TIMER_BAR + 0x0004,
	ARM_TIMER_CTL = ARM_TIMER_BAR + 0x0008,
	ARM_TIMER_CLI = ARM_TIMER_BAR + 0x000C,
	ARM_TIMER_RIS = ARM_TIMER_BAR + 0x0010,
	ARM_TIMER_MIS = ARM_TIMER_BAR + 0x0014,
	ARM_TIMER_RLD = ARM_TIMER_BAR + 0x0018,
	ARM_TIMER_DIV = ARM_TIMER_BAR + 0x001C,
	ARM_TIMER_CNT = ARM_TIMER_BAR + 0x0020
};


enum {
	TIMER_SIZE_BIT = 1,
	TIMER_PRESCALE_BIT = 2,
	TIMER_INT_ENABLE_BIT = 5,
	TIMER_ENABLE_BIT = 7,
	TIMER_PRESCALE_BYTE_BIT = 16 // @TODO don't understand
};

enum {
	TIMER_DISABLE = 0,
	TIMER_ENABLE = 1,
	TIMER_IRQ_DISABLE = 0,
	TIMER_IRQ_ENABLE = 1
};

unsigned int set_timer_ctrl(
		unsigned int enable,
		unsigned int irq_enable,
		unsigned prescale,
		timer_size_t timer_size) {
	enum {
		RESET_PRESCALER = 0x3E  // from BCM2835-ARM-Peripherals
	};

	unsigned int temp = (RESET_PRESCALER << TIMER_PRESCALE_BYTE_BIT)
			+ (enable << TIMER_ENABLE_BIT)
			+ (irq_enable << TIMER_INT_ENABLE_BIT) + (prescale << TIMER_PRESCALE_BIT)
			+ (timer_size << TIMER_SIZE_BIT);
	*(unsigned int*) ARM_TIMER_CTL = temp;
	return temp;
}

unsigned int get_timer_ctrl(
		unsigned int* enable,
		unsigned int* irq_enable,
		unsigned int* prescale,
		unsigned int* timer_size) {
	unsigned int temp = *(unsigned int*) ARM_TIMER_CTL;
	*enable = ((temp & (1 << TIMER_ENABLE_BIT)) > 0);
	*irq_enable = ((temp & (1 << TIMER_INT_ENABLE_BIT)) > 0);
	enum {
		TIMER_PRESCALE_MASK = 0x03 // all bits set
	};
	*prescale = (temp >> TIMER_PRESCALE_BIT) & TIMER_PRESCALE_MASK;
	*timer_size =
			(temp & (1 << TIMER_SIZE_BIT)) ? TWENTY_THREE_BITS : SIXTEEN_BITS;
	return *(unsigned int*) ARM_TIMER_CTL;
}

unsigned int load_timer(unsigned int i) {
	*(unsigned int*) ARM_TIMER_LOD = i;
	return *(unsigned int*) ARM_TIMER_LOD;
}

void set_timer_reload(unsigned int i) {
	*(unsigned int*) ARM_TIMER_RLD = i;
}

void set_timer_divider(unsigned int i) {
	*(unsigned int*) ARM_TIMER_DIV = i;
}

unsigned int arm_timer_val() {
	return *(unsigned int*) ARM_TIMER_VAL;
}

unsigned int arm_free_timer_val() {
	return *(unsigned int*) ARM_TIMER_CNT;
}

void arm_timer_clear_irq() {
	*(unsigned int*) ARM_TIMER_CLI = 0;
}

void arm_timer_setup(unsigned int timer_load, unsigned int timer_reload,
		unsigned int timer_divider, unsigned int prescale, timer_size_t ts) {
	arm_timer_disable();
	arm_timer_irq_disable();
	set_timer_ctrl(TIMER_DISABLE, TIMER_IRQ_DISABLE, prescale, TWENTY_THREE_BITS);
	load_timer(timer_load);
	set_timer_reload(timer_reload);
	set_timer_divider(timer_divider);
	arm_timer_clear_irq();
}

unsigned int arm_timer_enable() {
	unsigned int ignore;
	unsigned int irq_enable;
	unsigned int prescale;
	unsigned int tsize;
	unsigned int temp = get_timer_ctrl(&ignore, &irq_enable, &prescale, &tsize);
	set_timer_ctrl(TIMER_ENABLE, irq_enable, prescale, tsize);
	return temp;
}

void arm_timer_disable() {
	unsigned int ignore;
	unsigned int irq_enable;
	unsigned int prescale;
	unsigned int tsize;
	get_timer_ctrl(&ignore, &irq_enable, &prescale, &tsize);
	set_timer_ctrl(TIMER_DISABLE, irq_enable, prescale, tsize);
}

void arm_timer_irq_enable() {
	unsigned int enable;
	unsigned int ignore;
	unsigned int prescale;
	unsigned int tsize;
	get_timer_ctrl(&enable, &ignore, &prescale, &tsize);
	set_timer_ctrl(enable, TIMER_IRQ_ENABLE, prescale, tsize);
}

void arm_timer_irq_disable() {
	unsigned int enable;
	unsigned int ignore;
	unsigned int prescale;
	unsigned int tsize;
	get_timer_ctrl(&enable, &ignore, &prescale, &tsize);
	set_timer_ctrl(enable, TIMER_IRQ_DISABLE, prescale, tsize);
}

int arm_timer_irq_pending_raw() {
	return *(unsigned int*) ARM_TIMER_RIS;
}

int arm_timer_irq_pending() {
	return *(unsigned int*) ARM_TIMER_MIS;
}
