#ifndef __MB_H
#define __MB_H

void MBRun();
void MBInit();
char MBReceive(char *received_frame);
void MBRespond(int sensor_value);
char check_crc(char *received_frame);
void USART1_mbFlag(void);
unsigned short int CRC16(char *nData, unsigned short int wLength);

#endif