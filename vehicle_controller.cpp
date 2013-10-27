#include "vehicle_controller.h"
#include "pca9685_pwm.h"
#include "gpio_dir_controller.h"
#include "make_unique.h"
#include <memory>

using namespace std;

vehicle_controller vehicle_controller()
: fb_ctr_(make_unique<gpio_dir_controller>()),
  fb_power_(),
  rl_ctr_(make_unique<gpio_dir_controller>()),
  rl_power_()
{
	enum { PCA9685_ADDRESS = 0x40 };
	auto pca9685shared = 
	    make_shared<pca9685>(PCA9685_ADDRESS, i2c::setup1()));

	fb_power_ = 
	    make_unique<pwm_driver>(pca_9685_pwm(pca9685::pwmled::LED0, 
	             pca9685shared);
	             
	rl_power_ = 
	    make_unique<pwm_driver>(pca_9685_pwm(pca9685::pwmled::LED1, 
	             pca9685shared);
	             
}

