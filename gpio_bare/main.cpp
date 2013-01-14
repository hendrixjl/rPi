
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


#include "gpio.h"
#include "bsp.h"
#include "arm_timer.h"
#include "interrupts.h"
#include "utils.h"
#include "uart.h"
#include "i2c.h"
#include "l3gd20.h"
#include "mcp23008.h"

extern "C" void enable_irq ( void );

//-------------------------------------------------------------------------


volatile unsigned int icount;
extern "C" void c_irq_handler ( void )
{
	arm_timer_clear_irq();
    icount++;
    if(icount&1)
    {
        gpio_t::clear0(gpio_t::PIN_16);
    }
    else
    {
        gpio_t::set0(gpio_t::PIN_16);
    }
}

extern "C"
int notmain ( )
{
	uart_init ();

    disable_basic_interrupt(IRQ_ARM_TIMER);

	uart_out("Hello from gpio_bare");
	uart_outln();
    uart_outln();
    unsigned long n = 0xffffffff;
    uart_out(n);
    uart_outln();
    uart_out("123456789012345678901234567890");
    uart_outln();
    n = 123456789UL;
    uart_out(n);
    uart_outln();

    long nn = -1234;
    uart_out(nn);
    uart_outln();

    nn = -123456789;
    uart_out(nn);
    uart_outln();

    gpio_t::fsel(gpio_t::PIN_16, gpio_t::OUTPUT);

    enum {
    	TIMER_LOAD=1000000-1,
    	TIMER_RELOAD=1000000-1,
    	PRESCALE_CNTRL=0xF9
    };
//    timer.setup(TIMER_LOAD, TIMER_RELOAD, PRESCALE_CNTRL);
//    timer.enable();
//    uart_out("Enable Timer: (IRQ Disabled)");
//	uart_outln();
//    timer_reg_dump();
//
//    for (unsigned int ra=0; ra<3; ++ra) {
//    	timer_reg_dump();
//		if (timer.irq_pending_raw()) {
//			timer.clear_timer_irq();
//		}
//		busy_loop(2500000);
//    }
//
//    timer.clear_timer_irq();
//    timer.irq_enable();
//    uart_out("IRQ Enabled");
//	uart_outln();
//    timer_reg_dump();
//
//	uart_outln();

    uart_out("Use ISR to toggle LED.");
	uart_outln();

	arm_timer_setup(TIMER_LOAD, TIMER_RELOAD, PRESCALE_CNTRL, PRESCALE_IS_CLOCK_DIV_1, TWENTY_THREE_BITS);
    arm_timer_clear_irq();
    arm_timer_irq_enable();
    arm_timer_enable();
    enable_basic_interrupt(IRQ_ARM_TIMER);
    enable_irq();

    uart_outln();

    uart_out("i2c ");
    i2c i2c1(reinterpret_cast<unsigned int*>(i2c::BSC1_BAR));
    uart_outln();

    i2c1.init();
    i2c1.enable();
    uart_out(" bar=");
    uart_hex_out(i2c1.get_control());
    uart_out(" cntrl=");
    uart_hex_out(i2c1.get_control());
    uart_out(" status=");
    uart_hex_out(i2c1.get_status());
    uart_outln();

    enum { LG3D20_ADDR=0x06B };
    l3gd20 gyro(LG3D20_ADDR, i2c1);
    gyro.enable();
    uart_out("cntrl1=");
    uart_hex_out(gyro.get_ctrl1());
    uart_out(" who=");
    uart_hex_out(gyro.identify());
    uart_outln();

    for (unsigned g=0; g<10; g++)
    {
    	short temp=0;
    	unsigned char status=0;
    	short x=0,y=0,z=0;
    	if (gyro.measurements(temp, status, x, y, z))
    	{
			uart_out(" temp=");
			uart_out(temp);
			uart_out(" status=");
			uart_hex_out(status);
			uart_out(" (");
			uart_out(x);
			uart_out(",");
			uart_out(y);
			uart_out(",");
			uart_out(z);
			uart_out(")");
			uart_outln();
    	}
    	else
    	{
    		uart_out("no data");
    		uart_outln();
    	}
    }

    enum { MCP23008_ADDRESS=0x20 };
    mcp23008 mcp(MCP23008_ADDRESS, i2c1);
    mcp.set_olat(mcp23008::PIN_ALL, mcp23008::OFF);

    uart_out("mcp23008. iodir=");
    uart_hex_out(mcp.get_iodir());
    uart_out(" ipol=");
    uart_hex_out(mcp.get_input_polarity());
    uart_out(" gpio=");
    uart_hex_out(mcp.get_gpio());
    uart_out(" olat=");
    uart_hex_out(mcp.get_olat());
    uart_outln();

    mcp.set_iodir(mcp23008::PIN7, mcp23008::OUTPUT);
    mcp.set_input_polarity(mcp23008::PIN7, mcp23008::INVERSE_LOGIC);
    mcp.set_olat(mcp23008::PIN7, mcp23008::ON);

    uart_out("mcp23008. iodir=");
    uart_hex_out(mcp.get_iodir());
    uart_out(" ipol=");
    uart_hex_out(mcp.get_input_polarity());
    uart_out(" gpio=");
    uart_hex_out(mcp.get_gpio());
    uart_out(" olat=");
    uart_hex_out(mcp.get_olat());
    uart_outln();

    i2c1.init();

    for (volatile unsigned ti=0; ti<10000; ++ti);
    uart_init();

    while(1) continue;

    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
