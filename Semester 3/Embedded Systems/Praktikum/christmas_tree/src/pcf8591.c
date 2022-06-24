#include "platform.h"
#include "stdbool.h"

#include "pcf8591.h"
#include "gpio.h"

#define IOF_I2C_MASK (MASK(IOF_I2C_SCL) | MASK(IOF_I2C_SDA))

void pcf8591_init()
{
    GPIO_REG(GPIO_IOF_SEL) &= ~IOF_I2C_MASK;
    GPIO_REG(GPIO_IOF_EN)  |=  IOF_I2C_MASK;

    I2C_REG(I2C0_CONTROL)       &= ~MASK(I2C_CTRL_EN);
    I2C_REG(I2C0_PRESCALE_HIGH)  = 0x00;
    I2C_REG(I2C0_PRESCALE_LOW)   = 0x1F;
    I2C_REG(I2C0_CONTROL)       |=  MASK(I2C_CTRL_EN);
}

void i2c_transmit(uint32_t transmit, uint32_t command)
{
    I2C_REG(I2C0_TRANSMIT) = transmit;
    I2C_REG(I2C0_COMMAND)  = command;
    
    while ((I2C_REG(I2C0_STATUS) & MASK(I2C_STAT_TIP)) > 0U) {
    }
}

uint8_t pcf8591_read(const pcf8591_t *dev, const pcf8591_channel_t channel)
{
    // Initialize transmission
    i2c_transmit(0,             MASK(I2C_CMD_STA));
    // Switch to write mode
    i2c_transmit(dev->addr | 0, MASK(I2C_CMD_WR));
    // Write control byte
    i2c_transmit(channel,       MASK(I2C_CMD_WR));
    // Switch to read mode
    i2c_transmit(dev->addr | 1, MASK(I2C_CMD_STA) | MASK(I2C_CMD_WR));
    // Dummy read
    i2c_transmit(0,             MASK(I2C_CMD_RD));
    // Actual read
    i2c_transmit(0,             MASK(I2C_CMD_RD));
    uint32_t result = I2C_REG(I2C0_RECEIVE);
    // Finish transmission
    i2c_transmit(0,             MASK(I2C_CMD_ACK));

    return result;
}
