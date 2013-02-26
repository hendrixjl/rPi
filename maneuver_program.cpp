/*
 * maneuver_program.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include "stdout.h"
#include "gpio.h"
#include "l3gd20.h"
#include "i2c.h"
#include "lsm303dlh.h"
#include "mcp23008.h"
#include "timeUtils.h"

void pause_till_signal()
{
	gpio_set_fsel(PIN_25, INTPUT);
	gpio_set_pud(PIN_25, ENABLE_PULL_UP_CNTRL);
	while (gpio_get_level(PIN_25) == PIN_HIGH);
//	gpio_set_event_detect(PIN_25, FALLING_EDGE_DETECT);
//	gpio_clear_event_detected(PIN_25);
//	while (!gpio_event_detected(PIN_25));
}

void maneuver_program()
{
	i2c& i2c1(i2c::setup(1));
	i2c1.enable();

	enum {LSM303_A=0x19, LSM303_M=0x1E, L3GD20=0x6B, MCP23008=0x20 };

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

	gpio.set_iodir(FORWARD_BACK_ENABLE | FORWARD | BACKWARD , mcp23008::OUTPUT);

	gpio.set_input_polarity(FORWARD_BACK_ENABLE | FORWARD | BACKWARD, mcp23008::NORMAL_LOGIC);

	gpio.set_olat(FORWARD_BACK_ENABLE | FORWARD | BACKWARD, mcp23008::OFF);

	struct command_t {
		uint8_t olat;
		int speed;
		const char* msg;
	};

	command_t *commands = {
		command_t{FORWARD_BACK_ENABLE + FORWARD, 100, "FORWARD"},
		command_t{FORWARD_BACK_DISABLE + FORWARD, 75, "STOP"},
		command_t{FORWARD_BACK_ENABLE + BACKWARD, 50, "BACKWARD"},
		command_t{FORWARD_BACK_DISABLE + BACKWARD, 25, "STOP"},
		nullptr
	};

	auto it = commands;
	while (it != nullptr)
	{
		udelay(1000);
		setServo(it->speed);
		gpio.set_olat(it->olat);
		gpio.set_olat(it->olat);
		write("dir: ");
		write(it->msg);
		writeln();

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

	udelay(1000);
	gpio.set_olat(mcp23008::PIN_ALL, mcp23008::OFF);
	gpio.set_iodir(mcp23008::PIN_ALL, mcp23008::INPUT);
}
