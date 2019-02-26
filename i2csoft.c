/**
 * i2csoft.c - Basic soft i2c function
 * Copyright (c) 2018 Silgm. All right reserved.
*/

#include "i2csoft.h"
#include "delay.h"

static void s_reset_timeoutcnt(I2CDev *dev)
{
	dev->timeoutcnt = 0;
}
static bool s_wait_for_timeout(I2CDev *dev)
{
	++(dev->timeoutcnt);
	if (dev->timeoutcnt == 65535)
		return true;
	else 
		return false;
}

void I2CDev_create(I2CDev *dev, Pin sdaPin, Pin sclPin)
{
	dev->sda = sdaPin;
	dev->scl = sclPin;
	dev->started = false;
}

void I2CDev_init(I2CDev *dev)
{
	digitalWrite(dev->sda, HIGH);
	digitalWrite(dev->scl, HIGH);
}

bool I2CDev_start(I2CDev *dev)
{
	
	if (dev->started) // if started, do a restart condition
	{
		digitalWrite(dev->sda, HIGH);
		digitalWrite(dev->scl, HIGH);
		
		s_reset_timeoutcnt(dev);
		while(digitalRead(dev->scl) == LOW)
		{
			// Clock stretching
			// You should add timeout to this loop
			if (s_wait_for_timeout(dev))
				break;
		}
		
		if (digitalRead(dev->sda) == LOW)
		{
			return false;
		}
	}
	
	// SCL is high, set SDA from 1 to 0.
	digitalWrite(dev->sda, LOW);
	digitalWrite(dev->scl, LOW);
	dev->started = true;
	
	return true;
}

bool I2CDev_stop(I2CDev *dev)
{
	// set SDA to 0
	digitalWrite(dev->sda, LOW);
	digitalWrite(dev->scl, HIGH);
	
	// Clock stretching
	s_reset_timeoutcnt(dev);
	while(digitalRead(dev->scl) == LOW)
	{
		// Clock stretching
		// You should add timeout to this loop
		if (s_wait_for_timeout(dev))
			break;
	}
	
	// Stop bit setup time, minimum 4us
	// SCL is high, set SDA from 0 to 1
	digitalWrite(dev->sda, HIGH);

	if (digitalRead(dev->sda) == LOW) {
		return false;
	}
	
	dev->started = false;
	return true;
}

bool I2CDev_writeByte(I2CDev *dev, uint8_t bt)
{
	uint8_t ack;
	shiftOut(dev->sda, dev->scl, MSBFIRST, bt);
	
	digitalWrite(dev->sda, HIGH);
	digitalWrite(dev->scl, HIGH);
	ack = digitalRead(dev->sda);
	digitalWrite(dev->scl, LOW);
	
	if (ack == LOW)
		return true;
	else 
		return false;
}

bool I2CDev_writeData(I2CDev *dev, uint8_t dat)
{
	return I2CDev_writeByte(dev, dat);
}

bool I2CDev_writeAddress(I2CDev *dev, uint8_t addr, uint8_t mode_rw)
{
	return I2CDev_writeByte(dev, (addr<<1) | mode_rw);
}

uint8_t I2CDev_readByte(I2CDev *dev, bool ack)
{
	uint8_t dat = shiftIn(dev->sda, dev->scl, MSBFIRST);
	
	//Send Ack
	if (ack == true)
	{
		digitalWrite(dev->sda, ack);
		digitalWrite(dev->scl, HIGH);
		digitalWrite(dev->scl, LOW);	
	}
	
	return dat;
}

uint8_t I2CDev_readData(I2CDev *dev, bool ack)
{
	return I2CDev_readByte(dev, ack);
}







