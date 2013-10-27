#ifndef __PCA_9685_PWM__H__
#define __PCA_9685_PWM__H__

#include "pwm_driver.h"
#include "pca9685.h"
#include <memory>

/**
 * Adapts a pca9685 LED signal to a pwm_driver object.
 */
 
class pca_9685_pwm : public pwm_driver
{
public:
    pca_9685_pwm(pca9685::pwmled led, shared_ptr<pca9685>& device)
    : device_(device), signal_(led) {}
    
    virtual ~pca_9685_pwm() override {}
    
    virtual set_frequency(int hertz) override {
        device_.set_frequency(hertz);
    }
    
    virtual set_duty(int duty) override {
        device_.set_duty(signal_, duty);
    }
private:
    shared_ptr<pca9685> device_;
    pca9685:pwmled signal_;
};

#endif 
