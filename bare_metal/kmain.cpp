#include "bar.h"


extern void maneuver_program();

extern "C"
{

int kmain()
{
    init_bars();

    maneuver_program();
}

}
