#include "hardware_serial2.h"
#include "stc12c5a60s2.h"

bit busy;
static uint16_t _avaliable = 0;

static int32_t fosc;
static int32_t baud;

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

char recvBuff[REC_BUFF_SIZE] = {0};

typedef struct struct_RecvQueue
{
	int head;
	int tail;
}RecvQueue;

static RecvQueue rq;

static void QueInit()
{
	rq.head = 0;
	rq.tail = 0;
}

static void QueIn(char dat)
{
	recvBuff[(rq.tail)] = dat;
	++(rq.tail);
	rq.tail %= REC_BUFF_SIZE;
}

static char QueOut()
{
	char dat = recvBuff[(rq.head)];
	++(rq.head);
	rq.head %= REC_BUFF_SIZE;
	return dat;
}

void Serial2_init(int32_t in_fosc, int32_t in_baud)
{
	fosc = in_fosc;
	baud = in_baud;
	QueInit();
	
#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;           //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;           //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;           //9-bit variable UART, parity bit initial to 0
#endif

    BRT = -(fosc/32/baud);  //Set auto-reload vaule of baudrate generator
    AUXR = 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch
}

static void sendByte(char dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#endif
    }
    busy = 1;
    S2BUF = ACC;            //Send data to UART2 buffer
}

void Serial2_sendByte(char byte)
{
	sendByte(byte);
}

void Serial2_sendString(char *str)
{
	while(*str)
	{
		sendByte(*str++);
	}
}

void Serial2_send(char *buff, uint16_t buffSize)
{
	uint16_t i = 0;
	for (; i < buffSize; ++i)
	{
		sendByte(buff[i]);
	}
}

char Serial2_recvByte()
{
	char dat = 0;
	if (_avaliable > 0)
	{
		--_avaliable;
		dat = QueOut();
	}
	return dat;
}


uint16_t Serial2_avaliable()
{
	return _avaliable;
}

uint16_t Serial2_recv(char *buff, uint16_t buffSize)
{
	uint16_t cnt = 0;
	for (; Serial2_avaliable() > 0 && cnt < buffSize; ++cnt)
	{
		buff[cnt] = Serial2_recvByte();
	}
	return cnt;
}

uint16_t Serial2_recvWithBlock(char *buff, uint16_t buffSize)
{
	uint16_t cnt = 0;
	while(Serial2_avaliable() == 0);
	for (;Serial2_avaliable() > 0 && cnt < buffSize; ++cnt)
	{
		buff[cnt] = Serial2_recvByte();
	}
	return cnt;
}

char Serial2_recvByteWithBlock()
{
	while (Serial2_avaliable() == 0);
	return Serial2_recvByte();
}

uint16_t Serial2_recvUntilN(char *buff, uint16_t buffSize, uint16_t n)
{
	uint16_t cnt = 0;
	for (;cnt < n && cnt < buffSize; ++cnt)
	{
		buff[cnt] = Serial2_recvByteWithBlock();
	}
	return cnt;
}

static void Callback_Receive()
{
	char byte = S2BUF;
	QueIn(byte);
	++_avaliable;
    //P2 = (S2CON & S2RB8);//P2.2 show parity bit
}

void Interrupt_Serial2_Receive_Data() interrupt 8 //using 1
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
		
		//Receive CallBack
		Callback_Receive();
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}

