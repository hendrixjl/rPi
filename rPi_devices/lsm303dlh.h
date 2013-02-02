/*
 * lsm303dlh.h
 *
 *  Created on: Feb 2, 2013
 *      Author: jonathanhendrix
 */

#ifndef LSM303DLH_H_
#define LSM303DLH_H_
#include "i2c.h"

class lsm303dlh
{
public:
	lsm303dlh(unsigned char address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {}

	unsigned char identify() {
		return i2cbus_.query(addr_, WHO_AM_I_A);
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
		OUT_Z_H_A,
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
		CRA_REG_M=0x00,
		CRB_REG_M,
		MR_REG_M,
		OUT_X_H_M,
		OUT_X_L_M,
		OUT_Z_H_M,
		OUT_Z_L_M,
		OUT_Y_H_M,
		OUT_Y_L_M,
		SR_REG_M,
		IRA_REG_M,
		IRB_REG_M,
		IRC_REG_M,
		TEMP_OUT_H_M=0x31,
		TEMP_OUT_L_M
	};
	unsigned char addr_;
	i2c& i2cbus_;
};


#endif /* LSM303DLH_H_ */
