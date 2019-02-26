/**
 * lcd1602.c - LCD1602 Module 
 * Copyright (c) 2018 Silgm. All right reserved.
*/

#include "lcd1602.h"

#define MODE_DATA	1
#define MODE_CMD	0



static void s_Lcd1602_pluseEnable(const Lcd1602 *lcd)
{
	digitalWrite(lcd->enable, LOW);
	digitalWrite(lcd->enable, HIGH);
	digitalWrite(lcd->enable, LOW);
	//delay_us(1);
}

static void s_Lcd1602_Write(const Lcd1602 *lcd, const uint8_t value, const uint8_t mode)
{
	digitalWrite(lcd->rs, mode);

	//write4bits(value>>4);
	digitalWrite(lcd->d4, ((value >> 4) >> 0) & 0x01);
	digitalWrite(lcd->d5, ((value >> 4) >> 1) & 0x01);
	digitalWrite(lcd->d6, ((value >> 4) >> 2) & 0x01);
	digitalWrite(lcd->d7, ((value >> 4) >> 3) & 0x01);
	s_Lcd1602_pluseEnable(lcd);

	//write4bits(value);
	digitalWrite(lcd->d4, (value >> 0) & 0x01);
	digitalWrite(lcd->d5, (value >> 1) & 0x01);
	digitalWrite(lcd->d6, (value >> 2) & 0x01);
	digitalWrite(lcd->d7, (value >> 3) & 0x01);

	s_Lcd1602_pluseEnable(lcd);
}


void Lcd1602_create(Lcd1602 *lcd, 
	Pin rs, 
	Pin enable, 
	Pin d4,
	Pin d5,
	Pin d6,
	Pin d7)
{
	lcd->rs = rs;
	lcd->enable = enable;
	lcd->d4 = d4;
	lcd->d5 = d5;
	lcd->d6 = d6;
	lcd->d7 = d7;
	
	lcd->lastSetRow = 0;
	lcd->lastSetCol = 0;
}

void Lcd1602_init(Lcd1602 *lcd)
{
	//IO Set
	pinMode(lcd->rs, Mode_WeakUp);
	pinMode(lcd->enable, Mode_WeakUp);
	pinMode(lcd->d4, Mode_WeakUp);
	pinMode(lcd->d5, Mode_WeakUp);
	pinMode(lcd->d6, Mode_WeakUp);
	pinMode(lcd->d7, Mode_WeakUp);
	
	//Lcd Set
	lcd->_displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;				//
	s_Lcd1602_Write(lcd, LCD_FUNCTIONSET | lcd->_displayfunction, MODE_CMD);	//
	
	lcd->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	Lcd1602_display(lcd);
	Lcd1602_clear(lcd);
	lcd->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	s_Lcd1602_Write(lcd, LCD_ENTRYMODESET | lcd->_displaymode, MODE_CMD);
}

void Lcd1602_setCursor(Lcd1602 *lcd, uint8_t col, uint8_t row)
{
	if (row)
		s_Lcd1602_Write(lcd, LCD_SETDDRAMADDR | (col + 0x40), MODE_CMD);	
	else
		s_Lcd1602_Write(lcd, LCD_SETDDRAMADDR | (col), MODE_CMD);	
	lcd->lastSetRow = row;
	lcd->lastSetCol = col;
}

void Lcd1602_print(Lcd1602 *lcd, const char *str)
{
	for (; *str != '\0'; ++str)
		s_Lcd1602_Write(lcd, *str, MODE_DATA);
}

void Lcd1602_send(Lcd1602 *lcd, char *buff, uint16_t buffSize)
{
	uint16_t i;
	for (i = 0; i < buffSize; ++i)
	{
		s_Lcd1602_Write(lcd, buff[i], MODE_DATA);
	}
}

void Lcd1602_clear(Lcd1602 *lcd)
{
	s_Lcd1602_Write(lcd, LCD_CLEARDISPLAY, MODE_CMD);  // clear display, set cursor position to zero
	delay_us(2000);  // this command takes a long time!
}

void Lcd1602_clearLine(Lcd1602 *lcd, uint8_t line)
{
	uint8_t row = lcd->lastSetRow;
	uint8_t col = lcd->lastSetCol;
	if (line == 0)
	{
		Lcd1602_setCursor(lcd, 0, 0);
		Lcd1602_print(lcd, "                ");
	}
	else
	{
		Lcd1602_setCursor(lcd, 0, 1);
		Lcd1602_print(lcd, "                ");
	}
	Lcd1602_setCursor(lcd, row, col);
}

void Lcd1602_home(Lcd1602 *lcd)
{
	s_Lcd1602_Write(lcd, LCD_RETURNHOME, MODE_CMD);  // set cursor position to zero
	delay_us(2000);  // this command takes a long time!
}

void Lcd1602_createChar(Lcd1602 *lcd, uint8_t location, uint8_t pixmap[])
{
	uint8_t i = 0;
	location &= 0x7; // we only have 8 locations 0-7
	s_Lcd1602_Write(lcd, LCD_SETCGRAMADDR | (location << 3), MODE_CMD);
	for (; i<8; i++) 
	{
		s_Lcd1602_Write(lcd, pixmap[i], MODE_DATA);
	}
}

void Lcd1602_showChar(Lcd1602 *lcd, uint8_t location)
{
	s_Lcd1602_Write(lcd, location, MODE_DATA);
}

void Lcd1602_noDisplay(Lcd1602 *lcd)
{
	lcd->_displaycontrol &= ~LCD_DISPLAYON;
  	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}
void Lcd1602_display(Lcd1602 *lcd)
{
	lcd->_displaycontrol |= LCD_DISPLAYON;
  	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}
void Lcd1602_noBlink(Lcd1602 *lcd)
{
	lcd->_displaycontrol &= ~LCD_BLINKON;
  	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}
void Lcd1602_blink(Lcd1602 *lcd)
{
	lcd->_displaycontrol |= LCD_BLINKON;
  	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}
void Lcd1602_noCursor(Lcd1602 *lcd)
{
	lcd->_displaycontrol &= ~LCD_CURSORON;
	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}
void Lcd1602_cursor(Lcd1602 *lcd)
{
	lcd->_displaycontrol |= LCD_CURSORON;
	s_Lcd1602_Write(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol, MODE_CMD);
}

void Lcd1602_scrollDisplayLeft(Lcd1602 *lcd)
{
	s_Lcd1602_Write(lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT, MODE_CMD);
}
void Lcd1602_scrollDisplayRight(Lcd1602 *lcd)
{
	s_Lcd1602_Write(lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT, MODE_CMD);
}
void Lcd1602_leftToRight(Lcd1602 *lcd)
{
	lcd->_displaymode |= LCD_ENTRYLEFT;
	s_Lcd1602_Write(lcd, LCD_ENTRYMODESET | lcd->_displaymode, MODE_CMD);
}
void Lcd1602_rightToLeft(Lcd1602 *lcd)
{
	lcd->_displaymode &= ~LCD_ENTRYLEFT;
	s_Lcd1602_Write(lcd, LCD_ENTRYMODESET | lcd->_displaymode, MODE_CMD);
}
void Lcd1602_autoscroll(Lcd1602 *lcd)
{
	lcd->_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	s_Lcd1602_Write(lcd, LCD_ENTRYMODESET | lcd->_displaymode, MODE_CMD);
}
void Lcd1602_noAutoscroll(Lcd1602 *lcd)
{
	lcd->_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	s_Lcd1602_Write(lcd, LCD_ENTRYMODESET | lcd->_displaymode, MODE_CMD);
}

