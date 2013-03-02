
#include "crawler.h"
#include "stdout.h"
#include "format.h"
#include "i2c.h"
#include "pwm.h"

namespace
{

enum {
	MCP23008=0x20
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
	static char buffer[RECOMMENDED_BUFFER_SIZE];
	unsigned_to_bstring(buffer, RECOMMENDED_BUFFER_SIZE, (unsigned)v);
	writeln(buffer);
    gpio_.set_olat(v);
//    setTurnServo(maneuver.turn_power);
//    setDirectionServo(maneuver.direction_power);
}


uint8_t crawler::turn_to_olat(turn_t turn)
{
	uint8_t value=0;
    if (turn == crawler::NO_CHANGE_TURN)
    {
        turn = current_turn_;
    }
    else
    {
    	current_turn_ = turn;
    }

    if (turn == crawler::STOP_TURN)
    {
        value = 0;
    }
    else if (turn == crawler::RIGHT_TURN)
    {
        value = TURN_ENABLE | RIGHT;
    }
    else if (turn == crawler::LEFT_TURN)
    {
        value = TURN_ENABLE | LEFT;
    }
    return value;
}

uint8_t crawler::direction_to_olat(direction_t dir)
{
	uint8_t value=0;
    if (dir == crawler::NO_CHANGE_DIRECTION)
    {
        dir = current_direction_;
    }
    else
    {
    	current_direction_ = dir;
    }

    if (dir == crawler::STOP_DIRECTION)
    {
        value = 0;
    }
    else if (dir == FORWARD_DIRECTION)
    {
        value = DIRECTION_ENABLE | FORWARD;
    }
    else if (dir == BACKWARD_DIRECTION)
    {
        value = DIRECTION_ENABLE | BACKWARD;
    }
    return value;
}
