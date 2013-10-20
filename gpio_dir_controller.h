#ifndef __GPIO_DIR_CONTROLLER__
#define __GPIO_DIR_CONTROLLER__

#include "gpio_output_driver.h"
#include "direction_cntrl.h"
#include <memory>

/*
 * This class implements direction control using two GPIO output drivers
 */
 
class gpio_dir_controller: public direction_cntrl
{
public:
    gpio_dir_controller();

    virtual void go() override { backbit_->off(); gobit_->on(); }
    virtual void stop() override { backbit_->off(); gobit_->off(); }
    virtual void back() override { gobit_->off(); backbit->on(); }

private:
    std::unique_ptr<gpio_output_driver> gobit_;
    std::unique_ptr<gpio_output_driver> backbit_;
};


#endif
