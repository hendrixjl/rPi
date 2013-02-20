#include "l3gd20.h"
#include "lsm303dlh.h"
#include "mcp23008.h"

#include <iostream>
#include <vector>
using namespace std;

void dump(mcp23008& gpio)
{
	cout << "mcp23008 regs: ";
	const auto& v = gpio.get_registers();
	cout << "(" << v.size() << ")" << endl;
	for (auto it: v)
	{
		cout << " " << hex << unsigned(it);
	}
	cout << dec << endl;
}

int main()
{
	init_bars();
	enum {LSM303_A=0x19, LSM303_M=0x1E, L3GD20=0x6B, MCP23008=0x20 };

	i2c& i2c1(i2c::setup(1));

	l3gd20 gyro(L3GD20,i2c1);
	gyro.enable();

	lsm303dlh accel(LSM303_M, LSM303_A, i2c1);
	accel.enable();

	mcp23008 gpio(MCP23008, i2c1);

	enum {
		FORWARD_BACK_ENABLE=mcp23008::PIN0,
		FORWARD_BACK_DISABLE=0,
		FORWARD=mcp23008::PIN1,
		BACKWARD=mcp23008::PIN2,
	};

	cout << "pins = " << unsigned(FORWARD_BACK_ENABLE | FORWARD | BACKWARD ) << endl;
	gpio.set_iodir(FORWARD_BACK_ENABLE | FORWARD | BACKWARD , mcp23008::OUTPUT);
	cout << "io dir=" << hex << unsigned(gpio.get_iodir()) << dec << endl;

	gpio.set_input_polarity(FORWARD_BACK_ENABLE | FORWARD | BACKWARD, mcp23008::NORMAL_LOGIC);

	gpio.set_olat(FORWARD_BACK_ENABLE | FORWARD | BACKWARD, mcp23008::OFF);

	struct command_t {
		uint8_t olat;
		string msg;
	};

	vector<command_t> commands{
		command_t{FORWARD_BACK_ENABLE + FORWARD, "FORWARD"},
		command_t{FORWARD_BACK_DISABLE + FORWARD, "STOP"},
		command_t{FORWARD_BACK_ENABLE + BACKWARD, "BACKWARD"},
		command_t{FORWARD_BACK_DISABLE + BACKWARD, "STOP"},
	};

	auto it = commands.begin();
	while (it != commands.end())
	{
		sleep(1);
		gpio.set_olat(it->olat);
		gpio.set_olat(it->olat);
		cout << "dir: " << it->msg << " " << endl;
		++it;
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
	}

	sleep(1);
	gpio.set_olat(mcp23008::PIN_ALL, mcp23008::OFF);
	gpio.set_iodir(mcp23008::PIN_ALL, mcp23008::INPUT);
}
