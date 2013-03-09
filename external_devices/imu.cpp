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
  accelerometer_(LSM303_A, ani2c),
  magnetometer_(LSM303_M, ani2c),
  heading_(0.0),
  inclination_(0.0),
  roll_(0.0)
{
	gyro_.enable();
	accelerometer_.enable();
	magnetometer_.enable();
}

imu::~imu()
{
}

void imu::integrate()
{
	write(getTime()); write(',');
	int16_t angles[3];
	int16_t accels[3] = {};
	int16_t mags[3] = {};

        gyro_.getAngles(angles);
	accelerometer_.getAcc(accels);
	magnetometer_.getMag(mags);

	write(angles[1]); write(',');
	write(angles[2]); write(',');

	write(accels[0]); write(',');
	write(accels[1]); write(',');
	write(accels[2]); write(',');

	write(mags[0]); write(',');
	write(mags[1]); write(',');
	writeln(mags[2]); write(',');
}

matrix rotationFromCompass(const vector& acceleration, const vector& magnetic_field)
{
    vector down = -acceleration;     // usually true
    vector east = down.cross(magnetic_field); // actually it's magnetic east
    vector north = east.cross(down);

    east.normalize();
    north.normalize();
    down.normalize();

    matrix r;
    r.row(0) = north;
    r.row(1) = east;
    r.row(2) = down;
    return r;
}
