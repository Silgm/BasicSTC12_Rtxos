#include "ad9850.h"
#include "delay.h"
#include "binary.h"

#include <limits.h>

//phasePowerCon
//phase[7:3] Power[2] Con[1:0]

void Ad9850_create(Ad9850 *dev, Pin wclk, Pin fq, Pin rst, Pin d7, uint32_t maxFreq)
{
	dev->wclk = wclk;
	dev->fq = fq;
	dev->rst = rst;
	dev->d7 = d7;
	
	dev->maxFreq = maxFreq;
}

static void Ad9850_send(Ad9850 *dev, uint32_t freq, uint8_t phasePowerCon)
{
	uint8_t i;
	for (i = 0; i < 32; ++i)
	{
		if (freq & 1)
		{
			digitalWrite(dev->d7, HIGH);
		}
		else
		{
			digitalWrite(dev->d7, LOW);
		}
		freq >>= 1;
		digitalWrite(dev->wclk, LOW);
		digitalWrite(dev->wclk, HIGH);
	}
	
	for (i = 0; i < 8; ++i)
	{
		if (phasePowerCon & 1)
		{
			digitalWrite(dev->d7, HIGH);
		}
		else
		{
			digitalWrite(dev->d7, LOW);
		}
		freq >>= 1;
		digitalWrite(dev->wclk, LOW);
		digitalWrite(dev->wclk, HIGH);
	}
	digitalWrite(dev->wclk, LOW);
}



void Ad9850_init(Ad9850 *dev)
{
	pinMode(dev->wclk, Mode_WeakUp);
	pinMode(dev->fq, Mode_WeakUp);
	pinMode(dev->rst, Mode_WeakUp);
	pinMode(dev->d7, Mode_WeakUp);
	
	
	digitalWrite(dev->rst, HIGH);
	delay_ms(10);
	
	digitalWrite(dev->wclk, LOW);
	digitalWrite(dev->fq, LOW);
	digitalWrite(dev->rst, LOW);
	digitalWrite(dev->d7, LOW);
	
	digitalWrite(dev->wclk, HIGH);
	digitalWrite(dev->wclk, LOW);
	
	//fq pulse
	digitalWrite(dev->fq, HIGH);
	digitalWrite(dev->fq, LOW);	
	
	Ad9850_send(dev, 0, 0);
	
	//fq pulse
	digitalWrite(dev->fq, HIGH);
	digitalWrite(dev->fq, LOW);	
}

void Ad9850_write(Ad9850 *dev, uint32_t freq, uint8_t phasePowerCon)
{
	Ad9850_send(dev, freq, phasePowerCon);
	digitalWrite(dev->fq, HIGH);
	digitalWrite(dev->fq, LOW);	
}

void Ad9850_powerdown(Ad9850 *dev)
{
	Ad9850_write(dev, 0, B00000100);
}

void Ad9850_output(Ad9850 *dev, uint32_t hz, uint8_t phase)
{
	float rat = ((float)(hz))/(dev->maxFreq);
	uint32_t freqDat = (uint32_t) (rat*(ULONG_MAX) + 0.5f);
	uint32_t phasePowerCon = (phase << 3);
	Ad9850_write(dev, freqDat, phasePowerCon);
}


