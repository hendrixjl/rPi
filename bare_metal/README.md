This is for the low level files that enable running bare metal.

memmap - This is the linker memory map (used in the top directory) that guarantees
         that bootstrap.o is the first to load at location 0x08000.

bootstrap.S - Defines and sets up the interrupt vectors and branches to kmain.

cpp_enables.S - Trivially defines __cxa_guard_acquire and __cxa_guard_release 
                so that C++ function-level static initialization can occur.
                This will need to have true guards if multithreaded access is 
                possible.

kmain.cpp - Defines the initial "program" entry to bare metal. This initializes
            the BARs for the Broadcom peripherals and jumps to maneuver_program().

timeUtils.c - Defines the udelay function under bare metal.

stdout.cpp - Defines write functions to send output to the mini uart peripheral.
