/*
 * stdout.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#include <iostream>
#include <string.h>
using namespace std;

/**
* Put a byte on the output.
* @param b - the byte to put
* @return the number of bytes put or -1 for error.
*/
int write(char b)
{
	cout << b;
	return 1;
}

/**
* Put a string of bytes (ending in null) on the
* uart. The null character is *not* sent.
* @param s - the string of bytes
* @return the number of bytes sent or -1 for error.
*/
int write(const char* s)
{
	cout << s;
	return strlen(s);
}

/**
* Put a number of bytes on the uart.
* @param buffer - The buffer containing the data to send.
* @param len - the number of bytes to send.
* @return The number of bytes sent or -1 for error.
*/
int write(const void* buffer, size_t len)
{
	write(static_cast<const char*>(buffer), len);
	return len;
}
