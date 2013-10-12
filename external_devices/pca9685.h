#ifndef __PCA9685__H__
#define __PCA9685__H__

#include "i2c.h"
#include "mytypes.h"

class pca9685
{
public:
    enum led_t {
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

    pca9685(uint8_t address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {
      reset();
    }
    
    void reset() {
        enum { RESET=0 };
        uint8_t command = RESET;
        i2cbus_.command(addr_, MODE1, &command, sizeof(command));
    }
    
    uint8_t getMode1() {
        return i2cbus_.query(addr_, MODE1);
    }
    
    uint8_t getMode2() {
        return i2cbus_.query(addr_, MODE2);
    }
    
    void set_frequency(uint32_t frequency) {
        enum {
            RESTART=0x80,
            EXTCLK=0x40,
            AI=0x20,
            SLEEP= 0x10,
            SUB1=0x08,
            SUB2=0x04,
            SUB3=0x02,
            ALLCALL=0x01,
            INVRT=0x10, // MODE2
            OCH=0x40
        };
        enum { CLOCK_FREQ_HZ = 25000000 };
        double prescaleval = (double(CLOCK_FREQ_HZ) / 
                              double(TWELVE_BIT_VALUE)) /
                             double(frequency) - 1.0; // why -1.0?
        uint8_t iprescale = uint8_t(prescaleval);
        uint8_t oldmode = i2cbus_.query(addr_, MODE1);
        uint8_t newmode = (oldmode & 0x7F) | SLEEP; // or sleep
        i2cbus_.command(addr_, MODE1, &newmode, sizeof(newmode));
        i2cbus_.command(addr_, PRE_SCALE, &iprescale, sizeof(iprescale));
        i2cbus_.command(addr_, MODE1, &oldmode, sizeof(oldmode));
        enum { FIVE_MILLISECONDS = 5 };
        udelay(FIVE_MILLISECONDS);
        oldmode |= 0x80;
        i2cbus_.command(addr_, MODE1, &oldmode, sizeof(oldmode));
    }
    
    /**
     * Set the duty cycle of the LED
     * @param led - the target LED
     * @param duty - the duty cycle desired (0-100%)
     */
    void set_duty(led_t led, int duty, int offset=0) {
      if (offset < 0) {
        duty = 0;
      }
      else if (offset > 100) {
        duty = 100;
      }

      if (duty < 0) {
        duty = 0;
      }
      else if ((duty + offset) > 100) {
        duty = 100 - offset;
      }
      
      set_interval_raw(led_t led, offset * TWELVE_BIT_VALUE / 100,
                                  duty * TWELVE_BIT_VALUE / 100);
    }
    
private:
    enum subaddrs_t {
      MODE1 = 0,
      MODE2 = 1,
      SUBADR1 = 2,
      SUBADR2 = 3,
      SUBADR3 = 4,
      ALLCALLADR = 5,
      LED_BASE = 6,
      PRE_SCALE = 0xFE,
      TestMode = 0xFF
    };

    enum { TWELVE_BIT_VALUE=0x08000 };

    enum {
      ADDRS_PER_LED = 4,
      ON_L = 0,
      ON_H = 1,
      OFF_L = 2,
      OFF_H = 3
    };
    
    int ledAddr(led_t led) {
      return LED_BASE + led*ADDRS_PER_LED;
    }
    
    void set_interval_raw(led_t led, int on_start, int off_start) {
      uint8_t buffer[4];
      buffer[ON_L] = on_start & 0xFF;
      buffer[ON_H] = on_start >> 8;
      buffer[OFF_L] = off_start & 0xFF;
      buffer[OFF_L] = off_start >> 8;
      i2cbus_.command(addr_, ledAddr(led), buffer, sizeof(buffer));
    }

    uint8_t addr_;
    i2c& i2cbus_;
    
    pca9685(const pca9685&); // no copy
    pca9685 operator=(const pca9685&); // no assign
};

#endif
