#include "uart.h"
#include "bar.h"
#include "gpio.h"
#include "mytypes.h"

#define GPFSEL1 0x20200004
#define GPSET0 0x2020001C
#define GPCLR0 0x20200028
#define GPPUD 0x20200094
#define GPPUDCLK0 0x20200098

typedef enum {
	AUX_IRQ = 0,
	AUX_ENABLES = 1,
	AUX_MU_IO_REG = 10,
	AUX_MU_IER_REG = 11,
	AUX_MU_IIR_REG = 12,
	AUX_MU_LCR_REG = 13,
	AUX_MU_MCR_REG = 14,
	AUX_MU_LSR_REG = 15,
	AUX_MU_MSR_REG = 16,
	AUX_MU_SCRATCH = 17,
	AUX_MU_CNTL_REG = 18,
	AUX_MU_STAT_REG = 19,
	AUX_MU_BAUD_REG = 20
} registers_t;


void uart_init ( void )
{
	uart_disable();
    UART_BAR[AUX_MU_IER_REG] = 0;
    UART_BAR[AUX_MU_CNTL_REG] = 0;
    UART_BAR[AUX_MU_LCR_REG] = 3;
    UART_BAR[AUX_MU_MCR_REG] = 0;
    UART_BAR[AUX_MU_IER_REG] = 0x5; //enable rx interrupts
    UART_BAR[AUX_MU_IIR_REG] = 0xC6;
    UART_BAR[AUX_MU_BAUD_REG] = 270;

    gpio_set_fsel(PIN_14, ALT5);
    gpio_set_pud(PIN_14, DISABLE_PULL_UP_DOWN_CTRL);
    gpio_set_fsel(PIN_15, ALT5);
    gpio_set_pud(PIN_15, DISABLE_PULL_UP_DOWN_CTRL);

    UART_BAR[AUX_MU_CNTL_REG] = 3;
}

void uart_enable(void)
{
    UART_BAR[AUX_ENABLES] |= 1;
}

void uart_disable(void)
{
	UART_BAR[AUX_ENABLES] &= ~1;
}

int uart_getc(char* b)
{
    unsigned int st = UART_BAR[AUX_MU_LSR_REG] & 0x01;
    if (st)
    {
    	*b = UART_BAR[AUX_MU_IO_REG] & 0xff;
    }
    return st;
}

int uart_get(char* buffer, size_t len)
{
	int cnt=0;
	for (size_t i=0; i<len; ++i)
	{
		if (uart_getc(&buffer[i]) == -1)
		{
			cnt=-1;
			break;
		}
		cnt++;
	}
	return cnt;
}

int uart_putc(char b)
{
    while(0 != (UART_BAR[AUX_MU_LSR_REG] & 0x20));
    UART_BAR[AUX_MU_IO_REG] = b;
    return 1;
}

int uart_puts(const char* s)
{
	int cnt=0;
	while (*s != '\0')
	{
		if (uart_putc(*s) == -1)
		{
			cnt=-1;
			break;
		}
		cnt++;
		s++;
	}
	return cnt;
}


int uart_put(const void* buffer, size_t len)
{
	const char* bbuf = (const char*)buffer;
	int cnt=0;
	for (size_t i=0; i<len; ++i)
	{
		if (uart_putc(bbuf[i]) == -1)
		{
			cnt=-1;
			break;
		}
		cnt++;
	}
	return cnt;
}
