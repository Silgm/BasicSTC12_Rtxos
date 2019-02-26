#ifndef _HARDWARE_SERIAL2_
#define _HARDWARE_SERIAL2_

#include "intrins.h"
#include "intdef.h"

/* 
 * P1.2 = RXD2  <--------- TXD
 * P1.3 = TXD2  ---------> RXD
*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity
//Modify your ParityBit Here
#define PARITYBIT NONE_PARITY   //Testing even parity
#define REC_BUFF_SIZE	256

void Serial2_init(int32_t in_fosc, int32_t in_baud);

void Serial2_send(char *buff, uint16_t buffSize);

void Serial2_sendString(char *str);

void Serial2_sendByte(char byte);

uint16_t Serial2_avaliable();

char Serial2_recvByte();

uint16_t Serial2_recv(char *buff, uint16_t buffSize);

uint16_t Serial2_recvWithBlock(char *buff, uint16_t buffSize);

char Serial2_recvByteWithBlock();

uint16_t Serial2_recvUntilN(char *buff, uint16_t buffSize, uint16_t n);

#endif
