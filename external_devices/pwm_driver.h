#ifndef PWM_DRIVER_H__
#define PWM_DRIVER_H__

/**
 * This is an abstract class for a PWM controller.
 */
 
class pwm_driver
{
public:
    /**
     * Set the duty cycle for a PWM device.
     * @param duty - The duty cycle in percentage.
     */
    virtual void set_duty(int duty)=0;
private:
};


#endif
