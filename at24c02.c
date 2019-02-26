/**
 * at24c02.h - at24c02 chip function
 * Copyright (c) 2018 Silgm. All right reserved.
*/
#include "at24c02.h"

void At24c02_create(At24c02 *dev, Pin sda, Pin scl, uint8_t devAddr)
{
	I2CDev_create(&(dev->i2cDev), sda, scl);
	dev->addr = devAddr;
}

void At24c02_init(At24c02 *dev)
{
	I2CDev_init(&(dev->i2cDev));
}

void At24c02_writeByte(At24c02 *dev, uint8_t wordAddr, uint8_t byte)
{
	I2CDev_start(&(dev->i2cDev));
	I2CDev_writeAddress(&(dev->i2cDev), dev->addr, MODE_WRITE);
	I2CDev_writeData(&(dev->i2cDev), wordAddr);
	I2CDev_writeData(&(dev->i2cDev), byte);
	I2CDev_stop(&(dev->i2cDev));
}

uint8_t At24c02_readByte(At24c02 *dev, uint8_t wordAddr)
{
	uint8_t dat;
	I2CDev_start(&(dev->i2cDev));
	I2CDev_writeAddress(&(dev->i2cDev), dev->addr, MODE_WRITE);
	I2CDev_writeData(&(dev->i2cDev), wordAddr);
	I2CDev_stop(&(dev->i2cDev));

	I2CDev_start(&(dev->i2cDev));
	I2CDev_writeAddress(&(dev->i2cDev), dev->addr, MODE_READ);
	dat = I2CDev_readData(&(dev->i2cDev), false);	//No Ack
	I2CDev_stop(&(dev->i2cDev));
	return dat;
}
