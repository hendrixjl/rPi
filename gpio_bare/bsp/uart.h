/*
 * uart.h
 *
 *  Created on: Dec 1, 2012
 *      Author: jonathanhendrix
 */

#ifndef UART_H_
#define UART_H_

#ifdef __cplusplus
extern "C"
{
#endif
void uart_init ( void );


unsigned int uart_hex_out(const unsigned int n);

unsigned int uart_hex_byte_out(const unsigned char b);

unsigned int uart_outln();

unsigned int uart_string_out(const char* s);

unsigned int uart_ustring_out(const unsigned char* s);

unsigned int uart_char_out(const char n);

unsigned int uart_uchar_out(const unsigned char n);

unsigned int uart_signed_out(const long n);

unsigned int uart_unsigned_out(const unsigned long n);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
