#ifndef __MB_H
#define __MB_H

int MBRequest(char slave, int address);
void MBInitSlave();
char MBReceive(char *frame);
void MBRespond(int sensor_value);
char check_crc(char *frame, int len);
void USART1_mbFlag(void);
unsigned short int CRC16(char *nData, unsigned short int wLength);

#endif