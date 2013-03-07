#include "bar.h"
#include "arm_timer.h"

extern void maneuver_program();

extern "C" int kmain();

enum {
	CYCLES_IN_TIME_TICK = 1000U,
};

unsigned time_ticks;

void c_irq_handler()
{
	++time_ticks;
}


int kmain()
{
	time_ticks = 0;
    init_bars();

    enum {
    	ARM_TIMER_DIV = 0x000000F9U
    };
    arm_timer_setup(CYCLES_IN_TIME_TICK-1,
    		CYCLES_IN_TIME_TICK-1,
    		ARM_TIMER_DIV,
    		PRESCALE_IS_CLOCK_DIV_1,
    		TWENTY_THREE_BITS);
    arm_timer_clear_irq();
    arm_timer_enable();
    arm_timer_irq_enable();

    maneuver_program();
    
    return 1;
}

