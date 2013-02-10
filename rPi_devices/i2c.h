/*
 * i2c.h
 *
 *  Created on: Dec 30, 2012
 *      Author: jonathanhendrix
 */

#ifndef I2C_H_
#define I2C_H_

#ifdef __BARE_METAL__
#include "i2c.h"
#else
#include "i2c_linux.h"
#endif

#endif /* I2C_H_ */
