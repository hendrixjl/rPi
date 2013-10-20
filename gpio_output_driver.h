#ifndef __GPIO_OUTPUT_DRIVER_H__
#define __GPIO_OUTPUT_DRIVER_H__

/**
 * Abstract base class for GPIO output
 */
 
class gpio_output_driver
{
public:
    /**
     * Virtual destructor for polymorphic delete
     */
    virtual ~gpio_output_driver() {}
    
    /**
     * Turn the pin on (active state)
     */
    virtual void on()=0;
    
    /**
     * Turn the pin off (deactive)
     */
    virtual void off()=0;
    
private:
};

#endif
