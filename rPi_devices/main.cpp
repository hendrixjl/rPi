#include "l3gd20.h"
#include "lsm303dlh.h"

#include <iostream>
using namespace std;

int main()
{
	enum {LSM303_A=0x19, LSM303_M=0x1E, L3GD20=0x6B };

	i2c& i2c1(i2c::setup(1));

	l3gd20 gyro(L3GD20,i2c1);

	gyro.enable();

	while (true)
	{
		sleep(1);

		cout << "Gyro address = " << hex << (unsigned)gyro.identify() << " temp=" << gyro.get_temp() << endl;

		lsm303dlh accel(LSM303_A,i2c1);

		cout << "accel address = " << hex << (unsigned)accel.identify() << " temp=" << accel.get_temp() << endl;
	}
}
