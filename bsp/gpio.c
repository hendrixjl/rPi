/*
 * gpio.c
 *
 *  Created on: Jan 15, 2013
 *      Author: jonathanhendrix
 */

#include "gpio.h"
#include "bar.h"
#include <stdint.h>

#include <stdio.h>

typedef enum {
	GPFSEL0, //   = GPIO_BAR,
	GPFSEL1, //   = GPIO_BAR + 0x0004,
	GPFSEL2, //   = GPIO_BAR + 0x0008,
	GPFSEL3, //   = GPIO_BAR + 0x000C,
	GPFSEL4, //   = GPIO_BAR + 0x0010,
	GPFSEL5, //   = GPIO_BAR + 0x0014,
	RESERV1, //   = GPIO_BAR + 0x0018,
	GPSET0, //   = GPIO_BAR + 0x001C,
	GPSET1, //    = GPIO_BAR + 0x0020,
	RESERV2, //   = GPIO_BAR + 0x0024,
	GPCLR0, //    = GPIO_BAR + 0x0028,
	GPCLR1, //    = GPIO_BAR + 0x002C,
	RESERV3, //   = GPIO_BAR + 0x0030,
	GPLEV0, //    = GPIO_BAR + 0x0034,
	GPLEV1, //    = GPIO_BAR + 0x0038,
	RESERV4, //   = GPIO_BAR + 0x003C,
	GPEDS0, //    = GPIO_BAR + 0x0040,
	GPEDS1, //    = GPIO_BAR + 0x0044,
	RESERV5, //   = GPIO_BAR + 0x0048,
	GPREN0, //    = GPIO_BAR + 0x004C,
	GPREN1, //    = GPIO_BAR + 0x0050,
	RESERV6, //   = GPIO_BAR + 0x0054,
	GPFEN0, //    = GPIO_BAR + 0x0058,
	GPFEN1, //   = GPIO_BAR + 0x005C,
	RESERV7, //   = GPIO_BAR + 0x0060,
	GPHEN0, //    = GPIO_BAR + 0x0064,
	GPHEN1, //    = GPIO_BAR + 0x0068,
	RESERV8, //   = GPIO_BAR + 0x006C,
	GPLEN0, //    = GPIO_BAR + 0x0070,
	GPLEN1, //    = GPIO_BAR + 0x0074,
	RESERV9, //   = GPIO_BAR + 0x0078,
	GPAREN0, //   = GPIO_BAR + 0x007C,
	GPAREN1, //   = GPIO_BAR + 0x0080,
	RESERVA, //   = GPIO_BAR + 0x0084,
	GPAFEN0, //   = GPIO_BAR + 0x0088,
	GPAFEN1, //   = GPIO_BAR + 0x008C,
	RESERVB, //   = GPIO_BAR + 0x0090,
	GPPUD, //     = GPIO_BAR + 0x0094,
	GPPUDCLK0, // = GPIO_BAR + 0x0098,
	GPPUDCLK1, // = GPIO_BAR + 0x009C,
	RESERVC, //   = GPIO_BAR + 0x00A0,
	RESERVD //   = GPIO_BAR + 0x00B0
} gpio_registers_t;

enum {
	MAX_PINS_PER_WORD=32
};

void gpio_fsel(gpio_pin_t pin, gpio_function_t fun) 
{
	enum {
		PINS_PER_WORD = 10,
		BITS_PER_PIN = 3
	};
	uint32_t word = GPFSEL0 + pin/PINS_PER_WORD;
//	unsigned int *word = (unsigned int*)(GPFSEL0) + pin/PINS_PER_WORD;
	unsigned int ra = GPIO_BAR[word]; // *word;
    ra &= ~(ALL_MASK<<((pin%PINS_PER_WORD)*BITS_PER_PIN));
    ra |= OUTPUT<<((pin%PINS_PER_WORD)*BITS_PER_PIN);
    GPIO_BAR[word] = ra; // *(unsigned int*)word = ra;
	printf("%s:%d - GPIO_BAR=%08X. GPIO_BAR[GPFSEL0]=%08X.  state=%08X\n", __FILE__, __LINE__, (unsigned)GPIO_BAR, (unsigned)&GPIO_BAR[word], GPIO_BAR[word]);
}

void gpio_set0(gpio_pin_t pin) 
{
	if (pin > (uint32_t)MAX_PINS_PER_WORD)
	{
		GPIO_BAR[GPSET0] = 1<<(pin-MAX_PINS_PER_WORD); // *(unsigned int*)GPSET0 = 1<<pin;
	}
	else
	{
		GPIO_BAR[GPSET0] = 1<<pin; // *(unsigned int*)GPSET0 = 1<<pin;
	}
}

void gpio_clear0(gpio_pin_t pin) 
{
	if (pin > (uint32_t)MAX_PINS_PER_WORD)
	{
		GPIO_BAR[GPCLR0] = 1<<(pin-MAX_PINS_PER_WORD);
	}
	else
	{
		GPIO_BAR[GPCLR0] = 1<<pin;
	}
}


void gpio_set1(gpio_pin_t pin)
{
	if (pin > (uint32_t)MAX_PINS_PER_WORD)
	{
		GPIO_BAR[GPSET1] = 1<<(pin-MAX_PINS_PER_WORD);
	}
	else
	{
		GPIO_BAR[GPSET1] = 1<<pin;
	}
}

void gpio_clear1(gpio_pin_t pin)
{
	if (pin > (uint32_t)MAX_PINS_PER_WORD)
	{
		GPIO_BAR[GPCLR1] = 1<<(pin-MAX_PINS_PER_WORD);
	}
	else
	{
		GPIO_BAR[GPCLR1] = 1<<pin;
	}
}

pin_level_t gpio_get_level(gpio_pin_t pin)
{
	if (pin > (uint32_t)MAX_PINS_PER_WORD)
	{
		return ((GPIO_BAR[GPLEV1] & (1<<(pin-MAX_PINS_PER_WORD))) != 0);
	}
	else
	{
		return ((GPIO_BAR[GPLEV0] & (1<<pin)) != 0);
	}
}

bool gpio_event_detected(gpio_pin_t pin)
{
	int word = GPEDS0;
	int pinInWord = pin;
	if (pin > (unsigned)MAX_PINS_PER_WORD)
	{
		word = GPEDS1;
		pinInWord = pin - MAX_PINS_PER_WORD;
	}
	printf("%s:%d - GPIO_BAR=%08X. GPIO_BAR[GPEDS0]=%08X.  state=%08X\n", __FILE__, __LINE__, (unsigned)GPIO_BAR, (unsigned)&GPIO_BAR[word], GPIO_BAR[word]);
	return ((GPIO_BAR[word] & (1<<pinInWord)) != 0);
}

void gpio_clear_event_detected(gpio_pin_t pin)
{
	int word = GPEDS0;
	int pinInWord = pin;
	if (pin > (unsigned)MAX_PINS_PER_WORD)
	{
		word = GPEDS1;
		pinInWord = pin - MAX_PINS_PER_WORD;
	}
	printf("%s:%d - GPIO_BAR=%08X. GPIO_BAR[GPEDS0]=%08X.  pin=%d\n", __FILE__, __LINE__, (unsigned)GPIO_BAR, (unsigned)&GPIO_BAR[word], pinInWord);
	GPIO_BAR[word] |= (1<<pinInWord);
}

void gpio_set_event_detect(gpio_pin_t pin, event_type_t event_type)
{
	int word = GPREN0;
	int pinInWord = pin;
	if (pin > (unsigned)MAX_PINS_PER_WORD)
	{
		word = GPREN1;
		pinInWord = pin - MAX_PINS_PER_WORD;
	}
	switch (event_type)
	{
		case NO_DETECT:
			GPIO_BAR[word] &= ~(1<<pinInWord);
			GPIO_BAR[word+(GPFEN0-GPREN0)] &= ~(1<<pinInWord);
			GPIO_BAR[word+(GPHEN0-GPREN0)] &= ~(1<<pinInWord);
			GPIO_BAR[word+(GPLEN0-GPREN0)] &= ~(1<<pinInWord);
			GPIO_BAR[word+(GPAREN0-GPREN0)] &= ~(1<<pinInWord);
			GPIO_BAR[word+(GPAFEN0-GPREN0)] &= ~(1<<pinInWord);
			break;
		case RISING_EDGE_DETECT:
			GPIO_BAR[word] |= (1<<pinInWord);
			break;
		case FALLING_EDGE_DETECT:
			GPIO_BAR[word+(GPFEN0-GPREN0)] |= (1<<pinInWord);
			printf("%s:%d - GPIO_BAR=%08X. GPIO_BAR[GPFEN0]=%08X.  pin=%d state=%d\n", __FILE__, __LINE__, (unsigned)GPIO_BAR, (unsigned)&GPIO_BAR[word+(GPFEN0-GPREN0)], pinInWord, GPIO_BAR[GPFEN0]);
			break;
		case TRANSITION_DETECT:
			GPIO_BAR[word] |= (1<<pinInWord);
			GPIO_BAR[word+(GPFEN0-GPREN0)] |= (1<<pinInWord);
			break;
		case HIGH_DETECT:
			GPIO_BAR[word+(GPHEN0-GPREN0)] |= (1<<pinInWord);
			break;
		case LOW_DETECT:
			GPIO_BAR[word+(GPLEN0-GPREN0)] |= (1<<pinInWord);
			break;
		case ASYNC_RISING_EDGE_DETECT:
			GPIO_BAR[word+(GPAREN0-GPREN0)] |= (1<<pinInWord);
			break;
		case ASYNC_FALLING_EDGE_DETECT:
			GPIO_BAR[word+(GPAFEN0-GPREN0)] |= (1<<pinInWord);
			break;
	}
}


static void busy(unsigned int n)
{
	for(volatile unsigned i=0; i<n; i++);
}

void gpio_set_pud(gpio_pin_t pin, gppud_t pud)
{
	int word = GPPUDCLK0;
	int pinInWord = pin;
	if (pin > (unsigned)MAX_PINS_PER_WORD)
	{
		word = GPPUDCLK1;
		pinInWord = pin - MAX_PINS_PER_WORD;
	}
	
	GPIO_BAR[GPPUD] = pud;
	enum { WAIT_150_CYCLES = 150 };
	busy(WAIT_150_CYCLES);
	GPIO_BAR[word] |= (1<<pinInWord);
	busy(WAIT_150_CYCLES);
	GPIO_BAR[GPPUD] = 0;
	GPIO_BAR[word] = 0;
}
