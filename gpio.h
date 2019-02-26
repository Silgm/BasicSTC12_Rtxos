/**
 * gpio.h - "Arduino like" GPIO Fuction
 * Copyright (c) 2018 Silgm. All right reserved.
*/

#ifndef _GPIO_H_
#define _GPIO_H_

#include "intdef.h"

#define HIGH	1
#define LOW		0

#define LSBFIRST	1
#define MSBFIRST	0


typedef enum enPin
{
	P0_0 = 0, P0_1 = 1, P0_2 = 2, P0_3 = 3, P0_4 = 4, P0_5 = 5, P0_6 = 6, P0_7 = 7,
	P1_0 = 8, P1_1 = 9, P1_2 = 10, P1_3 = 11, P1_4 = 12, P1_5 = 13, P1_6 = 14, P1_7 = 15,
	P2_0 = 16, P2_1 = 17, P2_2 = 18, P2_3 = 19, P2_4 = 20, P2_5 = 21, P2_6 = 22, P2_7 = 23,
}Pin;

typedef enum enPort
{
	PORT_0 = 0, PORT_1 = 1, PORT_2 = 2
}Port;

typedef enum enPinMode
{
	//The default mode is Mode_WeakUp, if we do not use "pinMode" Function to set the mode of gpio.
	
	Mode_WeakUp = 0,	//Standard 8051 IO Mode ---- Weak pull up ---> recommended to be used in input-mode
	Mode_PPOut = 1,		//Push-Pull output ---> recommended to be used in output-mode
	Mode_HighImpedanceInput = 2,//High Impedance input
	Mode_OpenDrainOuput = 3 //Open-Drain output
	
}PinMode;

void pinMode(Pin pin, PinMode mode);
void digitalWrite(Pin pin, uint8_t val);
uint8_t digitalRead(Pin pin);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);

#endif
