#ifndef _AD9850_H_
#define _AD9850_H_

#include "gpio.h"

#define MAX_FREQ_DEFAULT (125000000)
#define MAX_PHASE	32
typedef struct struct_ad9850
{
	Pin wclk;
	Pin fq;
	Pin rst;
	Pin d7;
	
	uint32_t maxFreq;
}Ad9850;

void Ad9850_create(Ad9850 *dev, Pin wclk, Pin fq, Pin rst, Pin d7, uint32_t maxFreq);
void Ad9850_init(Ad9850 *dev);
void Ad9850_write(Ad9850 *dev, uint32_t freq, uint8_t phasePowerCon);
void Ad9850_powerdown(Ad9850 *dev);
void Ad9850_output(Ad9850 *dev, uint32_t hz, uint8_t phase);

#endif
