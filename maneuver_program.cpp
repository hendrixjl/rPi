/*
 * maneuver_program.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include "stdout.h"
#include "gpio.h"
#include "i2c.h"
#include "imu.h"
#include "crawler.h"
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
	gpio_set_fsel(PIN_18, ALT1);

	write("Waiting for signal");
	writeln();
//	pause_till_signal();
	write("Signal!");
	writeln();
	
	i2c& i2c1(i2c::setup(1));
	i2c1.enable();

	imu myimu(i2c1);
	// start_imu_integration(myimu);

	crawler mycrawler(i2c1);

	static const crawler::maneuver_t commands[] = {
			crawler::maneuver_t{crawler::FORWARD_DIRECTION, 50, crawler::NO_CHANGE_TURN, 0},
			crawler::maneuver_t{crawler::NO_CHANGE_DIRECTION, 20, crawler::RIGHT_TURN, 10},
			crawler::maneuver_t{crawler::STOP_DIRECTION, 0, crawler::STOP_TURN, 0},
			crawler::maneuver_t{crawler::BACKWARD_DIRECTION, 80, crawler::NO_CHANGE_TURN, 0},
			crawler::maneuver_t{crawler::NO_CHANGE_DIRECTION, 100, crawler::LEFT_TURN, 50},
			crawler::maneuver_t{crawler::STOP_DIRECTION, 0, crawler::STOP_TURN, 0}
	};

	for (auto i=0U; i<sizeof(commands)/sizeof(crawler::maneuver_t); ++i)
	{
		mycrawler.maneuver(commands[i]);
		udelay(1000);
	}

	udelay(1000);
}
