#include "vehicle_controller.h"
#include "pwm_driver.h"
#include "direction_ctrl.h"

using namespace std;

vehicle_controller vehicle_controller()
: fb_ctr_(),
  fb_power_(),
  rl_ctr_(),
  rl_power_()
{
	
}

