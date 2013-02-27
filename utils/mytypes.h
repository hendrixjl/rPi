#ifndef __MYTYPES_H__
#define __MYTYPES_H__

#ifdef __BARE_METAL__
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

#else

#include <stdint.h>
#include <stdlib.h>

#endif

#endif
