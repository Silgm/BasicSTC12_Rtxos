/**
 * lcd1602.h - LCD1602 Module 
 * Copyright (c) 2018 Silgm. All right reserved.
*/

#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "intdef.h"
#include "delay.h"
#include "gpio.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


/**
 * LCD1602 Module:
 * rs -> GPIO
 * enable -> GPIO
 * d4~47 -> GPIO
 * RW -> GND //Never Forget
*/

typedef struct struct_lcd1602
{
	Pin rs;
	Pin enable;
	Pin d4, d5, d6, d7;
	uint8_t _displayfunction, _displaycontrol, _displaymode;
	uint8_t lastSetRow, lastSetCol;
}Lcd1602;

void Lcd1602_create(Lcd1602 *lcd, 
	Pin rs, 
	Pin enable, 
	Pin d4,
	Pin d5,
	Pin d6,
	Pin d7);

void Lcd1602_init(Lcd1602 *lcd);
void Lcd1602_setCursor(Lcd1602 *lcd, uint8_t col, uint8_t row);
void Lcd1602_print(Lcd1602 *lcd, const char *str);
void Lcd1602_send(Lcd1602 *lcd, char *buff, uint16_t buffSize);

void Lcd1602_clear(Lcd1602 *lcd);
void Lcd1602_clearLine(Lcd1602 *lcd, uint8_t line);
void Lcd1602_home(Lcd1602 *lcd);

/*After Use CreateChar Function, You must use setCursor to set mode to normal*/
void Lcd1602_createChar(Lcd1602 *lcd, uint8_t location, uint8_t pixmap[]); //location 0 ~ 7
void Lcd1602_showChar(Lcd1602 *lcd, uint8_t location);

void Lcd1602_noDisplay(Lcd1602 *lcd);
void Lcd1602_display(Lcd1602 *lcd);
void Lcd1602_noBlink(Lcd1602 *lcd);
void Lcd1602_blink(Lcd1602 *lcd);
void Lcd1602_noCursor(Lcd1602 *lcd);
void Lcd1602_cursor(Lcd1602 *lcd);
void Lcd1602_scrollDisplayLeft(Lcd1602 *lcd);
void Lcd1602_scrollDisplayRight(Lcd1602 *lcd);
void Lcd1602_leftToRight(Lcd1602 *lcd);
void Lcd1602_rightToLeft(Lcd1602 *lcd);
void Lcd1602_autoscroll(Lcd1602 *lcd);
void Lcd1602_noAutoscroll(Lcd1602 *lcd);

#endif

