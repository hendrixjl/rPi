/*
 * i2c.h
 *
 *  Created on: Dec 30, 2012
 *      Author: jonathanhendrix
 */

#ifndef I2C_H_
#define I2C_H_

#include "bar.h"
/**
 * The i2c class encapsulates interactions on an i2c bus.
 * Usage:
 * Invoke i2c::setup(bus), where bus is 0, 1, or 2.
 * This will initialize the given i2c bus. The associated i2c0, i2c1, and i2c2 pointers
 * will be setup for use. Only i2c0 and ic21 are available on the raspberry pi (rev 2 board)
 */

class i2c {
public:
	/**
	 * Setup the i2c bus and initialize it to disabled.
	 * @param bus
	 * @return a i2c object address
	 */
	static i2c& setup(unsigned short bus);

	/**
	 * Enable this i2c bus
	 */
	void enable();

	/**
	 * Disable this i2c bus
	 */
	void disable();

	/**
	 * Return the status bits of this i2c bus device
	 */
	unsigned int get_status() const;

	/**
	 * Return the control bits of this i2c bus device
	 */
	unsigned int get_control() const;

	/**
	 * Send a command to a slave device
	 * on this bus.
	 * @param slaveaddr
	 * @param cmd
	 * @param data_addr
	 * @param data_size
	 */
	unsigned command(unsigned char slaveaddr,
			unsigned char cmd,
			const unsigned char* data_addr=0,
			unsigned data_size=0);

	/**
	 * Query a register on a slave device. Return
	 * a one-byte reply
	 * @param slaveaddr
	 * @param slave_register
	 * @return reply
	 */
	unsigned char query(unsigned char slaveaddr,
			unsigned char slave_register);


	/**
	 * Query multiple registers on a slave device. Return
	 * the multi-byte reply
	 * @param slaveaddr
	 * @param slave_register
	 * @param buffer
	 * @param buffer_size
	 * @return number of bytes read
	 */
	unsigned query(unsigned char slaveaddr,
			unsigned char slave_register,
			unsigned char* buffer,
			unsigned buffer_size);

	/**
	 * Return the base address register for
	 * the bus.
	 */
	unsigned int get_bar() const;

private:


	/**
	 * Construct an i2c bus using
	 * a base address register
	 */
	explicit i2c(volatile unsigned int *bar);

	/**
	 * Initialize the bus, clear the slave
	 * address, disable the bus.
	 */
	void init();

	/**
	 * Clear the FIFO on the bus device
	 */
	void clear_fifo();

	/**
	 * Clear the DONE bit for the bus device
	 */
	void clear_done();

	/**
	 * Is there received data in the FIFO?
	 * @return true if so
	 */
	bool rx_data_avail() const;

	/**
	 * Is there room in the FIFO for transmit data?
	 * @return true if so
	 */
	bool tx_room_avail() const;

	/**
	 * Push a byte on the FIFO
	 * @param byte
	 */
	void push_byte_on_fifo(unsigned char byte);

	/**
	 * Pop a byte from the FIFO
	 */
	unsigned char pop_byte_from_fifo() const;

	/**
	 * Read a data byte from an i2c slave
	 * @param byte
	 * @return true if a byte was read
	 */
	bool read_byte(unsigned char& byte) const;

	/**
	 * Write a byte to an already-address i2c slave
	 * @param byte
	 * @return true if successful
	 */
	bool write_byte(unsigned char byte);

	/**
	 * What is the state of an i2c transfer
	 * @return true if the DONE bit is set
	 */
	bool txfer_done() const;

	/**
	 * Reset the transfer bit on the i2c bus device
	 */
	void reset_txfer_done() const;

	/**
	 * Busy wait for the done bit to be set for the
	 * i2c bus device
	 */
	void wait_for_done();

	/**
	 * Set the slave address for the i2c bus device
	 * @param slaveaddr
	 */
	void set_slave_address(unsigned char slaveaddr);

	/**
	 * Set the data length of an upcoming
	 * i2c transfer
	 * @param len
	 */
	void set_data_len(unsigned len);

	/**
	 * Initiate a write to an i2c slave device.
	 */
	void initiate_write();

	/**
	 * Initiate a read from an i2c slave device
	 */
	void initiate_read();

	/**
	 * Return the slave address currently
	 * set for this i2c bus device
	 * @return the slave address
	 */
	unsigned char get_slave_address() const;

	/**
	 * Set the clock divider for the i2c bus device clock
	 * @param div (defaults to 0x5DC [100 kHz])
	 */
	void set_clk_divider(unsigned short div=0x5DC) const;

	/**
	 * Set the delay for the i2c bus device.
	 * @param delay (defaults to 0x0000 0030 0000 0030
	 */
	void set_delay(unsigned int delay=(0x030 << 16) + 0x030) const;

	/**
	 * Set clkt for the i2c bus device.
	 * @param clkt (defauts to 0x040)
	 */
	void set_clkt(unsigned char clkt=0x040) const;

	i2c(const i2c&); // no copy
	i2c& operator=(const i2c&); // no assign

	/**
	 * Setup the i2c bus 0 and initialize it to disabled.
	 */
	static i2c& setup0();

        /**
	 * Setup the i2c bus 1 and initialize it to disabled.
	 */
	static i2c& setup1();

        /**
	 * Setup the i2c bus 2 and initialize it to disabled.
	 */
	static i2c& setup2();

};


#endif /* I2C_H_ */
