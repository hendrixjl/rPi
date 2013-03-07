/*
 * lsm303dlh.h
 *
 *  Created on: Feb 2, 2013
 *      Author: jonathanhendrix
 */

#ifndef LSM303DLH_ACCELEROMETER_H_
#define LSM303DLH_ACCELEROMETER_H_

#include "i2c.h"
#include "mytypes.h"

class lsm303dlh_accelerometer
{
public:
	lsm303dlh_accelerometer(uint8_t acc_address,
			i2c& i2cbus)
	: acc_addr_(acc_address),
	  i2cbus_(i2cbus) {}

	uint8_t accel_identify() {
		return i2cbus_.query(acc_addr_, WHO_AM_I_A);
	}

	void enable()
	{
	    // Enable accelerometer.
		enum {
			XEN = 1,
			YEN = 1<<1,
			ZEN = 1<<2,
			XYZEN = XEN | YEN | ZEN,
			LPEN = 1<<3,
			PWR_DWN = 0,
			ONE_HZ = 1<<4,
			TEN_HZ = 2<<4,
			TWENTYFIVE_HZ = 3<<4,
			FIFTY_HZ = 4<<4,
			ONE_HUNDRED_HZ = 5<<4,
			TWO_HUNDRED_HZ = 6<<4,
			FOUR_HUNDRED_HZ = 7<<4,
			TWO_G = 0 << 4,
			FOUR_G = 1 << 4,
			EIGHT_G = 2 << 4,
			SIXTEEN_G = 3 << 4,
			HIGH_RESOLUTION_OUTPUT = 8
		};
		uint8_t data = {ONE_HZ | XYZEN};
		i2cbus_.command(acc_addr_, CTRL_REG1_A, &data, 1);
		data = EIGHT_G | HIGH_RESOLUTION_OUTPUT;
		i2cbus_.command(acc_addr_, CTRL_REG4_A, &data, 1);
	}

	void getAcc(int16_t acc[3])
	{
	    uint8_t block[6];
	    i2cbus_.query(acc_addr_, OUT_X_L_A, block, sizeof(block));

	    acc[0] = (int16_t)(block[0] | block[1] << 8) >> 4;
	    acc[1] = (int16_t)(block[2] | block[3] << 8) >> 4;
	    acc[2] = (int16_t)(block[4] | block[5] << 8) >> 4;
	}

private:
	/**
	 * The registers for the Accelerometer (marked _A) and
	 * magnetometer (marked _M)
	 */
	enum registers_t {
		WHO_AM_I_A=0x0F,
		CTRL_REG1_A=0x20,
		CTRL_REG2_A,
		CTRL_REG3_A,
		CTRL_REG4_A,
		CTRL_REG5_A,
		CTRL_REG6_A,
		REFERENCE_A,
		STATUS_REG_A,
		OUT_X_L_A,
		OUT_X_H_A,
		OUT_Y_L_A,
		OUT_Y_H_A,
		OUT_Z_L_A,
		OUT_Z_H_A,
		FIFO_CTRL_REG_A,
		FIFO_SRC_REG_A,
		INT1_CFG_A,
		INT1_SOURCE_A,
		INT1_THS_A,
		INT1_DURATION_A,
		INT2_CFG_A,
		INT2_SOURCE_A,
		INT2_THS_A,
		INT2_DURATION_A,
		CLICK_CFG_A,
		CLICK_SRC_A,
		CLICK_THS_A,
		TIME_LIMIT_A,
		TIME_LATENCY_A,
		TIME_WINDOW_A,
	};
	uint8_t acc_addr_;
	i2c& i2cbus_;
};


#endif 
