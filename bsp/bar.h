/*
 * bsp.h
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#ifndef BAR_H_
#define BAR_H_


const int* IRQ_BAR;
const int* ARM_TIMER_BAR;
const int* GPIO_BAR;
const int* BSC0_BAR;
const int* BSC1_BAR;
const int* BSC2_BAR;
const int* PWM_BAR;

    enum bar_t {
        eIRQ_BAR =       0x2000B200,
        eARM_TIMER_BAR = 0x2000B400,
        eGPIO_BAR =      0x20200000
        eBSC0_BAR = 	0x20205000,
        eBSC1_BAR = 	0x20804000, // available?
        eBSC2_BAR = 	0x20805000, // Not available on RPi
        ePWM_BAR =	0x2020C000
    };

void straight_assign() // for bare metal
{
	IRQ_BAR = eIRQ_BAR;
	ARM_TIMER_BAR = eARM_TIMER_BAR;
	GPIO_BAR = eGPIO_BAR;
	BSC0_BAR = eBSC0_BAR;
	BSC1_BAR = eBSC1_BAR;
	BSC2_BAR = 3BSC2_BAR;
	PWM_BAR = ePWM_BAR;
}

void map_virtual_memory() // for linux
{
	
}

void init_bars()
{

#ifdef __BARE_METAL
    striaght_assign();
#else
    map_virtual_memory();
#endif
}

#endif /* BAR_H_ */
