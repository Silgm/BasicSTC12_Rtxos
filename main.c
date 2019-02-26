#include "rtx51tny.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stc12c5a60s2.h"
#include "delay.h"
#include "gpio.h"
#include "lcd1602.h"
#include "binary.h"


#include "hardware_serial2.h"

/*Define UART parity mode*/

#define FOSC 11059200L      //System frequency
#define BAUD 115200         //UART baudrate

char buff[32] = "";

void Startup_Task() _task_ 0
{
	os_create_task(1); //task1  
	os_delete_task(0); //delet task0  	
}

void Lcd_Task() _task_ 1
{
	int i = 0;
	Lcd1602 lcd;
	Lcd1602_create(&lcd, P2_7, P2_6, P2_5, P2_4, P2_3, P2_2);
	Lcd1602_init(&lcd);
	for(;;)
	{
		Lcd1602_setCursor(&lcd, 0, 0);
		Lcd1602_print(&lcd, "Hello, World!");
		
		Lcd1602_setCursor(&lcd, 0, 1);
		sprintf(buff, "%d    ", i++);
		Lcd1602_print(&lcd, buff);
		delay_ms(5000);
	}
}

/*
void Startup_Task() _task_ 0
{
	Serial2_init(FOSC, BAUD);
		
	os_create_task(1); //task1  
	os_create_task(2); //task2
	os_delete_task(0); //delet task0  	
}

void Serial_Task() _task_ 1
{
	for (;;)
	{
		Serial2_sendString("Hello, World!\n");
		delay_ms(1000);
	}
}

void Lcd_Task() _task_ 2
{
	uint16_t readSize;
	int i = 0;
	Lcd1602 lcd;
	Lcd1602_create(&lcd, P2_7, P2_6, P2_5, P2_4, P2_3, P2_2);
	Lcd1602_init(&lcd);
	for (;;)
	{
		Lcd1602_setCursor(&lcd, 0, 0);
		sprintf(buff, "%d  ", i++);
		Lcd1602_print(&lcd, buff);
		
//		readSize = Serial2_recv(buff, 32);
		
		
		for(i = 0;Serial2_avaliable() > 0; ++i)
		{
			buff[i] = Serial2_recvByte();
		}
		buff[i] = '\0';
		
		readSize = Serial2_recvWithBlock(buff, 32);
		Lcd1602_setCursor(&lcd, 0, 1);
		Lcd1602_send(&lcd, buff, readSize);
	}
}
*/


