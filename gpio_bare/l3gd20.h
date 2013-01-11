/*
 * l3gd20.h
 *
 *  Created on: Jan 5, 2013
 *      Author: jonathanhendrix
 */

#ifndef L3GD20_H_
#define L3GD20_H_

#include "i2c.h"

class l3gd20 {
public:
	l3gd20(unsigned char address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {}

	unsigned char identify() {
		return i2cbus_.query(addr_, WHO_AM_I);
	}

	enum {
		PD=1<<3,
		XEN=1 | PD,
		YEN=1<<1 | PD,
		ZEN=1<<2 | PD,
		XYZEN= XEN | YEN | ZEN
	};

	void enable(unsigned char bits = XYZEN) {
		i2cbus_.command(addr_, CNTRL_REG1, &bits, 1);
	}

	unsigned int get_temp() {
		return i2cbus_.query(addr_, OUT_TEMP);
	}

	bool measurements(short& temp, unsigned char& status, short& x, short& y, short& z)
	{
		bool rst = false;
		enum { BYTES_IN_MEASUREMENT=8 };
		unsigned char buffer[BYTES_IN_MEASUREMENT];
		if (i2cbus_.query(addr_, OUT_TEMP, buffer, BYTES_IN_MEASUREMENT))
		{
			temp = buffer[0];
			status = buffer[1];
			x = buffer[2] + buffer[3]*0x0100;
			y = buffer[4] + buffer[5]*0x0100;
			z = buffer[6] + buffer[7]*0x0100;
			rst = true;
		}
		return rst;
	}

	unsigned char get_ctrl1() {
		return i2cbus_.query(addr_, CNTRL_REG1);
	}

private:

	enum registers_t {
		WHO_AM_I=0x0F,
		CNTRL_REG1=0x20,
		CNTRL_REG2=0x21,
		CNTRL_REG3=0x22,
		CNTRL_REG4=0x23,
		CNTRL_REG5=0x24,
		REFERENCE=0x25,
		OUT_TEMP=0x26,
		STATUS_REG=0x27,
		OUT_X_L=0x28,
		OUT_X_H=0x29,
		OUT_Y_L=0x2A,
		OUT_Y_H=0x2B,
		OUT_Z_L=0x2C,
		OUT_Z_H=0x2D,
		FIFO_CTRL_REG=0x2E,
		FIFO_SRC_REG=0x2F
	};

	unsigned char addr_;
	i2c& i2cbus_;

	l3gd20(const l3gd20&); // no copy
	l3gd20& operator=(const l3gd20&); // no assign
};

#endif /* L3GD20_H_ */
