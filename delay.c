/**
 * delay.c - Basic and inaccuracy delay function
 * Copyright (c) 2018 Silgm. All right reserved.
*/
#include "delay.h"

void delay_ms(uint16_t ms)
{
	unsigned char i = 0;
	for (; ms; --ms)
		for (i = 0; i < DELAY_FACTOR; ++i);
}

void delay_us(uint16_t us)
{
	for (; us; --us);
}