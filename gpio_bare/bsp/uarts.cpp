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

