#include "bar.h"
#include "stdout.h"


extern void maneuver_program();

int main()
{
	init_bars();

	maneuver_program();
}
