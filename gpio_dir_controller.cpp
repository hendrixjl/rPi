#include "gpio_dir_controller.h"

#include "mcp23008.h"

mcp23008 mcp23008_0x20(0x20, i2c::setup1());

class mcp23008_gpio_output_driver: public gpio_output_driver
{
public:
    mcp23008_gpio_output_driver(int pin) : pin_(pin) {
		mcp23008_0x20.set_iodir(pin_, ACTIVE_HIGH_OUTPUT_IOCON);
	}
    /**
     * Turn the pin on (active state)
     */
    virtual void on() override { mcp23008_0x20.set_gpio(pin_, true); }
    
    /**
     * Turn the pin off (deactive)
     */
    virtual void off() override { mcp23008_0x20.set_gpio(pin_, false); }
    
private:
    int pin_;
};


gpio_dir_controller::gpio_dir_controller()
:   gobit_(make_unique<mcp23008_gpio_output_driver>(mcp23008::PIN0)),
    backbit_(make_unique<mcp23008_gpio_output_driver>(mcp23008::PIN1))
{
}
