#ifndef IMU_H_
#define IMU_H_

#include "l3gd20.h"
#include "lsm303dlh_accelerometer.h"
#include "lsm303dlh_magnetometer.h"

#include "Core"
#include "Geometry"
typedef Eigen::Vector3f vector;
typedef Eigen::Vector3i int_vector;
typedef Eigen::Matrix3f matrix;
typedef Eigen::Quaternionf quaternion;

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
	lsm303dlh_accelerometer accelerometer_;
	lsm303dlh_magnetometer magnetometer_;
	float heading_;
	float inclination_;
	float roll_;

	matrix rotationFromCompass(const vector& acceleration, const vector& magnetic_field);

};

#endif /* IMU_H_ */
