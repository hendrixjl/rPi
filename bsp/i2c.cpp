#include "i2c.h"

#include "bar.h"

// BSC registers for the raspberry pi
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

/**
* For interpreting/setting the control bits
* of the device
*/
enum control_bits_t {
    I2CEN = 1 << 15,
    INTR = 1 << 10,
    INTT = 1 << 9,
    INTD = 1 << 8,
    ST = 1 << 7,
    CLEAR = 1 << 4,
    READ = 1
};

/**
* For interpreting the status bits on the device
*/
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

i2c& i2c::setup(unsigned short bus) 
{
    switch (bus)
    {
    case 0: return setup0();
    case 1: return setup1();
    case 2: return setup2();
    default: return setup0();
    }
}

void i2c::enable()
{
    bar_[CNTRL_REG] |= I2CEN;
}

void i2c::disable()
{
    bar_[CNTRL_REG] &= ~I2CEN;
}

unsigned int i2c::get_status() const
{
    return bar_[STATUS_REG];
}

unsigned int i2c::get_control() const
{
    return bar_[CNTRL_REG];
}

unsigned i2c::command(unsigned char slaveaddr,
                      unsigned char cmd,
                      const unsigned char* data_addr=0,
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
        if (write_byte(*data_addr))
        {
            data_addr++;
            data_size--;
            bytes_sent++;
        }
        // TODO check for error conditions
    }
    wait_for_done();
    clear_fifo();
    return bytes_sent;
}

unsigned char i2c::query(unsigned char slaveaddr,
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


unsigned i2c::query(unsigned char slaveaddr,
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

unsigned int i2c::get_bar() const
{
    return (unsigned int)bar_;
}


explicit i2c::i2c(volatile unsigned int *bar)
: bar_ (bar)
{
    init();
}

void i2c::init()
{
    bar_[CNTRL_REG] = 0;
    set_clk_divider();
    set_delay();
    set_clkt();
    bar_[SLAVE_ADDR_REG] = 0;
    bar_[DLEN_REG] = 0;
}

void i2c::clear_fifo() 
{
    bar_[CNTRL_REG] |= CLEAR;
}

void i2c::clear_done() 
{
    bar_[STATUS_REG] |= DONE;
}

bool i2c::rx_data_avail() const
{
    return bar_[STATUS_REG] & RXD;
}

bool i2c::tx_room_avail() const
{
    return bar_[STATUS_REG] & TXD;
}

void i2c::push_byte_on_fifo(unsigned char byte)
{
    bar_[FIFO_REG] = byte;
}

unsigned char i2c::pop_byte_from_fifo() const
{
    return bar_[FIFO_REG];
}

bool read_byte(unsigned char& byte) const
{
    if (rx_data_avail())
    {
        byte = pop_byte_from_fifo();
        return true;
    }
    else
    {
        byte = 0x00;
        return false;
    }
}

bool i2c::write_byte(unsigned char byte)
{
    if (tx_room_avail())
    {
        push_byte_on_fifo(byte);
        return true;
    }
    else
    {
        return false;
    }
}

/**
* What is the state of an i2c transfer
* @return true if the DONE bit is set
*/
bool txfer_done() const
{
return (bar_[STATUS_REG] & DONE);
}

/**
* Reset the transfer bit on the i2c bus device
*/
void reset_txfer_done() const
{
bar_[STATUS_REG] |= DONE;
}

/**
* Busy wait for the done bit to be set for the
* i2c bus device
*/
void wait_for_done()
{
while (!txfer_done());
reset_txfer_done();
}

/**
* Set the slave address for the i2c bus device
* @param slaveaddr
*/
void set_slave_address(unsigned char slaveaddr)
{
bar_[SLAVE_ADDR_REG] = slaveaddr;
}

/**
* Set the data length of an upcoming
* i2c transfer
* @param len
*/
void set_data_len(unsigned len)
{
bar_[DLEN_REG]=len;
}

/**
* Initiate a write to an i2c slave device.
*/
void initiate_write()
{
bar_[CNTRL_REG] = (bar_[CNTRL_REG] & ~READ) | ST | CLEAR;
}

/**
* Initiate a read from an i2c slave device
*/
void initiate_read()
{
bar_[CNTRL_REG] |= (ST | CLEAR | READ);
}

/**
* Return the slave address currently
* set for this i2c bus device
* @return the slave address
*/
unsigned char get_slave_address() const {
return bar_[SLAVE_ADDR_REG];
}

/**
* Set the clock divider for the i2c bus device clock
* @param div (defaults to 0x5DC [100 kHz])
*/
void set_clk_divider(unsigned short div=0x5DC) const {
bar_[CLOCK_DIV_REG] = div;
}

/**
* Set the delay for the i2c bus device.
* @param delay (defaults to 0x0000 0030 0000 0030
*/
void set_delay(unsigned int delay=(0x030 << 16) + 0x030) const {
bar_[DATA_DELAY_REG] = delay;
}

/**
* Set clkt for the i2c bus device.
* @param clkt (defauts to 0x040)
*/
void set_clkt(unsigned char clkt=0x040) const {
bar_[CLKT] = clkt;
}

volatile unsigned int* bar_;

i2c(const i2c&); // no copy
i2c& operator=(const i2c&); // no assign

/**
* Setup the i2c bus 0 and initialize it to disabled.
*/
static i2c& setup0() {
static i2c i2c0(BSC0_BAR);
i2c0.init();
return i2c0;
}
/**
* Setup the i2c bus 1 and initialize it to disabled.
*/
static i2c& setup1() {
static i2c i2c1(BSC1_BAR);
i2c1.init();
return i2c1;
}
/**
* Setup the i2c bus 2 and initialize it to disabled.
*/
static i2c& setup2() {
static i2c i2c2(BSC2_BAR); // Not available on RPi
i2c2.init(); // Not available on RPi
return i2c2;
}

};
