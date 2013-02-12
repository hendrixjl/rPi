/*
 * l3gd20.h
 *
 *  Created on: Jan 5, 2013
 *      Author: jonathanhendrix
 */

#ifndef L3GD20_H_
#define L3GD20_H_

#include "i2c.h"
#include <stdint.h>

//    Usage
//    enum { LG3D20_ADDR=0x06B };
//    l3gd20 gyro(LG3D20_ADDR, i2c1);
//    gyro.enable();
//    short address = gyro.identify();
//    short temp=0;
//    uint8_t status=0;
//    short x=0,y=0,z=0;
//    if (gyro.measurements(temp, status, x, y, z))
//    {
//		// use data
//    }
//    else
//    {
//    	// no data update
//    }

class l3gd20 {
public:
	l3gd20(uint8_t address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {}

	uint8_t identify() {
		return i2cbus_.query(addr_, WHO_AM_I);
	}

	enum {
		PD=1<<3,
		XEN=1 | PD,
		YEN=1<<1 | PD,
		ZEN=1<<2 | PD,
		XYZEN= XEN | YEN | ZEN
	};

	void enable(uint8_t bits = XYZEN) {
		i2cbus_.command(addr_, CNTRL_REG1, &bits, 1);
		uint8_t data[] = { 0x20 };
		i2cbus_.command(addr_, CNTRL_REG4, data, sizeof(data));
	}

	unsigned int get_temp() {
		return i2cbus_.query(addr_, OUT_TEMP);
	}

	bool measurements(short& temp, uint8_t& status, int16_t& x, int16_t& y, int16_t& z)
	{
		bool rst = false;
		enum { BYTES_IN_MEASUREMENT=8 };
		uint8_t buffer[BYTES_IN_MEASUREMENT];
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

	bool getAngles(int16_t a[3])
	{
		bool rst = false;
		enum { BYTES_IN_MEASUREMENT=6 };
		uint8_t buffer[BYTES_IN_MEASUREMENT];
		if (i2cbus_.query(addr_, OUT_X_L, buffer, BYTES_IN_MEASUREMENT))
		{
			a[0] = buffer[0] + buffer[1]*0x0100;
			a[1] = buffer[2] + buffer[3]*0x0100;
			a[2] = buffer[4] + buffer[5]*0x0100;
		}
		return rst;
	}

	uint8_t get_ctrl1() {
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

	uint8_t addr_;
	i2c& i2cbus_;

	l3gd20(const l3gd20&); // no copy
	l3gd20& operator=(const l3gd20&); // no assign
};

#endif /* L3GD20_H_ */
