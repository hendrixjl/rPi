/*
 * mcp23008.h
 *
 *  Created on: Jan 6, 2013
 *      Author: jonathanhendrix
 */

#ifndef MCP23008_H_
#define MCP23008_H_

#include "i2c.h"
#include <stdint.h>
#include <vector>

class mcp23008
{
public:
	enum {
		PIN0 = 1,
		PIN1 = 1<<1,
		PIN2 = 1<<2,
		PIN3 = 1<<3,
		PIN4 = 1<<4,
		PIN5 = 1<<5,
		PIN6 = 1<<6,
		PIN7 = 1<<7,
		PIN_ALL = PIN0 | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7,
		INPUT = 1,
		OUTPUT = 0,
		NORMAL_LOGIC=0,
		INVERSE_LOGIC=1,
		ON=1,
		OFF=0,
		ACTIVE_HIGH_OUTPUT_IOCON=2,
		OPEN_DRAIN_OUTPUT_IOCON=4
	};

	mcp23008(uint8_t address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {}

	std::vector<uint8_t> get_registers() {
		static const uint32_t NUM_ELEMENTS = REGISTERS_END-1;
		std::vector<uint8_t> regs(NUM_ELEMENTS, 0);
		uint8_t *a = &regs[0];
		i2cbus_.query(addr_, IODIR, a, NUM_ELEMENTS);
		return regs;
	}

	unsigned char get_iodir() {
		return i2cbus_.query(addr_, IODIR);
	}

	void set_iodir(uint8_t pins, bool direction) {
		uint8_t iodir = get_iodir();
		if (direction == INPUT)
		{
    		 iodir |= pins;
		}
		else
		{
			iodir &= ~pins;
		}
		i2cbus_.command(addr_, IODIR, &iodir, 1);
	}

	uint8_t get_input_polarity() {
		return i2cbus_.query(addr_, IPOL);
	}

	uint8_t get_conf() {
		return i2cbus_.query(addr_, IOCON);
	}

	/**
	 * Sets the interrupt pin to active high
	 */
	void set_active_high_int() {
		uint8_t b = get_conf() | ACTIVE_HIGH_OUTPUT_IOCON;
		i2cbus_.command(addr_, IOCON, &b, 1);
	}

	/**
	 * Sets the interrupt pin to active low
	 */
	void set_active_low_int() {
		uint8_t b = get_conf() & (0xff - ACTIVE_HIGH_OUTPUT_IOCON);
		i2cbus_.command(addr_, IOCON, &b, 1);
	}

	/**
	 * Sets the interrupt pin to open drain
	 */
	void set_open_drain_int() {
		uint8_t b = get_conf() | OPEN_DRAIN_OUTPUT_IOCON;
		i2cbus_.command(addr_, IOCON, &b, 1);
	}

	/**
	 * Sets the interrupt pin to active driver
	 */
	void set_active_driver_int() {
		uint8_t b = get_conf() & (0xff - OPEN_DRAIN_OUTPUT_IOCON);
		i2cbus_.command(addr_, IOCON, &b, 1);
	}

	void set_input_polarity(uint8_t pins, bool direction) {
		uint8_t iodir = get_iodir();
		if (direction == INVERSE_LOGIC)
		{
    		 iodir |= pins;
		}
		else
		{
			iodir &= ~pins;
		}
		i2cbus_.command(addr_, IPOL, &iodir, 1);
	}

	uint8_t get_gpio() {
		return i2cbus_.query(addr_, GPIO);
	}

	void set_gpio(uint8_t pins, bool value) {
		uint8_t gpio = get_gpio();
		if (value == ON)
		{
			gpio |= pins;
		}
		else
		{
			gpio &= ~pins;
		}
		i2cbus_.command(addr_, GPIO, &gpio, 1);
	}

	uint8_t get_olat() {
		return i2cbus_.query(addr_, OLAT);
	}

	void set_olat(uint8_t pins, bool value) {
		uint8_t gpio = get_gpio();
		if (value == ON)
		{
			gpio |= pins;
		}
		else
		{
			gpio &= ~pins;
		}
		i2cbus_.command(addr_, OLAT, &gpio, 1);
	}

private:
	enum registers_t {
		IODIR=0x00,
		IPOL=0x01,
		GPINTEN=0x02,
		DEFVAL=0x03,
		INTCON=0x04,
		IOCON=0x05,
		GPPU=0x06,
		INTF=0x07,
		INTCAP=0x08,
		GPIO=0x09,
		OLAT=0x0A,
		REGISTERS_END
	};

	uint8_t addr_;
	i2c& i2cbus_;

	mcp23008(const mcp23008&); // no copy
	mcp23008 operator=(const mcp23008&); // no assign
};


#endif /* MCP23008_H_ */
