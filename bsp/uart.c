
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
#include "uart.h"


#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098

#define AUX_ENABLES     0x20215004
#define AUX_MU_IO_REG   0x20215040
#define AUX_MU_IER_REG  0x20215044
#define AUX_MU_IIR_REG  0x20215048
#define AUX_MU_LCR_REG  0x2021504C
#define AUX_MU_MCR_REG  0x20215050
#define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_MSR_REG  0x20215058
#define AUX_MU_SCRATCH  0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068
//------------------------------------------------------------------------
unsigned int uart_recv ( unsigned char* b )
{
    unsigned int st = (*(unsigned int*)AUX_MU_LSR_REG) & 0x01;
    if (st) *b = (*(unsigned int*)AUX_MU_IO_REG)&0xff;
    return st;
}

void busy(unsigned int n)
{
	for(volatile unsigned i=0; i<150; i++);
}
//------------------------------------------------------------------------
void uart_init ( void )
{
    unsigned int ra;

    *(unsigned int*)AUX_ENABLES = 1;
    *(unsigned int*)AUX_MU_IER_REG = 0;
    *(unsigned int*)AUX_MU_CNTL_REG = 0;
    *(unsigned int*)AUX_MU_LCR_REG = 3;
    *(unsigned int*)AUX_MU_MCR_REG = 0;
    *(unsigned int*)AUX_MU_IER_REG = 0x5; //enable rx interrupts
    *(unsigned int*)AUX_MU_IIR_REG = 0xC6;
    *(unsigned int*)AUX_MU_BAUD_REG = 270;

    ra = *(unsigned int*)GPFSEL1;
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    *(unsigned int*)GPFSEL1 = ra;

    *(unsigned int*)GPPUD = 0;
    busy(150);
    *(unsigned int*)GPPUDCLK0 = (1<<14)|(1<<15);
    busy(150);
    *(unsigned int*)GPPUDCLK0 = 0;

    *(unsigned int*)AUX_MU_CNTL_REG = 3;
}
//------------------------------------------------------------------------
void uart_putc ( unsigned int c )
{
    while(1)
    {
        if(*(unsigned int*)AUX_MU_LSR_REG & 0x20) break;
    }
    *(unsigned int*)AUX_MU_IO_REG = c;
}
//------------------------------------------------------------------------

unsigned char hex_digit(const unsigned int i)
{
	if (i>9) {
		return i + 'A' - 10;
	} else {
		return i + '0';
	}
}

unsigned int hexstrings ( const unsigned int d )
{
    unsigned int rb;
    unsigned int rc;

    enum {
    	HEX_DIGITS_IN_32_BIT_NUM = 8,
    	BITS_IN_32_BIT_NUM=32
    };

    rb=BITS_IN_32_BIT_NUM;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        uart_putc(hex_digit(rc));
        if(rb==0) break;
    }
    return HEX_DIGITS_IN_32_BIT_NUM;
}
//------------------------------------------------------------------------
unsigned int bytehexstrings ( const unsigned char d )
{
	uart_putc(hex_digit((d & 0xF0)>>4));
	uart_putc(hex_digit(d & 0x0F));
    enum { HEX_DIGITS_IN_8_BIT_NUM = 2 };
    return HEX_DIGITS_IN_8_BIT_NUM;
}
//------------------------------------------------------------------------
unsigned int hexstring ( unsigned int d )
{
    unsigned int i = hexstrings(d);
    uart_putc(0x0D);
    uart_putc(0x0A);
    return i+2;
}

unsigned int putstr( const unsigned char* s )
{
	const unsigned char* start = s;
	while (*s) {
		uart_putc(*s);
		++s;
	}
	return (s - start);
}


unsigned int uart_hex_out(const unsigned int n)
{
	return hexstrings(n);
}

unsigned int uart_hex_byte_out(const unsigned char n)
{
	return bytehexstrings(n);
}


unsigned int uart_outln()
{
	uart_putc('\n');
	uart_putc('\r');
	enum { TWO_CHARS=2 };
	return TWO_CHARS;
}

unsigned int uart_string_out(const char* s)
{
	return putstr((const unsigned char*)s);
}

unsigned int uart_ustring_out(const unsigned char* s)
{
	return putstr(s);
}

unsigned int uart_char_out(const char n)
{
	uart_putc(n);
	enum { ONE_BYTE=1 };
	return ONE_BYTE;
}

unsigned int uart_uchar_out(const unsigned char n)
{
	uart_putc(n);
	enum { ONE_BYTE=1 };
	return ONE_BYTE;
}

unsigned int uart_unsigned_out(const unsigned long n)
{
	enum { MAX_DIGITS_IN_32_BIT_NUM=10 };
	unsigned char buffer[MAX_DIGITS_IN_32_BIT_NUM+2]={}; // last char stays null
	unsigned temp = n;
	unsigned count = 0;
	while (temp > 0)
	{
		buffer[MAX_DIGITS_IN_32_BIT_NUM-count]='0' + temp%10;
		temp /= 10;
		count++;
	}
	return putstr(&buffer[MAX_DIGITS_IN_32_BIT_NUM-count+1]);
}

unsigned int uart_signed_out(const long number)
{
	if (number == 0) {
		return uart_char_out('0');
	}
	unsigned int n = (number < 0) ? -number : number;
	enum { MAX_DIGITS_IN_32_BIT_NUM=11 };
	unsigned char buffer[MAX_DIGITS_IN_32_BIT_NUM+2]={};
	unsigned temp = n;
	unsigned count = 0;
	while (temp > 0)
	{
		buffer[MAX_DIGITS_IN_32_BIT_NUM-count]='0' + temp%10;
		temp /= 10;
		count++;
	}

	if (number < 0)
	{
		buffer[MAX_DIGITS_IN_32_BIT_NUM-count]='-';
		count++;
	}
	return putstr(&buffer[MAX_DIGITS_IN_32_BIT_NUM-count+1]);
}
