#include "bar.h"

enum bar_t {
        eIRQ_BAR =       0x2000B200,
        eARM_TIMER_BAR = 0x2000B400,
        eGPIO_BAR =      0x20200000,
        eBSC0_BAR =   0x20205000,
        eBSC1_BAR = 	0x20804000, // available?
        eBSC2_BAR = 	0x20805000, // Not available on RPi
        ePWM_BAR =	0x2020C000
};

void straight_assign() // for bare metal
{
    IRQ_BAR = (volatile unsigned*) eIRQ_BAR;
    ARM_TIMER_BAR = (volatile unsigned*) eARM_TIMER_BAR;
    GPIO_BAR = (volatile unsigned*) eGPIO_BAR;
    BSC0_BAR = (volatile unsigned*) eBSC0_BAR;
    BSC1_BAR = (volatile unsigned*) eBSC1_BAR;
    BSC2_BAR = (volatile unsigned*) eBSC2_BAR;
    PWM_BAR = (volatile unsigned*) ePWM_BAR;
}

#ifndef __BARE_METAL__

#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

// map 4k register memory for direct access from user space and return a user space pointer to it
volatile unsigned *mapRegisterMemory(int base)
{
    static int mem_fd = 0;
    char *mem, *map;

    /* open /dev/mem */
    if (!mem_fd) {
        if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
            printf("can't open /dev/mem \n");
            exit (-1);
        }
    }
	
    /* mmap register */
    // Allocate MAP block
    static const unsigned PAGE_SIZE = 4*1024;
	static const unsigned BLOCK_SIZE = 4*1024;

    if ((mem = malloc(BLOCK_SIZE + (PAGE_SIZE-1))) == NULL) {
        printf("allocation error \n");
        exit (-1);
    }
	
    // Make sure pointer is on 4K boundary
    if ((unsigned long)mem % PAGE_SIZE)
    {
		    mem += PAGE_SIZE - ((unsigned long)mem % PAGE_SIZE);
    }
	
    // Now map it
    map = (char *)mmap(
                (caddr_t)mem,
                BLOCK_SIZE,
                PROT_READ|PROT_WRITE,
                MAP_SHARED|MAP_FIXED,
                mem_fd,
                base);
	
    if ((long)map < 0) {
        printf("mmap error %d\n", (int)map);
        exit (-1);
    }

    // Always use volatile pointer!
    return (volatile unsigned *)map;
}


void map_virtual_memory() // for linux
{
    IRQ_BAR = mapRegisterMemory(eIRQ_BAR);
    ARM_TIMER_BAR = mapRegisterMemory(eARM_TIMER_BAR);
    GPIO_BAR = mapRegisterMemory(eGPIO_BAR);
    BSC0_BAR = mapRegisterMemory(eBSC0_BAR);
    BSC1_BAR = mapRegisterMemory(eBSC1_BAR);
    BSC2_BAR = mapRegisterMemory(eBSC2_BAR);
    PWM_BAR = mapRegisterMemory(ePWM_BAR);
}
#endif


void init_bars()
{

#ifdef __BARE_METAL
    striaght_assign();
#else
    map_virtual_memory();
#endif
}
