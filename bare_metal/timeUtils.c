#include "timeUtils.h"


enum { USECS_TO_CYCLES=1 }; // just a guess

void udelay(uint32_t useconds)
{
	busyloop(useconds * USECS_TO_CYCLES);
}
