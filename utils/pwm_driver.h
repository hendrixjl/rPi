#ifndef PWM_DRIVER_H__
#define PWM_DRIVER_H__

/**
 * This is an abstract class for a PWM controller.
 * A pwm_driver object controls a *single* PWM signal.
 */
 
class pwm_driver
{
public:
    /**
     * virtual destructor so interface will work
     */
    virtual ~pwm_driver() {}
    
    /**
     * Set the frequency in hertz for the PWM device.
     * @param hertz - the desired frequency.
     */
    virtual void set_frequency(int hertz)=0;

    /**
     * Set the duty cycle for a PWM device.
     * @param duty - The duty cycle in percentage.
     */
    virtual void set_duty(int duty)=0;
};


#endif
