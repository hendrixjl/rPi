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

i2c& i2c::setup(uint16_t bus) 
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

uint32_t i2c::get_status() const
{
    return bar_[STATUS_REG];
}

uint32_t i2c::get_control() const
{
    return bar_[CNTRL_REG];
}

size_t i2c::command(uint8_t slaveaddr,
                    uint8_t cmd,
                    const uint8_t* data_addr=0,
                    size_t data_size=0)
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

uint8_t i2c::query(uint8_t slaveaddr,
                         uint8_t slave_register)
{
    command(slaveaddr, slave_register);
    initiate_read();
    unsigned char b;
    while (!read_byte(b)); // loop until success
    clear_fifo();
    // TODO error conditions?
    return b;
}


size_t i2c::query(uint8_t slaveaddr,
                  uint8_t slave_register,
                  uint8_t* buffer,
                  size_t buffer_size)
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

uint32_t i2c::get_bar() const
{
    return (unsigned int)bar_;
}


explicit i2c::i2c(volatile uint32_t *bar)
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

void i2c::push_byte_on_fifo(uint8_t byte)
{
    bar_[FIFO_REG] = byte;
}

uint8_t i2c::pop_byte_from_fifo() const
{
    return bar_[FIFO_REG];
}

bool read_byte(uint8_t& byte) const
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

bool i2c::write_byte(uint8_t byte)
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

bool i2c::txfer_done() const
{
    return (bar_[STATUS_REG] & DONE);
}

void i2c::reset_txfer_done() const
{
    bar_[STATUS_REG] |= DONE;
}

void i2c::wait_for_done()
{
    while (!txfer_done());
    reset_txfer_done();
}

void i2c::set_slave_address(uint8_t slaveaddr)
{
    bar_[SLAVE_ADDR_REG] = slaveaddr;
}

void i2c::set_data_len(size_t len)
{
    bar_[DLEN_REG]=len;
}

void i2c::initiate_write()
{
    bar_[CNTRL_REG] = (bar_[CNTRL_REG] & ~READ) | ST | CLEAR;
}

void i2c::initiate_read()
{
    bar_[CNTRL_REG] |= (ST | CLEAR | READ);
}

unsigned char i2c::get_slave_address() const 
{
    return bar_[SLAVE_ADDR_REG];
}

void i2c::set_clk_divider(uint16_t div) const 
{
    bar_[CLOCK_DIV_REG] = div;
}

void i2c::set_delay(uint16_t delay) const 
{
    bar_[DATA_DELAY_REG] = delay;
}

void i2c::set_clkt(uint8_t clkt) const 
{
    bar_[CLKT] = clkt;
}

i2c& i2c::setup0()
{
    static i2c i2c0(BSC0_BAR);
    i2c0.init();
    return i2c0;
}

i2c& i2c::setup1() 
{
    static i2c i2c1(BSC1_BAR);
    i2c1.init();
    return i2c1;
}

i2c& i2c::setup2() 
{
    static i2c i2c2(BSC2_BAR); // Not available on RPi
    i2c2.init(); // Not available on RPi
    return i2c2;
}

