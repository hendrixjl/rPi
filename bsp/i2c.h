/*
 * i2c.h
 *
 *  Created on: Dec 30, 2012
 *      Author: jonathanhendrix
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <stddef.h>

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
	static i2c& setup(uint16_t bus);

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
	uint32_t get_status() const;

	/**
	 * Return the control bits of this i2c bus device
	 */
	uint32_t get_control() const;

	/**
	 * Send a command to a slave device
	 * on this bus.
	 * @param slaveaddr
	 * @param cmd
	 * @param data_addr
	 * @param data_size
	 */
	size_t command(uint8_t slaveaddr,
			uint8_t cmd,
			const uint8_t* data_addr=0,
			size_t data_size=0);

	/**
	 * Query a register on a slave device. Return
	 * a one-byte reply
	 * @param slaveaddr
	 * @param slave_register
	 * @return reply
	 */
	uint8_t query(uint8_t slaveaddr,
		      uint8_t slave_register);


	/**
	 * Query multiple registers on a slave device. Return
	 * the multi-byte reply
	 * @param slaveaddr
	 * @param slave_register
	 * @param buffer
	 * @param buffer_size
	 * @return number of bytes read
	 */
	size_t query(uint8_t slaveaddr,
			uint8_t slave_register,
			uint8_t* buffer,
			size_t buffer_size);

	/**
	 * Return the base address register for
	 * the bus.
	 */
	uint32_t get_bar() const;

private:
	volatile uint32_t* bar_;

	/**
	 * Construct an i2c bus using
	 * a base address register
	 */
	explicit i2c(volatile uint32_t *bar);

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
	void push_byte_on_fifo(uint8_t byte);

	/**
	 * Pop a byte from the FIFO
	 */
	uint8_t pop_byte_from_fifo() const;

	/**
	 * Read a data byte from an i2c slave
	 * @param byte
	 * @return true if a byte was read
	 */
	bool read_byte(uint8_t& byte) const;

	/**
	 * Write a byte to an already-address i2c slave
	 * @param byte
	 * @return true if successful
	 */
	bool write_byte(uint8_t byte);

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
	void set_slave_address(uint8_t slaveaddr);

	/**
	 * Set the data length of an upcoming
	 * i2c transfer
	 * @param len
	 */
	void set_data_len(size_t len);

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
	uint8_t get_slave_address() const;

	/**
	 * Set the clock divider for the i2c bus device clock
	 * @param div (defaults to 0x5DC [100 kHz])
	 */
	void set_clk_divider(uint16_t div=0x5DC) const;

	/**
	 * Set the delay for the i2c bus device.
	 * @param delay (defaults to 0x0000 0030 0000 0030
	 */
	void set_delay(uint32_t delay=0x0300030) const;

	/**
	 * Set clkt for the i2c bus device.
	 * @param clkt (defauts to 0x040)
	 */
	void set_clkt(uint8_t clkt=0x040) const;

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
