#include "l3gd20.h"
#include "lsm303dlh.h"
#include "mcp23008.h"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	enum {LSM303_A=0x19, LSM303_M=0x1E, L3GD20=0x6B, MCP23008=0x20 };

	i2c& i2c1(i2c::setup(1));

	l3gd20 gyro(L3GD20,i2c1);
	gyro.enable();

	lsm303dlh accel(LSM303_M, LSM303_A, i2c1);

	mcp23008 gpio(MCP23008, i2c1);

	enum { FORWARD=mcp23008::PIN7, BACK=mcp23008::PIN6, RIGHT=mcp23008::PIN4, LEFT=mcp23008::PIN2 };

	gpio.set_iodir(FORWARD | BACK | RIGHT | LEFT, mcp23008::OUTPUT);

	typedef unsigned char direction_t;
	typedef unsigned char direction_state_t;
	struct command_t {
		direction_t dir;
		direction_state_t state;
	};

	vector<command_t> commands{
		command_t{FORWARD, mcp23008::ON},
		command_t{FORWARD | RIGHT,mcp23008::ON},
		command_t{RIGHT, mcp23008::OFF},
		command_t{FORWARD | LEFT, mcp23008::ON},
		command_t{FORWARD | LEFT, mcp23008::OFF},
		command_t{BACK, mcp23008::ON},
		command_t{BACK | LEFT, mcp23008::ON},
		command_t{BACK, mcp23008::OFF},
		command_t{BACK | RIGHT, mcp23008::ON},
		command_t{BACK | RIGHT, mcp23008::OFF},
		command_t{FORWARD, mcp23008::ON},
		command_t{FORWARD | RIGHT,mcp23008::ON},
		command_t{RIGHT, mcp23008::OFF},
		command_t{FORWARD | LEFT, mcp23008::ON},
		command_t{FORWARD | LEFT, mcp23008::OFF},
		command_t{BACK, mcp23008::ON},
		command_t{BACK | LEFT, mcp23008::ON},
		command_t{BACK, mcp23008::OFF},
		command_t{BACK | RIGHT, mcp23008::ON},
		command_t{BACK | RIGHT, mcp23008::OFF},
		command_t{FORWARD, mcp23008::ON},
		command_t{FORWARD | RIGHT,mcp23008::ON},
		command_t{RIGHT, mcp23008::OFF},
		command_t{FORWARD | LEFT, mcp23008::ON},
		command_t{FORWARD | LEFT, mcp23008::OFF},
		command_t{BACK, mcp23008::ON},
		command_t{BACK | LEFT, mcp23008::ON},
		command_t{BACK, mcp23008::OFF},
		command_t{BACK | RIGHT, mcp23008::ON},
		command_t{BACK | RIGHT, mcp23008::OFF},
		command_t{FORWARD, mcp23008::ON},
		command_t{FORWARD | RIGHT,mcp23008::ON},
		command_t{RIGHT, mcp23008::OFF},
		command_t{FORWARD | LEFT, mcp23008::ON},
		command_t{FORWARD | LEFT, mcp23008::OFF},
		command_t{BACK, mcp23008::ON},
		command_t{BACK | LEFT, mcp23008::ON},
		command_t{BACK, mcp23008::OFF},
		command_t{BACK | RIGHT, mcp23008::ON},
		command_t{BACK | RIGHT, mcp23008::OFF},
	};

	auto it = commands.begin();
	while (it != commands.end())
	{
		usleep(500);
		gpio.set_olat(it->dir, it->state);
		++it;
		short temp; unsigned char status; short xa; short ya; short za;
		gyro.measurements(temp, status, xa, ya, za);
		uint16_t accels[3] = {};
		accel.getAcc(accels);
		uint16_t mags[3] = {};
		accel.getMag(mags);
		cout << "Gyro: " << temp << " " << xa << " " << ya << " " << za
				<< " accel: " << accels[0] << " " << accels[1] << " " << accels[2]
				<< " mags: " << mags[0] << " " << mags[1] << " " << mags[2]
				<< endl;
	}
}
