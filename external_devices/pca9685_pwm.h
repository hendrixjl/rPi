#ifndef __PCA_9685_PWM__H__
#define __PCA_9685_PWM__H__

#include "pwm_driver.h"
#include "pca9685.h"
#include "i2c.h"

/**
 * implements pwm_driver on a pca9685 signal line.
 */
 
class pca_9685_pwm : public pwm_driver
{
public:
    pca_9685_pwm(led, pca9685& device);
    virtual ~pca_9685_pwm() override;
    virtual set_frequency(int hertz) override;
    virtual set_duty(int duty) override;
private:
    pca9685 device_;
    pca9685::led signal_;
};

#endif 
