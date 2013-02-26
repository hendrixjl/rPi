#include "uart.h"

/**
* Put a byte on the output.
* @param b - the byte to put
* @return the number of bytes put or -1 for error.
*/
int write(char b)
{
	return uart_putc(b);
}

/**
* Put a string of bytes (ending in null) on the
* uart. The null character is *not* sent.
* @param s - the string of bytes
* @return the number of bytes sent or -1 for error.
*/
int write(const char* s)
{
	return uart_puts(s);
}

/**
* Put a number of bytes on the uart.
* @param buffer - The buffer containing the data to send.
* @param len - the number of bytes to send.
* @return The number of bytes sent or -1 for error.
*/
int write(const void* buffer, size_t len)
{
	return uart_put(buffer, len);
}
