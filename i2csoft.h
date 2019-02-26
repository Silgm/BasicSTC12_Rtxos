/**
 * i2csoft.h - Basic soft i2c function
 * Copyright (c) 2018 Silgm. All right reserved.
*/
#ifndef _I2CSOFT_H_
#define _I2CSOFT_H_

#include "gpio.h"
#include "intdef.h"

#define MODE_READ	0x01
#define MODE_WRITE	0x00

typedef struct structI2CDev
{
	Pin sda;
	Pin scl;
	bool started;
	uint16_t timeoutcnt;
}I2CDev;

void I2CDev_create(I2CDev *dev, Pin sdaPin, Pin sclPin);
void I2CDev_init(I2CDev *dev);
bool I2CDev_start(I2CDev *dev);
bool I2CDev_stop(I2CDev *dev);
bool I2CDev_writeByte(I2CDev *dev, uint8_t bt);
bool I2CDev_writeData(I2CDev *dev, uint8_t dat);
bool I2CDev_writeAddress(I2CDev *dev, uint8_t addr, uint8_t mode_rw);
	
uint8_t I2CDev_readData(I2CDev *dev, bool ack);
uint8_t I2CDev_readByte(I2CDev *dev, bool ack);

#endif
