#include "bar.h"


extern void maneuver_program();

extern "C" { int kmain() }

int kmain()
{
    init_bars();

    maneuver_program();
    
    return 1;
}

