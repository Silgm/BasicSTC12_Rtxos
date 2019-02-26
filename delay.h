/**
 * delay.h - Basic and inaccuracy delay function
 * Copyright (c) 2018 Silgm. All right reserved.
*/
#ifndef _DELAY_H_
#define _DELAY_H_

#include "intdef.h"

#define DELAY_FACTOR	110
void delay_ms(uint16_t ms);
void delay_us(uint16_t us);
#endif

