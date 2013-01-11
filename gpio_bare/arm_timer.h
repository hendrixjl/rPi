/*
 * arm_timer.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jonathanhendrix
 */

#ifndef ARM_TIMER_H_
#define ARM_TIMER_H_

class arm_timer_t {
public:
	static arm_timer_t& get_reference() {
		static arm_timer_t just_one;
		return just_one;
	}

	enum prescale_ctrl_t {
		PRESCALE_IS_CLOCK_DIV_1 = 0,
		PRESCALE_IS_CLOCK_DIV_16 = 1,
		PRESCALE_IS_CLOCK_DIV_256 = 2,
		PRESCALE_IS_CLOCK_DIV_1_PRIME = 3 // @TODO don't understand
	};

	enum timer_size_t {
		SIXTEEN_BITS = 0,
		TWENTY_THREE_BITS = 1
	};

	unsigned int get_current_val() const;

	unsigned int get_free_val() const;

	void clear_timer_irq();

	void setup(unsigned int timer_load,
			unsigned int timer_reload,
			unsigned int timer_divider,
			prescale_ctrl_t prescale = PRESCALE_IS_CLOCK_DIV_1,
			timer_size_t ts = TWENTY_THREE_BITS);

	unsigned int enable();

	void disable();

	void irq_enable();

	void irq_disable();

	bool irq_pending_raw() const;

	bool irq_pending() const;

	unsigned int get_timer_ctrl() const;

#ifndef CPPUNIT_TEST
private:
#endif

	volatile unsigned int *bar_;

	enum {
		ARM_TIMER_LOD = 0x00,
		ARM_TIMER_VAL = 0x01, // integer pointer arithmetic
		ARM_TIMER_CTL = 0x02,
		ARM_TIMER_CLI = 0x03,
		ARM_TIMER_RIS = 0x04,
		ARM_TIMER_MIS = 0x05,
		ARM_TIMER_RLD = 0x06,
		ARM_TIMER_DIV = 0x07,
		ARM_TIMER_CNT = 0x08
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
			bool enable,
			bool irq_enable,
			prescale_ctrl_t p,
			timer_size_t ts = TWENTY_THREE_BITS);

	unsigned int get_timer_ctrl(bool& enable,
			bool& irq_enable,
			prescale_ctrl_t& p,
			timer_size_t& ts) const;

	unsigned int load_timer(unsigned int i);

	void set_timer_reload(unsigned int i);

	void set_timer_divider(unsigned int i);

	explicit arm_timer_t(unsigned int *bar=reinterpret_cast<unsigned int*>(0x2000B400))
    : bar_ (bar) {
	}

	arm_timer_t(const arm_timer_t&); // no copy
	arm_timer_t& operator=(const arm_timer_t&); // no assign
};

#endif /* ARM_TIMER_H_ */
