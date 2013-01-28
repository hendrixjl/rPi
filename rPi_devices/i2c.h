/*
 * i2c.h
 *
 *  Created on: Dec 30, 2012
 *      Author: jonathanhendrix
 */

#ifndef I2C_H_
#define I2C_H_

class i2c;
extern i2c* i2c0;
extern i2c* i2c1;
extern i2c* i2c2;

class i2c {
	enum {
		BSC0_BAR = 0x20205000,
		BSC1_BAR = 0x20804000,
		BSC2_BAR = 0x20805000
	};
public:
	static void setup() {
		static i2c i2c0r(reinterpret_cast<unsigned int*>(BSC0_BAR));
		static i2c i2c1r(reinterpret_cast<unsigned int*>(BSC1_BAR));
		static i2c i2c2r(reinterpret_cast<unsigned int*>(BSC2_BAR));
		i2c0 = &i2c0r;
		i2c1 = &i2c1r;
		i2c2 = &i2c2r;
	}

	explicit i2c(unsigned int *bar)
	: bar_ (bar)
	{
		init();
	}

	unsigned int get_bar() const
	{
		return (unsigned int)bar_;
	}

	void init()
	{
		bar_[CNTRL_REG] = 0;
		set_clk_divider();
		set_delay();
		set_clkt();
		bar_[SLAVE_ADDR_REG] = 0;
		bar_[DLEN_REG] = 0;
	}

	void enable()
	{
		bar_[CNTRL_REG] |= I2CEN;
	}

	void disable()
	{
		bar_[CNTRL_REG] &= ~I2CEN;
	}

	unsigned int get_status() const
	{
		return bar_[STATUS_REG];
	}

	unsigned int get_control() const
	{
		return bar_[CNTRL_REG];
	}

	unsigned command(unsigned char slaveaddr,
			unsigned char cmd,
			const unsigned char* data=0,
			unsigned data_size=0)
	{
		reset_txfer_done();
		set_slave_address(slaveaddr);
		set_data_len(1 + data_size);
		initiate_write();
		write_byte(cmd);
		unsigned bytes_sent=1;
		while (data_size>0)
		{
			if (write_byte(*data))
			{
				data++;
				data_size--;
				bytes_sent++;
			}
			// TODO check for error conditions
		}
		wait_for_done();
		clear_fifo();
		return bytes_sent;
	}

	unsigned char query(unsigned char slaveaddr,
			unsigned char slave_register)
	{
		command(slaveaddr, slave_register);
		initiate_read();
		unsigned char b;
		while (!read_byte(b)); // loop until success
		clear_fifo();
		// TODO error conditions?
		return b;
	}

	unsigned query(unsigned char slaveaddr,
			unsigned char slave_register,
			unsigned char* buffer,
			unsigned buffer_size)
	{
		enum { READ_MULTIPLE=0x080 };
		command(slaveaddr, slave_register | READ_MULTIPLE);
		set_data_len(buffer_size);
		initiate_read();
		unsigned bytes_read=0;
		while (buffer_size > 0)
		{
			if (read_byte(*buffer))
			{
				buffer_size--;
				bytes_read++;
				buffer++;
			}
			// TODO check for error conditions
		}
		clear_fifo();
		return bytes_read;
	}

private:

	enum registers_t {
		CNTRL_REG = 0x0000,
		STATUS_REG = 0x0001,
		DLEN_REG = 0x0002,
		SLAVE_ADDR_REG = 0x0003,
		FIFO_REG = 0x0004,
		CLOCK_DIV_REG = 0x0005,
		DATA_DELAY_REG = 0x0006,
		CLKT_REG = 0x0007
	};

	enum control_bits_t {
		I2CEN = 1 << 15,
		INTR = 1 << 10,
		INTT = 1 << 9,
		INTD = 1 << 8,
		ST = 1 << 7,
		CLEAR = 1 << 4,
		READ = 1
	};

	enum status_bits_t {
		CLKT=1<<9,
		ERR=1<<8,
		RXF=1<<7,
		TXE=1<<6,
		RXD=1<<5,
		TXD=1<<4,
		RXR=1<<3,
		TXW=1<<2,
		DONE=1<<1,
		TA=1<<0
	};

	void clear_fifo() {
		bar_[CNTRL_REG] |= CLEAR;
	}

	void clear_done() {
		bar_[STATUS_REG] |= DONE;
	}

	/**
	 * Is there received data in the FIFO?
	 */
	bool rx_data_avail() const
	{
		return bar_[STATUS_REG] & RXD;
	}

	/**
	 * Is there room in the FIFO for transmit data?
	 */
	bool tx_room_avail() const
	{
		return bar_[STATUS_REG] & TXD;
	}

	void push_byte_on_fifo(unsigned char b)
	{
		bar_[FIFO_REG] = b;
	}

	unsigned char pop_byte_from_fifo() const
	{
		return bar_[FIFO_REG];
	}

	bool read_byte(unsigned char& b) const
	{
		if (rx_data_avail())
		{
			b = pop_byte_from_fifo();
			return true;
		}
		else
		{
			b = 0x00;
			return false;
		}
	}

	bool write_byte(unsigned char b)
	{
		if (tx_room_avail())
		{
			push_byte_on_fifo(b);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool txfer_done() const
	{
		return (bar_[STATUS_REG] & DONE);
	}

	void reset_txfer_done() const
	{
		bar_[STATUS_REG] |= DONE;
	}

	void wait_for_done()
	{
		while (!txfer_done());
		reset_txfer_done();
	}

	void set_slave_address(unsigned char slaveaddr)
	{
		bar_[SLAVE_ADDR_REG] = slaveaddr;
	}

	void set_data_len(unsigned len)
	{
		bar_[DLEN_REG]=len;
	}

	void initiate_write()
	{
		bar_[CNTRL_REG] = (bar_[CNTRL_REG] & ~READ) | ST | CLEAR;
	}

	void initiate_read()
	{
		bar_[CNTRL_REG] |= (ST | CLEAR | READ);
	}

	unsigned char get_slave_address() const {
		return bar_[SLAVE_ADDR_REG];
	}


	void set_clk_divider() const {
		bar_[CLOCK_DIV_REG] = 0x05DC; // 100 kHz
	}

	void set_delay() const {
		bar_[DATA_DELAY_REG] = (0x030 << 16) + 0x030;
	}

	void set_clkt() const {
		bar_[CLKT] = 0x040;
	}

	volatile unsigned int* bar_;

	i2c(const i2c&); // no copy
	i2c& operator=(const i2c&); // no assign
};


#endif /* I2C_H_ */
