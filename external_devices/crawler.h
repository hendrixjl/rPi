#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "mcp23008.h"
#include "pca9685.h"
#include "mytypes.h"

class i2c;

class crawler {
public:
	enum class turn {
		STOP,
		RIGHT,
		LEFT,
		NO_CHANGE
	};

	enum class direction {
		STOP,
		FORWARD,
		BACKWARD,
		NO_CHANGE
	};

	typedef size_t power_t; // 0 .. 100

	struct maneuver_t
	{
	    direction direction;
	    power_t direction_power;
	    turn turn;
	    power_t turn_power;
	};

	crawler(i2c& bus);

	~crawler();

	void maneuver(const maneuver_t& maneuver);

private:
	mcp23008 gpio_;
	pca9685 pwm_;
	direction current_direction_;
	turn current_turn_;

	uint8_t turn_to_olat(turn turn);
	uint8_t direction_to_olat(direction dir);

	crawler(const crawler&)=delete; // no copy
	crawler& operator=(const crawler&)=delete; // no assign
};

#endif /* CRAWLER_H_ */
