#include "l3gd20.h"
#include "lsm303dlh.h"
#include "mcp23008.h"
#include "bar.h"
#include "gpio.h"
#include "pwm.h"

using namespace std;

extern void pause_till_signal();

extern void maneuver_program();

void dump(mcp23008& gpio)
{
	cout << "mcp23008 regs: ";
	const auto& v = gpio.get_registers();
	cout << "(" << v.size() << ")" << endl;
	for (auto it: v)
	{
		cout << " " << hex << unsigned(it);
	}
	cout << dec << endl;
}

int main()
{
	init_bars();
	initHardware();

	gpio_set_fsel(PIN_18, ALT1);

	cout << "Waiting for signal" << endl;
	pause_till_signal();
	cout << "Signal!" << endl;

	maneuver_program();

}
