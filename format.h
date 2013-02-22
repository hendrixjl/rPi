#ifndef FORMAT_H_
#define FORMAT_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum {
  RECOMMENDED_BUFFER_SIZE=33 // will fit binary
};

/**
 * Convert an unsigned integer to string.
 * @param buffer - the data buffer to store the string in
 * @param blen - the available space in the buffer
 * @param n - the number to convert
 * @return The number of characters used. -1 if error.
 */
int unsigned_to_string(char* buffer, size_t blen, unsigned n);

/**
 * Convert an integer to string.
 * @param buffer - the data buffer to store the string in
 * @param blen - the available space in the buffer
 * @param n - the number to convert
 * @return The number of characters used. -1 if error.
 */
int int_to_string(char* buffer, size_t blen, int n);

/**
 * Convert an unsigned integer to a hex string.
 * @param buffer - the data buffer to store the string in
 * @param blen - the available space in the buffer
 * @param n - the number to convert
 * @return The number of characters used. -1 if error.
 */
int unsigned_to_xstring(char* buffer, size_t blen, unsigned n);

/**
 * Convert an unsigned integer to a binary string.
 * @param buffer - the data buffer to store the string in
 * @param blen - the available space in the buffer
 * @param n - the number to convert
 * @return The number of characters used. -1 if error.
 */
int unsigned_to_bstring(char* buffer, size_t blen, unsigned n);

/**
 * Convert decimal string to unsigned integer
 * @param n - Pointer to the resulting unsigned
 * @param buffer - The string holding the number
 * @return The number of characters used. -1 if error.
 */
int string_to_unsigned(unsigned* n, const char* buffer);

/**
 * Convert a hex string to unsigned integer.
 * @param n - Pointer to the resulting unsigned
 * @param buffer - The string holding the number
 * @return The number of characters used. -1 if error.
 */
int xstring_to_unsigned(unsigned* n, const char* buffer);

/**
 * Convert a binary string to unsigned integer.
 * @param n - Pointer to the resulting unsigned
 * @param buffer - The string holding the number
 * @return The number of characters used. -1 if error.
 */
int bstring_to_unsigned(unsigned* n, const char* buffer);


/**
 * Convert decimal string to integer
 * @param n - Pointer to the resulting unsigned
 * @param buffer - The string holding the number
 * @return The number of characters used. -1 if error.
 */
int string_to_int(int* n, const char* buffer);

#ifdef __cplusplus
}
#endif


#endif /* FORMAT_H_ */
