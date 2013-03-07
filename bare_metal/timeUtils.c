#include "timeUtils.h"
#include "arm_timer.h"

enum {
	TIME_TICKS_IN_USEC=1
};

unsigned arm_timer_to_usec() {
	return arm_timer_val()/TIME_TICKS_IN_USEC;
}

void udelay(uint32_t useconds)
{
	enum { USECS_IN_CLCK_CYCLES };
	busyloop(useconds * USECS_IN_CLCK_CYCLES);
}

extern unsigned time_ticks;

unsigned long long getTime()
{
	enum {
		MICROSECONDS_IN_SECOND = 1000000U
	};

	return time_ticks * TIME_TICKS_IN_USEC;
}
