/**
 * at24c02.h - at24c02 chip function
 * Copyright (c) 2018 Silgm. All right reserved.
*/

#ifndef _AT24C02_H_
#define _AT24C02_H_
#include "i2csoft.h"
#include "binary.h"

#define AT24C02_ADDRESS_A2A1A0_000 B01010000
#define AT24C02_ADDRESS_A2A1A0_001 B01010001
#define AT24C02_ADDRESS_A2A1A0_010 B01010010
#define AT24C02_ADDRESS_A2A1A0_011 B01010011
#define AT24C02_ADDRESS_A2A1A0_100 B01010100
#define AT24C02_ADDRESS_A2A1A0_101 B01010101
#define AT24C02_ADDRESS_A2A1A0_110 B01010110
#define AT24C02_ADDRESS_A2A1A0_111 B01010111

typedef struct structAt24c02
{
	I2CDev i2cDev;
	uint8_t addr;
	
}At24c02;

void At24c02_create(At24c02 *dev, Pin sda, Pin scl, uint8_t devAddr);
void At24c02_init(At24c02 *dev);
void At24c02_writeByte(At24c02 *dev, uint8_t wordAddr, uint8_t byte);
uint8_t At24c02_readByte(At24c02 *dev, uint8_t wordAddr);

#endif
