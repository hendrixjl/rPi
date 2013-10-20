/*
 * maneuver_program.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include "gpio.h"
#include "i2c.h"
#include "imu.h"
#include "vehicle_controller.h"
#include "timeUtils.h"
#include "pca9685.h"

#include <iostream>
using namespace std;

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

	imu myimu(i2c1);
	// start_imu_integration(myimu);

    vehicle_controller vc;
    
    vc.fb_control(vehicle_controller::fb_dir::FORWARD, 30);
	udelay(1000);
    
    vc.rl_control(vehicle_controller::rl_dir::RIGHT, 10);
	udelay(1000);
    
    vc.fb_control(vehicle_controller::fb_dir::STOP, 30);
	udelay(1000);
    
    vc.rl_control(vehicle_controller::rl_dir::LEFT, 10);
	udelay(1000);
    
    vc.fb_control(vehicle_controller::fb_dir::BACKWARD, 20);
	udelay(1000);
        
}
