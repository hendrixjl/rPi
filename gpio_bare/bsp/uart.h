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
#endif
void uart_init ( void );


unsigned int uart_hex_out(const unsigned int n);

unsigned int uart_hex_out(const unsigned char b);

unsigned int uart_outln();

unsigned int uart_out(const char* s);

unsigned int uart_out(const unsigned char* s);

unsigned int uart_out(const bool n);

unsigned int uart_out(const char n);

unsigned int uart_out(const unsigned char n);

unsigned int uart_out(const short number);

unsigned int uart_out(const unsigned short number);

unsigned int uart_out(const int number);

unsigned int uart_out(const unsigned int number);

unsigned int uart_out(const long n);

unsigned int uart_out(const unsigned long n);


#endif /* UART_H_ */
