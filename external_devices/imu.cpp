
#include "imu.h"

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
}

imu::~imu()
{
}

//		short temp; unsigned char status; short xa; short ya; short za;
//		gyro.measurements(temp, status, xa, ya, za);
//		int16_t accels[3] = {};
//		accel.getAcc(accels);
//		int16_t mags[3] = {};
//		accel.getMag(mags);
//		cout << "Gyro: " << temp << " " << xa << " " << ya << " " << za
//				<< " accel: " << accels[0] << " " << accels[1] << " " << accels[2]
//				<< " mags: " << mags[0] << " " << mags[1] << " " << mags[2]
//				<< endl;

//l3gd20 gyro(L3GD20,i2c1);
//gyro.enable();
//
//lsm303dlh accel(LSM303_M, LSM303_A, i2c1);
//accel.enable();
