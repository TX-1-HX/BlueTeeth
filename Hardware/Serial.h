#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint8_t length);
uint8_t Serial_GetTxdata(void);
extern char string[100];
uint8_t Serial_GetFlag(void);

#endif
