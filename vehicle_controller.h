#ifndef __VEHICLE_CONTROLLER_H__
#define __VEHICLE_CONTROLLER_H__

#include <memory>
#include "direction_ctrl.h"
#include "pwm_driver.h"


class vehicle_controller
{
public:
    enum class fb_dir { FORWARD, STOP, BACKWARD };
    enum class rl_dir { RIGHT, STOP, LEFT };
    
    vehicle_controller();

    void fb_control(fb_dir fbd, int power) {
        switch (fbd) {
        case fb_dir::FORWARD: fb_ctr_->go(); fb_power_->set_duty(power); break;
        case fb_dir::STOP: fb_ctr_->stop(); fb_power_->set_duty(0); break;
        case fb_dir::BACKWARD: fb_ctr_->back(); fb_power_->set_duty(power); break;
        }
    }
    
    void rl_control(rl_dir rld, int power) {
        switch (rld) {
        case rl_dir::RIGHT: rl_ctr_->go(); fb_power_->set_duty(power); break;
        case rl_dir::STOP: rl_ctr_->stop(); fb_power_->set_duty(0); break;
        case rl_dir::LEFT: rl_ctr_->back(); fb_power_->set_duty(power); break;
        }
    }

private:
    std::unique_ptr<direction_ctrl> fb_ctr_;
    std::unique_ptr<pwm_driver> fb_power_;
    std::unique_ptr<direction_ctrl> rl_ctr_;
    std::unique_ptr<pwm_driver> rl_power_;
};


#endif
