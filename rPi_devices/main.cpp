#include "l3gd20.h"
#include "lsm303dlh.h"

#include <iostream>
using namespace std;

int main()
{
	enum {LSM303_A=0x19, LSM303_M=0x1E, L3GD20=0x6B };

	i2c& i2c1(i2c::setup(1));

	i2c1.enable();

	l3gd20 gyro(L3GD20,i2c1);

	cout << "Gyro address = " << hex << gyro.identify() << endl;

	lsm303dlh accel(LSM303_A,i2c1);

	cout << "accel address = " << hex << accel.identify() << endl;
}
