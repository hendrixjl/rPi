#ifndef LSM303DLH_MAG_H_
#define LSM303DLH_MAG_H_

#include "i2c.h"
#include "mytypes.h"

class lsm303dlh_magnetometer
{
public:
    lsm303dlh_magnetometer(uint8_t mag_address, i2c& i2cbus)
    : mag_addr_(mag_address),
      i2cbus_(i2cbus) {}

    uint8_t mag_identify() {
        return i2cbus_.query(mag_addr_, WHO_AM_I_A);
    }

    uint32_t get_temp()
    {
        uint8_t buff[2];
        if (i2cbus_.query(mag_addr_, TEMP_OUT_H_M)==2)
        {
            return static_cast<uint32_t>(buff[0]);
        }
        return 0;
    }

    void enable()
    {
        enum {
            CONTINUOUS_CONVERSION_MODE = 0,
            SINGLE_CONVERSION_MODE = 1,
            SLEEP_MODE1 = 2,
            SLEEP_MODE2 = 3
        };
        uint8_t data = CONTINUOUS_CONVERSION_MODE;
        i2cbus_.command(mag_addr_, MR_REG_M, &data, 1);
    }

    void getMag(int16_t mag[3])
    {
        uint8_t block[6];
        i2cbus_.query(mag_addr_, OUT_X_H_M, block, sizeof(block));

        // DLM, DLHC: register address order is X,Z,Y with high bytes first
        mag[0] = (int16_t)(block[1] | block[0] << 8);
        mag[1] = (int16_t)(block[5] | block[4] << 8);
        mag[2] = (int16_t)(block[3] | block[2] << 8);

        // TODO: handle DLH properly here (switch two components?)
    }

private:
    enum registers_t {
		WHO_AM_I_A=0x0F,
        CRA_REG_M=0x00,
        CRB_REG_M,
        MR_REG_M,
        OUT_X_H_M,
        OUT_X_L_M,
        OUT_Z_H_M,
        OUT_Z_L_M,
        OUT_Y_H_M,
        OUT_Y_L_M,
        SR_REG_M,
        IRA_REG_M,
        IRB_REG_M,
        IRC_REG_M,
        TEMP_OUT_H_M=0x31,
        TEMP_OUT_L_M
    };
    uint8_t mag_addr_;
    i2c& i2cbus_;
};


#endif
