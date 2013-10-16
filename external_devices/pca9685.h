#ifndef __PCA9685__H__
#define __PCA9685__H__

#include "i2c.h"
#include "mytypes.h"

enum class pwmled {
      LED0 = 0,
      LED1,
      LED2,
      LED3,
      LED4,
      LED5,
      LED6,
      LED7,
      LED8,
      LED9,
      LED10,
      LED11,
      LED12,
      LED13,
      LED14,
      LED15
};

class pca9685
{
public:

    pca9685(uint8_t address, i2c& i2cbus);
    
    void reset();
    
    uint8_t getMode1();
    
    uint8_t getMode2();
    
    void set_frequency(int frequency);
    
    /**
     * Set the duty cycle of the LED
     * @param led - the target LED
     * @param duty - the duty cycle desired (0-100%)
     */
    void set_duty(pwmled led, int duty, int offset=0);
    
        
    void set_interval(pwmled led, int on_start, int off_start);

private:
    uint8_t addr_;
    i2c& i2cbus_;
    
    pca9685(const pca9685&); // no copy
    pca9685 operator=(const pca9685&); // no assign
};

#endif
