#include "ads1115.h"

void Ads1115_create(Ads1115 *dev, Pin sda, Pin scl, uint8_t devAddr)
{
	I2CDev_create(&(dev->i2cDev)
	, sda, scl);
	dev->addr = devAddr;
}

void Ads1115_init(Ads1115 *dev)
{
	I2CDev_init(&(dev->i2cDev));
}

static uint16_t s_Ads1115_read(Ads1115 *dev, uint8_t regAddr)
{
	uint16_t dat = 0;
	
	I2CDev_start(&(dev->i2cDev));
	I2CDev_writeAddress(&(dev->i2cDev), dev->addr, MODE_WRITE);
	I2CDev_writeData(&(dev->i2cDev), regAddr);
	I2CDev_stop(&(dev->i2cDev));
	
	I2CDev_start(&(dev->i2cDev));
	I2CDev_writeAddress(&(dev->i2cDev), dev->addr, MODE_READ);
	dat = ((uint16_t)I2CDev_readData(&(dev->i2cDev), true)) << 8;
	dat |= (uint16_t)I2CDev_readData(&(dev->i2cDev), true);
	I2CDev_stop(&(dev->i2cDev));
	
	return dat;
}
