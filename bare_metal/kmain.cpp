#include "bar.h"
#include "arm_timer.h"

extern void maneuver_program();

extern "C" int kmain();

enum {
	MICROSECONDS_IN_SECOND = 1000000U
};

unsigned seconds;

void c_irq_handler()
{
	++seconds;
}

extern "C" unsigned long long getTime();

unsigned long long getTime()
{
	return seconds*MICROSECONDS_IN_SECOND + arm_timer_val();
}

int kmain()
{
	seconds = 0;
    init_bars();

    enum {
    	ARM_TIMER_DIV = 0x000000F9U
    };
    arm_timer_setup(MICROSECONDS_IN_SECOND-1,
    		MICROSECONDS_IN_SECOND-1,
    		ARM_TIMER_DIV,
    		PRESCALE_IS_CLOCK_DIV_1,
    		TWENTY_THREE_BITS);
    arm_timer_clear_irq();
    arm_timer_enable();
    arm_timer_irq_enable();

    maneuver_program();
    
    return 1;
}

