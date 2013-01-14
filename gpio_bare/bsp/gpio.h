/*
 * gpio.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jonathanhendrix
 */

#ifndef GPIO_H_
#define GPIO_H_

class gpio_t
{
private:
	enum {
		GPIO_BAR  = 0x20200000,
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
	};
public:

	enum pin_t {
		PIN_00=0,
		PIN_01=1,
		PIN_02=2,
		PIN_03=3,
		PIN_04=4,
		PIN_05=5,
		PIN_06=6,
		PIN_07=7,
		PIN_08=8,
		PIN_09=9,
		PIN_10=10,
		PIN_11=11,
		PIN_12=12,
		PIN_13=13,
		PIN_14=14,
		PIN_15=15,
		PIN_16=16,
		PIN_17=17,
		PIN_18=18,
		PIN_19=19,
		PIN_20=20,
		PIN_21=21,
		PIN_22=22,
		PIN_23=23,
		PIN_24=24,
		PIN_25=25,
		PIN_26=26,
		PIN_27=27,
		PIN_28=28,
		PIN_29=29,
		PIN_30=30,
		PIN_31=31,
		PIN_32=32,
		PIN_33=33,
		PIN_34=34,
		PIN_35=35,
		PIN_36=36,
		PIN_37=37,
		PIN_38=38,
		PIN_39=39,
		PIN_40=40,
		PIN_41=41,
		PIN_42=42,
		PIN_43=43,
		PIN_44=44,
		PIN_45=45,
		PIN_46=46,
		PIN_47=47,
		PIN_48=48,
		PIN_49=49,
		PIN_50=50,
		PIN_51=51,
		PIN_52=52,
		PIN_53=53
	};

	enum function_t {
		INTPUT=0,
		OUTPUT=1,
		ALT0=4,
		ALT1=5,
		ALT2=6,
		ALT3=4,
		ALT4=3,
		ALT5=2,
		ALL_MASK=7
	};

	static void fsel(pin_t pin, function_t fun) {
		enum {
			PINS_PER_WORD = 10,
			BITS_PER_PIN = 3
		};
		unsigned int *word = reinterpret_cast<unsigned int*>(gpio_t::GPFSEL0) + pin/PINS_PER_WORD;
		unsigned int ra = *word;
	    ra &= ~(ALL_MASK<<((pin%PINS_PER_WORD)*BITS_PER_PIN));
	    ra |= OUTPUT<<((pin%PINS_PER_WORD)*BITS_PER_PIN);
	    *static_cast<unsigned int*>(word) = ra;
	}

	static void set0(pin_t pin) {
		*reinterpret_cast<unsigned int*>(GPSET0) = 1<<pin;
	}

	static void clear0(pin_t pin) {
		*reinterpret_cast<unsigned int*>(GPCLR0) = 1<<pin;
	}
};

#endif /* GPIO_H_ */
