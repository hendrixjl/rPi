#include "imu.h"
#include "stdout.h"
#include "timeUtils.h"

enum {
	LSM303_A=0x19,
	LSM303_M=0x1E,
	L3GD20=0x6B
};

imu::imu(i2c& ani2c)
: gyro_(L3GD20, ani2c),
  accelerometer_(LSM303_M, LSM303_A, ani2c),
  heading_(0.0),
  inclination_(0.0),
  roll_(0.0)
{
	gyro_.enable();
	accelerometer_.enable();
}

imu::~imu()
{
}

void imu::integrate()
{
	write(getTime()); write(',');
	int16_t angles[3];
	gyro_.getAngles(angles);
	write(angles[0]); write(',');
	write(angles[1]); write(',');
	write(angles[2]); write(',');

	int16_t accels[3] = {};
	accelerometer_.getAcc(accels);
	write(accels[0]); write(',');
	write(accels[1]); write(',');
	write(accels[2]); write(',');

	int16_t mags[3] = {};
	accelerometer_.getMag(mags);
	write(mags[0]); write(',');
	write(mags[1]); write(',');
	writeln(mags[2]); write(',');
}
