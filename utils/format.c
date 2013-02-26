#include "format.h"

#include mytypes.h"

char to_digit(const unsigned int i)
{
  if (i>9) {
		return i + 'A' - 10;
	} else {
		return i + '0';
	}
}

unsigned from_digit(unsigned c)
{
	if (c <= '9')
	{
		return c - '0';
	}
	else if (c <= 'Z')
	{
		return c - 'A' + 10;
	}
	else
	{
		return c - 'a' + 10;
	}
}


unsigned count_digits(unsigned n, unsigned base)
{
	int ndigits = 0;
	while (n>0) {
		n /= base;
		++ndigits;
	}
	return ndigits;
}

int unsigned_to_nstring(char* buffer, size_t blen, unsigned n, unsigned base)
{
	int cnt=0;
	unsigned digits = count_digits(n, base);
	if (digits > blen-1) return -1;
	buffer[digits] = '\0';
	unsigned temp = n;
	while (temp > 0)
	{
    	buffer[digits-cnt-1]=to_digit(temp%base);
    	temp /= base;
    	cnt++;
	}
	return cnt;
}

int unsigned_to_string(char* buffer, size_t blen, unsigned n)
{
	enum { BASE = 10 };
	return unsigned_to_nstring(buffer, blen, n, BASE);
}

int int_to_string(char* buffer, size_t blen, int n)
{
	enum { BASE = 10 };
	if (n < 0)
	{
		buffer[0] = '-';
		n = -n;
		++buffer;
		--blen;
	}
	return unsigned_to_string(buffer, blen, (unsigned)n);
}

int unsigned_to_xstring(char* buffer, size_t blen, unsigned n)
{
	enum { BASE = 16 };
	return unsigned_to_nstring(buffer, blen, n, BASE);
}

int unsigned_to_bstring(char* buffer, size_t blen, unsigned n)
{
	enum { BASE = 2 };
	return unsigned_to_nstring(buffer, blen, n, BASE);
}

int string_to_nunsigned(unsigned* n, const char* buffer, unsigned base)
{
	int cnt=0;
	*n = 0;
	while (*buffer != '\0') {
		*n *= base;
		*n += from_digit((unsigned)*buffer++);
	}
	return cnt;
}

int string_to_ninteger(int* n, const char* buffer, unsigned base)
{
	int s=1;
	if (*buffer == '-') {
		s=-1;
		buffer++;
	}
	unsigned u=0;
	int cnt = string_to_unsigned(&u, buffer);
	if (cnt != -1)
	{
		*n = s*(int)u;
		if (s == -1) {
			++cnt; // for leading '-'
		}
	}

	return cnt;
}

int string_to_unsigned(unsigned* n, const char* buffer)
{
	enum { BASE=10 };
	return string_to_nunsigned(n, buffer, BASE);
}

int xstring_to_unsigned(unsigned* n, const char* buffer)
{
	enum { BASE=16 };
	return string_to_nunsigned(n, buffer, BASE);
}

int bstring_to_unsigned(unsigned* n, const char* buffer)
{
	enum { BASE=2 };
	return string_to_nunsigned(n, buffer, BASE);
}

int string_to_int(int* n, const char* buffer)
{
	enum { BASE=10 };
	return string_to_ninteger(n, buffer, BASE);
}
