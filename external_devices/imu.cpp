#include "imu.h"
#include "stdout.h"

enum {
	LSM303_A=0x19,
	LSM303_M=0x1E,
	L3GD20=0x6B
};

imu::imu(i2c& ani2c)
: gyro_(L3GD20, ani2c),
  acceleromter_(LSM303_M, LSM303_A, ani2c),
  heading_(0.0),
  inclination_(0.0),
  roll_(0.0)
{
	l3gd20 gyro(L3GD20,i2c1);
	gyro.enable();

	lsm303dlh accel(LSM303_M, LSM303_A, i2c1);
	accel.enable();
}

imu::~imu()
{
}

void imu::integrate()
{
	write(getTime()); write(',');
	int16_t angles[3];
	gyro.measurements(angles);
	write(angles[0]); write(',');
	write(angles[1]); write(',');
	write(angles[2]); write(',');

	int16_t accels[3] = {};
	accel.getAcc(accels);
	write(accels[0]); write(',');
	write(accels[1]); write(',');
	write(accels[2]); write(',');

	int16_t mags[3] = {};
	accel.getMag(mags);
	write(mags[0]); write(',');
	write(mags[1]); write(',');
	writeln(mags[2]); write(',');
}
