#include "bar.h"
#include "gpio.h"
#include "stdout.h"


extern void pause_till_signal();

extern void maneuver_program();

int main()
{
	init_bars();
	initHardware();

	gpio_set_fsel(PIN_18, ALT1);

	write("Waiting for signal");
	writeln();
	pause_till_signal();
	write("Signal!");
	writeln();
	
	maneuver_program();

}
