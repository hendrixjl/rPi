#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
/**
* Initialize the uart. Starts off disabled.
*/
void uart_init ( void );

/**
 * Enable the uart. Call after uart_init.
 */
void uart_enable(void);

/**
 * Disable the uart.
 */
void uart_disable(void);

/**
* Get a char from the uart.
* @param b - pointer to the char to receive
* @param Number of bytes receives or -1 for error.
*/
int uart_getc(char* b);

/**
* Get a sequence of bytes from the uart.
* Note: this routine does *not* guarantee null termination.
* @param buffer - where to place the bytes.
* @param len - the available bytes in the buffer.
* @return the number of bytes returned or -1 for error.
*/
int uart_get(char* buffer, size_t len);

/**
* Put a byte on the uart.
* @param b - the byte to put
* @return the number of bytes put or -1 for error.
*/
int uart_putc(char b);

/**
* Put a string of bytes (ending in null) on the
* uart. The null character is *not* sent.
* @param s - the string of bytes
* @return the number of bytes sent or -1 for error.
*/
int uart_puts(const char* s);

/**
* Put a number of bytes on the uart.
* @param buffer - The buffer containing the data to send.
* @param len - the number of bytes to send.
* @return The number of bytes sent or -1 for error.
*/
int uart_put(const void* buffer, size_t len);

/**
* Write an end of line to the uart.
* @return the number of bytes sent or -1 for error.
*/
inline int uart_nl(void)
{
  return uart_puts("\n\r");
}

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
