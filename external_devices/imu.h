#ifndef IMU_H_
#define IMU_H_

#include "l3gd20.h"
#include "lsm303dlh.h"

class i2c;

class imu {
public:
	imu(i2c&);
	~imu();

	float get_heading();

	float get_inclination();

	/**
	 *
	 */
	float get_roll();

	/**
	 * Calculate calibration data for the imu
	 */
	void calibrate();

	/**
	 * Integrate data from the sensors.
	 * This routine should run periodically.
	 */
	void integrate();

private:
	l3gd20 gyro_;
	lsm303dlh accelerometer_;
	float heading_;
	float inclination_;
	float roll_;
};

#endif /* IMU_H_ */
