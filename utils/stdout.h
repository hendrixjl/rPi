/*
 * stdout.h
 *
 *  Created on: Feb 25, 2013
 *      Author: jonathanhendrix
 */

#ifndef STDOUT_H_
#define STDOUT_H_

#include "mytypes.h"


/**
* Put a byte on the standard output.
* @param b - the byte to put
* @return the number of bytes put or -1 for error.
*/
int write(char b);

/**
* Put a string of bytes (ending in null) on the
* standard output device. The null character is *not* sent.
* @param s - the string of bytes
* @return the number of bytes sent or -1 for error.
*/
int write(const char* s);

/**
* Put a number of bytes on the standard output device.
* @param buffer - The buffer containing the data to send.
* @param len - the number of bytes to send.
* @return The number of bytes sent or -1 for error.
*/
int write(const void* buffer, size_t len);

/**
* Write an end of line to the standard output device.
* @return the number of bytes sent or -1 for error.
*/
inline int writeln(void)
{
  return write("\n\r");
}

/**
* Put a byte on the standard output.
* @param b - the byte to put
* @return the number of bytes put or -1 for error.
*/
inline int writeln(char b)
{
	return write(b) + writeln();
}

/**
* Put a string of bytes (ending in null) on the
* standard output device. The null character is *not* sent.
* @param s - the string of bytes
* @return the number of bytes sent or -1 for error.
*/
inline int writeln(const char* s)
{
	return write(s) + writeln();
}


/**
* Put a number of bytes on the standard output device.
* @param buffer - The buffer containing the data to send.
* @param len - the number of bytes to send.
* @return The number of bytes sent or -1 for error.
*/
inline int writeln(const void* buffer, size_t len)
{
	return write(buffer, len) + writeln();
}


#endif /* STDOUT_H_ */
