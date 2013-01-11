/*
 * arm_timer.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: jonathanhendrix
 */

#include "arm_timer.h"

unsigned int arm_timer_t::get_current_val() const {
	return bar_[ARM_TIMER_VAL];
}

unsigned int arm_timer_t::get_free_val() const {
	return bar_[ARM_TIMER_CNT];
}

void arm_timer_t::clear_timer_irq() {
	bar_[ARM_TIMER_CLI] = 0;
}

void arm_timer_t::setup(unsigned int timer_load, unsigned int timer_reload,
		unsigned int timer_divider, prescale_ctrl_t prescale, timer_size_t ts) {
	disable();
	irq_disable();
	set_timer_ctrl(TIMER_DISABLE, TIMER_IRQ_DISABLE, prescale);
	load_timer(timer_load);
	set_timer_reload(timer_reload);
	set_timer_divider(timer_divider);
	clear_timer_irq();
}

unsigned int arm_timer_t::enable() {
	bool ignore;
	bool irq_enable;
	prescale_ctrl_t prescale;
	timer_size_t tsize;
	unsigned int temp = get_timer_ctrl(ignore, irq_enable, prescale, tsize);
	set_timer_ctrl(TIMER_ENABLE, irq_enable, prescale, tsize);
	return temp;
}

void arm_timer_t::disable() {
	bool ignore;
	bool irq_enable;
	prescale_ctrl_t prescale;
	timer_size_t tsize;
	get_timer_ctrl(ignore, irq_enable, prescale, tsize);
	set_timer_ctrl(TIMER_DISABLE, irq_enable, prescale, tsize);
}

void arm_timer_t::irq_enable() {
	bool enable;
	bool ignore;
	prescale_ctrl_t prescale;
	timer_size_t tsize;
	get_timer_ctrl(enable, ignore, prescale, tsize);
	set_timer_ctrl(enable, TIMER_IRQ_ENABLE, prescale, tsize);
}

void arm_timer_t::irq_disable() {
	bool enable;
	bool ignore;
	prescale_ctrl_t prescale;
	timer_size_t tsize;
	get_timer_ctrl(enable, ignore, prescale, tsize);
	set_timer_ctrl(enable, TIMER_IRQ_DISABLE, prescale, tsize);
}

bool arm_timer_t::irq_pending_raw() const {
	return bar_[ARM_TIMER_RIS];
}

bool arm_timer_t::irq_pending() const {
	return bar_[ARM_TIMER_MIS];
}

unsigned int arm_timer_t::get_timer_ctrl() const {
	return bar_[ARM_TIMER_CTL];
}

unsigned int arm_timer_t::set_timer_ctrl(
		bool enable,
		bool irq_enable,
		prescale_ctrl_t p,
		timer_size_t ts) {
	enum {
		RESET_PRESCALER = 0x3E  // from BCM2835-ARM-Peripherals
	};

	unsigned int temp = (RESET_PRESCALER << TIMER_PRESCALE_BYTE_BIT)
			+ (enable << TIMER_ENABLE_BIT)
			+ (irq_enable << TIMER_INT_ENABLE_BIT)
			+ (p << TIMER_PRESCALE_BIT)
			+ (ts << TIMER_SIZE_BIT);

	bar_[ARM_TIMER_CTL] = temp;
	return temp;
}

unsigned int arm_timer_t::get_timer_ctrl(bool& enable, bool& irq_enable,
		prescale_ctrl_t& p, timer_size_t& ts) const {
	unsigned int temp = bar_[ARM_TIMER_CTL];
	enable = (temp & (1 << TIMER_ENABLE_BIT));
	irq_enable = (temp & (1 << TIMER_INT_ENABLE_BIT));
	enum {
		TIMER_PRESCALE_MASK = 0x03 // all bits set
	};
	p = static_cast<prescale_ctrl_t>((temp >> TIMER_PRESCALE_BIT)
			& TIMER_PRESCALE_MASK);
	ts = (temp & (1 << TIMER_SIZE_BIT)) ? TWENTY_THREE_BITS : SIXTEEN_BITS;
	return bar_[ARM_TIMER_CTL];
}

unsigned int arm_timer_t::load_timer(unsigned int i) {
	bar_[ARM_TIMER_LOD] = i;
	return bar_[ARM_TIMER_LOD];
}

void arm_timer_t::set_timer_reload(unsigned int i) {
	bar_[ARM_TIMER_RLD] = i;
}

void arm_timer_t::set_timer_divider(unsigned int i) {
	bar_[ARM_TIMER_DIV] = i;
}
