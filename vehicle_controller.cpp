#include "vehicle_controller.h"
#include "pca9685_pwm.h"
#include "gpio_dir_controller.h"
#include "make_unique"
#include <memory>

using namespace std;

shared_ptr<pca9685> get_pca9685_shared()
{
    enum { PCA9685_ADDRESS = 0x40 };
    static auto pca9685shared = 
        make_shared<pca9685>(PCA9685_ADDRESS, i2c::setup1());
    return pca9685shared;
}

vehicle_controller::vehicle_controller()
: fb_ctr_(make_unique<gpio_dir_controller>()),
  fb_power_(make_unique<pca_9685_pwm>(pca9685::pwmled::LED0, pca9685shared)),
  rl_ctr_(make_unique<gpio_dir_controller>()),
  rl_power_(make_unique<pca_9685_pwm>(pca9685::pwmled::LED1, pca9685shared))
{
}

