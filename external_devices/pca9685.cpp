#include "pca9685.h"
#include "timeUtils.h"

#include <iostream>
#include <cassert>

using namespace std;


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

enum ControlBits {
      RESTART=0x80, // MODE1 bits
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

enum { TWELVE_BIT_VALUE = 0x01000 };

pca9685::pca9685(uint8_t address, i2c& i2cbus) : addr_(address), i2cbus_(i2cbus) {
    reset();
}
    
void pca9685::reset() {
    enum { RESET=0 };
    uint8_t command = RESET;
    i2cbus_.command(addr_, MODE1, &command, sizeof(command));
}
    
uint8_t pca9685::getMode1() {
     return i2cbus_.query(addr_, MODE1);
}
    
uint8_t pca9685::getMode2() {
    return i2cbus_.query(addr_, MODE2);
}
    
void pca9685::set_frequency(uint32_t frequency) {
    // prescale formula from pca9685 documentation
    enum { CLOCK_FREQ_HZ = 25000000 };
    double prescaleval = double(CLOCK_FREQ_HZ) / 
                          double(TWELVE_BIT_VALUE * frequency) - 1;
    assert( prescaleval <= 255.0 );
    uint8_t iprescale = static_cast<uint8_t>(prescaleval);
    cout << "iprescale=" << (uint32_t)iprescale << endl;
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
    
void pca9685::set_duty(pwmled led, int duty, int offset) {
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
      
    cout << "offset=" << offset << " duty=" << duty << endl;
    set_interval(led, offset * TWELVE_BIT_VALUE / 100,
                             duty * TWELVE_BIT_VALUE / 100);
}
    
enum {
      ADDRS_PER_LED = 4,
      ON_LOW_BYTE_OFFSET = 0,
      ON_HIGH_BYTE_OFFSET = 1,
      OFF_LOW_BYTE_OFFSET = 2,
      OFF_HIGH_BYTE_OFFSET = 3
};
    
static int ledAddr(pwmled led) {
      return LED_BASE + static_cast<uint32_t>(led)*ADDRS_PER_LED;
}
        
void pca9685::set_interval(pwmled led, int on_start, int off_start) {
      cout << " on_start=" << on_start << " off_start=" << off_start << endl;
      uint8_t buffer[] = 
      {
          static_cast<uint8_t>(on_start & 0xFF),
          static_cast<uint8_t>(on_start >> 8),
          static_cast<uint8_t>(off_start & 0xFF),
          static_cast<uint8_t>(off_start >> 8)
      };
//      i2cbus_.command(addr_, ledAddr(led), buffer, sizeof(buffer));
      i2cbus_.command(addr_, ledAddr(led) + ON_LOW_BYTE_OFFSET, &buffer[ON_LOW_BYTE_OFFSET], 1);
      i2cbus_.command(addr_, ledAddr(led) + ON_HIGH_BYTE_OFFSET, &buffer[ON_HIGH_BYTE_OFFSET], 1);
      i2cbus_.command(addr_, ledAddr(led) + OFF_LOW_BYTE_OFFSET, &buffer[OFF_LOW_BYTE_OFFSET], 1);
      i2cbus_.command(addr_, ledAddr(led) + OFF_HIGH_BYTE_OFFSET, &buffer[OFF_HIGH_BYTE_OFFSET], 1);
}

