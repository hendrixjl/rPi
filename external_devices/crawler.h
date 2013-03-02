
#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "mcp23008.h"
#include "mytypes.h"

class i2c;

class crawler {
public:
	enum turn_t {
		STOP_TURN,
		RIGHT_TURN,
		LEFT_TURN,
		NO_CHANGE_TURN
	};

	enum direction_t {
		STOP_DIRECTION,
		FORWARD_DIRECTION,
		BACKWARD_DIRECTION,
		NO_CHANGE_DIRECTION
	};

	typedef size_t power_t; // 0 .. 100

	struct maneuver_t
	{
	    direction_t direction;
	    power_t direction_power;
	    turn_t turn;
	    power_t turn_power;
	};

	crawler(i2c& bus);

	~crawler();

	void maneuver(const maneuver_t& maneuver);

private:
	mcp23008 gpio_;
	direction_t current_direction_;
	turn_t current_turn_;

	uint8_t turn_to_olat(turn_t turn);
	uint8_t direction_to_olat(direction_t dir);

	crawler(const crawler&)=delete; // no copy
	crawler& operator=(const crawler&)=delete; // no assign
};

#endif /* CRAWLER_H_ */
