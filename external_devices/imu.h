#ifndef IMU_H_
#define IMU_H_

#include "l3gd20.h"
#include "lsm303dlh_accelerometer.h"
#include "lsm303dlh_magnetometer.h"

#include "Core"
#include "Geometry"

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

	Eigen::Matrix3f rotationFromCompass(const Eigen::Vector3f& acceleration, const Eigen::Vector3f& magnetic_field);

	typedef void fuse_function(Eigen::Quaternionf& rotation, float dt, const Eigen::Vector3f& angular_velocity,
	                  const Eigen::Vector3f& acceleration, const Eigen::Vector3f& magnetic_field);

	void fuse_compass_only(Eigen::Quaternionf& rotation, float dt, const Eigen::Vector3f& angular_velocity,
	  const Eigen::Vector3f& acceleration, const Eigen::Vector3f& magnetic_field);

	// Uses the given angular velocity and time interval to calculate
	// a rotation and applies that rotation to the given quaternion.
	// w is angular velocity in radians per second.
	// dt is the time.
	void rotate(Eigen::Quaternionf& rotation, const Eigen::Vector3f& w, float dt);

	void fuse_gyro_only(Eigen::Quaternionf& rotation, float dt, const Eigen::Vector3f& angular_velocity,
	  const Eigen::Vector3f& acceleration, const Eigen::Vector3f& magnetic_field);

	void fuse_default(Eigen::Quaternionf& rotation, float dt, const Eigen::Vector3f& angular_velocity,
	  const Eigen::Vector3f& acceleration, const Eigen::Vector3f& magnetic_field);
};

#endif /* IMU_H_ */
