#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "pwm_driver.h"
#include "gpio_output_driver.h"
#include "mytypes.h"

#include <memory>


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

	crawler();

	~crawler();

	void maneuver(const maneuver_t& maneuver);

private:
	std::unique_ptr<gpio_output_driver> gpio_;
	std::unique_ptr<pwm_driver> pwm_;
	direction current_direction_;
	turn current_turn_;

	uint8_t turn_to_olat(turn turn);
	uint8_t direction_to_olat(direction dir);

	crawler(const crawler&)=delete; // no copy
	crawler& operator=(const crawler&)=delete; // no assign
};

#endif /* CRAWLER_H_ */
