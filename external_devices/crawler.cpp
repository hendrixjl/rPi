#include "crawler.h"
#include "format.h"
#include "i2c.h"

#include "make_unique"
#include "pca9685.h"

#include <iostream>
using namespace std;

namespace
{

enum {
	MCP23008=0x20,
	PCA9685=0x40
};

enum {
    DIRECTION_ENABLE=mcp23008::PIN0,
    FORWARD=mcp23008::PIN1,
    BACKWARD=mcp23008::PIN2,
    TURN_ENABLE=mcp23008::PIN3,
    RIGHT=mcp23008::PIN4,
    LEFT=mcp23008::PIN5,
    ALL_PINS = mcp23008::PIN0 | mcp23008::PIN1 | mcp23008::PIN2 | mcp23008::PIN3 | mcp23008::PIN4 | mcp23008::PIN5,
    OFF = 0
};
}


crawler::crawler(i2c& bus)
: gpio_(MCP23008, bus),
  current_direction_(STOP_DIRECTION),
  current_turn_(STOP_TURN)
{
	auto pwmdevice = make_shared<pca9685>(PCA9685, bus);
	enum { SIXTY_HZ = 60 };
	pwmdevice->set_frequency(SIXTY_HZ);
	forward_back_pwm_ = make_unique<pwm_driver>(pca9685::pwmled0, pwmdevice);
	left_right_pwm_ = make_unique<pwm_driver>(pca9685::pwmled1, pwmdevice);
	
	gpio_.set_iodir(ALL_PINS, mcp23008::OUTPUT);
	gpio_.set_input_polarity(ALL_PINS, mcp23008::NORMAL_LOGIC);
    gpio_.set_olat(OFF);
}

crawler::~crawler()
{
	gpio_.set_olat(ALL_PINS, mcp23008::OFF);
	gpio_.set_iodir(ALL_PINS, mcp23008::INPUT);
}

void crawler::maneuver(const maneuver_t& maneuver)
{
	uint8_t v = direction_to_olat(maneuver.direction) | turn_to_olat(maneuver.turn);
	cout << static_cast<uint32_t>(v) << endl;
    gpio_.set_olat(v);
    left_right_pwm_->set_duty(maneuver.turn_power);
    forward_back_pwm_->set_duty(maneuver.drive_power);
}


uint8_t crawler::turn_to_olat(crawler::turn turn)
{
	uint8_t value=0;
    if (turn == crawler::NO_CHANGE)
    {
        turn = current_turn_;
    }
    else
    {
    	current_turn_ = turn;
    }

    if (turn == crawler::STOP)
    {
        value = 0;
    }
    else if (turn == crawler::RIGHT)
    {
        value = TURN_ENABLE | RIGHT;
    }
    else if (turn == crawler::LEFT)
    {
        value = TURN_ENABLE | LEFT;
    }
    return value;
}

uint8_t crawler::direction_to_olat(crawler::direction dir)
{
	uint8_t value=0;
    if (dir == crawler::NO_CHANGE)
    {
        dir = current_direction_;
    }
    else
    {
    	current_direction_ = dir;
    }

    if (dir == crawler::STOP)
    {
        value = 0;
    }
    else if (dir == FORWARD)
    {
        value = DIRECTION_ENABLE | FORWARD;
    }
    else if (dir == BACKWARD)
    {
        value = DIRECTION_ENABLE | BACKWARD;
    }
    return value;
}
