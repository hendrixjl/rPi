/*
 * pwm.cpp
 *
 *  Shamelessly stolen
 */

#include "pwm.h"
#include "bar.h"
#include "gpio.h"
#include "timeUtils.h"

enum {
	PWM_CTL=0,
	PWM_STA=1,  // 0x04
	PWM_DMAC=2, // 0x08
	PWM_RSV1=3, // 0x0C
	PWM_RNG1=4, // 0x10
	PWM_DAT1=5, // 0x14
	PWM_FIF1=6, // 0x18
	PWM_RSV2=7, // 0x1C
	PWM_RNG2=8, // 0x20
	PWM_DAT2=9  // 0x24
};

enum {
	PWMClK_CNTL = 40,
	PWMCLK_DIV = 41
};

void setServo(int percent)
{
	int bitCount;
	unsigned int bits = 0;

	// 32 bits = 2 milliseconds
	bitCount = 16 + 16 * percent / 100;
	if (bitCount > 32) bitCount = 32;
	if (bitCount < 1) bitCount = 1;
	bits = 0;
	while (bitCount) {
		bits <<= 1;
		bits |= 1;
		bitCount--;
	}
	PWM_BAR[PWM_DAT1] = bits; // *(pwm + PWM_DAT1) = bits;
}

// init hardware
void initHardware()
{

	// set PWM alternate function for GPIO18
	gpio_set_fsel(PIN_18, ALT1); // SET_GPIO_ALT(18, 5);

	// stop clock and waiting for busy flag doesn't work, so kill clock
	CLOCK_BAR[PWMClK_CNTL] = 0x5A000000 | (1 << 5); //*(clk + PWMCLK_CNTL) = 0x5A000000 | (1 << 5);
	// needs some time
	enum { WAIT_150_CYCLES = 150 };
	busyloop(WAIT_150_CYCLES);

	// set frequency
	// DIVI is the integer part of the divisor
	// the fractional part (DIVF) drops clock cycles to get the output frequency, bad for servo motors
	// 320 bits for one cycle of 20 milliseconds = 62.5 us per bit = 16 kHz
	int idiv = (int) (19200000.0f / 16000.0f);
//	if (idiv < 1 || idiv > 0x1000) {
//		printf("idiv out of range: %x\n", idiv);
//		exit(-1);
//	}
	CLOCK_BAR[PWMCLK_DIV] = 0x5A000000 | (idiv<<12); //*(clk + PWMCLK_DIV)  = 0x5A000000 | (idiv<<12);

	// source=osc and enable clock
	CLOCK_BAR[PWMClK_CNTL] = 0x5A000011; //*(clk + PWMCLK_CNTL) = 0x5A000011;

	// disable PWM
	PWM_BAR[PWM_CTL] = 0; // *(pwm + PWM_CTL) = 0;

	// needs some time until the PWM module gets disabled, without the delay the PWM module crashs
	enum { WAIT_150_CYCLES = 150 };
	busyloop(WAIT_150_CYCLES);

	// filled with 0 for 20 milliseconds = 320 bits
	PWM_BAR[PWM_RNG1] = 320; // *(pwm + PWM_RNG1) = 320;

	// 32 bits = 2 milliseconds, init with 1 millisecond
	setServo(0);

	// start PWM1 in serializer mode
	PWM_BAR[PWM_CTL] = 3; // *(pwm + PWM_CTL) = 3;
}
