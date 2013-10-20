#ifndef __VEHICLE_CONTROLLER_H__
#define __VEHICLE_CONTROLLER_H__

#include <memory>

class vehicle_controller
{
public:
    enum class fb_dir { FORWARD, STOP, BACKWARD };
    enum class fl_dir { RIGHT, STOP, LEFT };
    
    vehicle_controller();

    void fb_control(fb_dir, power) {
        switch fb_dir {
        case FOWARD: fb_ctr_->go(); fb_power_->set_duty(power); break;
        case STOP: fb_ctr_->stop(); fb_power_->set_duty(0); break;
        case FOWARD: fb_ctr_->back(); fb_power_->set_duty(power); break;
        }
    }
    
    void rl_control(rl_dir, power) {
        switch rl_dir {
        case RIGHT: rl_ctr_->go(); fb_power_->set_duty(power); break;
        case STOP: rl_ctr_->stop(); fb_power_->set_duty(0); break;
        case LEFT: rl_ctr_->back(); fb_power_->set_duty(power); break;
    }

private:
    unique_ptr<direction_ctrl> fb_ctr_;
    unique_ptr<pwm_driver> fb_power_;
    unique_ptr<direction_ctrl> rl_ctr_;
    unique_ptr<pwm_driver> rl_power_;
};


#endif
