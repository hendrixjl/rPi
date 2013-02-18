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
		OFF=0
	};

	mcp23008(uint8_t address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {}

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

	unsigned char get_input_polarity() {
		return i2cbus_.query(addr_, IPOL);
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

	void set_olat(uint8_t value) {
		i2cbus_.command(addr_, OLAT, &value, 1);
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
	enum registers_1 {
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
		OLAT=0x0A
	};

	uint8_t addr_;
	i2c& i2cbus_;

	mcp23008(const mcp23008&); // no copy
	mcp23008 operator=(const mcp23008&); // no assign
};


#endif /* MCP23008_H_ */
