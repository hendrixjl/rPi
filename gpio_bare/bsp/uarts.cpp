/*
 * uart.cpp
 *
 *  Created on: Dec 16, 2012
 *      Author: jonathanhendrix
 */


#include "uart.h"

extern "C" void uart_putc ( unsigned int c );


extern "C" unsigned int hexstrings ( unsigned int d );
extern "C" unsigned int hexstring ( unsigned int d );

extern "C" unsigned int putstr(const unsigned char* s);


unsigned int uart_outln()
{
	uart_putc('\n');
	uart_putc('\r');
	enum { TWO_CHARS=2 };
	return TWO_CHARS;
}

unsigned int uart_out(const char* s)
{
	return putstr(reinterpret_cast<const unsigned char*>(s));
}

unsigned int uart_out(const unsigned char* s)
{
	return putstr(s);
}

unsigned int uart_hex_out(const unsigned int n)
{
	return hexstrings(n);
}

unsigned int uart_hex_out(const unsigned char n)
{
	return hexstrings(n);
}

unsigned int uart_out(const bool b)
{
	if (b)
	{
	    uart_putc('1');
	}
	else
	{
		uart_putc('0');
	}
	return 1;
}

// Output a single digit. Assumes n<10
void uart_out_digit(const unsigned int& n)
{
	uart_putc('0' + n);
}

unsigned int uart_out(const unsigned long n)
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

unsigned int uart_out(const long number)
{
	bool neg = (number < 0);
	unsigned int n = (neg) ? -number : number;
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

	if (neg)
	{
		buffer[MAX_DIGITS_IN_32_BIT_NUM-count]='-';
		count++;
	}
	return putstr(&buffer[MAX_DIGITS_IN_32_BIT_NUM-count+1]);
}

unsigned int uart_out(const short number)
{
	return uart_out(static_cast<long>(number));
}

unsigned int uart_out(const unsigned short number)
{
	return uart_out(static_cast<unsigned long>(number));
}

unsigned int uart_out(const int number)
{
	return uart_out(static_cast<long>(number));
}

unsigned int uart_out(const unsigned int number)
{
	return uart_out(static_cast<unsigned long>(number));
}

