/*
 * gpio.c
 *
 *  Created on: Jan 15, 2013
 *      Author: jonathanhendrix
 */

#include "gpio.h"
#include "bar.h"

typedef enum {
	GPFSEL0   = GPIO_BAR,
	GPFSEL1   = GPIO_BAR + 0x0004,
	GPFSEL2   = GPIO_BAR + 0x0008,
	GPFSEL3   = GPIO_BAR + 0x000C,
	GPFSEL4   = GPIO_BAR + 0x0010,
	GPFSEL5   = GPIO_BAR + 0x0014,
	RESERV1   = GPIO_BAR + 0x0018,
	GPSET0    = GPIO_BAR + 0x001C,
	GPSET1    = GPIO_BAR + 0x0020,
	RESERV2   = GPIO_BAR + 0x0024,
	GPCLR0    = GPIO_BAR + 0x0028,
	GPCLR1    = GPIO_BAR + 0x002C,
	RESERV3   = GPIO_BAR + 0x0030,
	GPLEV0    = GPIO_BAR + 0x0034,
	GPLEV1    = GPIO_BAR + 0x0038,
	RESERV4   = GPIO_BAR + 0x003C,
	GPEDS0    = GPIO_BAR + 0x0040,
	GPEDS1    = GPIO_BAR + 0x0044,
	RESERV5   = GPIO_BAR + 0x0048,
	GPREN0    = GPIO_BAR + 0x004C,
	GPREN1    = GPIO_BAR + 0x0050,
	RESERV6   = GPIO_BAR + 0x0054,
	GPFEN0    = GPIO_BAR + 0x0058,
	GPFEN1    = GPIO_BAR + 0x005C,
	RESERV7   = GPIO_BAR + 0x0060,
	GPHEN0    = GPIO_BAR + 0x0064,
	GPHEN1    = GPIO_BAR + 0x0068,
	RESERV8   = GPIO_BAR + 0x006C,
	GPLEN0    = GPIO_BAR + 0x0070,
	GPLEN1    = GPIO_BAR + 0x0074,
	RESERV9   = GPIO_BAR + 0x0078,
	GPAREN0   = GPIO_BAR + 0x007C,
	GPAREN1   = GPIO_BAR + 0x0080,
	RESERVA   = GPIO_BAR + 0x0084,
	GPAFEN0   = GPIO_BAR + 0x0088,
	GPAFEN1   = GPIO_BAR + 0x008C,
	RESERVB   = GPIO_BAR + 0x0090,
	GPPUD     = GPIO_BAR + 0x0094,
	GPPUDCLK0 = GPIO_BAR + 0x0098,
	GPPUDCLK1 = GPIO_BAR + 0x009C,
	RESERVC   = GPIO_BAR + 0x00A0,
	RESERVD   = GPIO_BAR + 0x00B0
} gpio_registers_t;

void gpio_fsel(gpio_pin_t pin, gpio_function_t fun) {
	enum {
		PINS_PER_WORD = 10,
		BITS_PER_PIN = 3
	};
	unsigned int *word = (unsigned int*)(GPFSEL0) + pin/PINS_PER_WORD;
	unsigned int ra = *word;
    ra &= ~(ALL_MASK<<((pin%PINS_PER_WORD)*BITS_PER_PIN));
    ra |= OUTPUT<<((pin%PINS_PER_WORD)*BITS_PER_PIN);
    *(unsigned int*)word = ra;
}

void gpio_set0(gpio_pin_t pin) {
	*(unsigned int*)GPSET0 = 1<<pin;
}

void gpio_clear0(gpio_pin_t pin) {
	*(unsigned int*)GPCLR0 = 1<<pin;
}
