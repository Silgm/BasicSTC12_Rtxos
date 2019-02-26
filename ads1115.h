#ifndef _ADS1115_H_
#define _ADS1115_H_

#include "binary.h"
#include "i2csoft.h"
#include "intdef.h"

#define ADS1115_ADDRESS_GND	B1001000
#define ADS1115_ADDRESS_VDD	B1001001
#define ADS1115_ADDRESS_SDA	B1001010
#define ADS1115_ADDRESS_SCL	B1001011

#define ADS1115_REG_ADDRESS_A B00
#define ADS1115_REG_ADDRESS_B B01
#define ADS1115_REG_ADDRESS_C B10
#define ADS1115_REG_ADDRESS_D B11


typedef struct structAds1115
{
	I2CDev 	i2cDev;
	uint8_t addr;
}Ads1115;

void Ads1115_create(Ads1115 *dev, Pin sda, Pin scl, uint8_t devAddr);
void Ads1115_init(Ads1115 *dev);

#endif
