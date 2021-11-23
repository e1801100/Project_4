#ifndef __MB_H
#define __MB_H

int MBRequest(char slave, int address);
void MBInitSlave(UART_HandleTypeDef *huart);
void MBInitMaster(UART_HandleTypeDef *huart);
char MBReceive(char slave, char *type, int *address, int *data);
void MBSend(char slave, int address, int value);
void MBRespond(char slave, int sensor_value);
char check_crc(char *frame, int len);
unsigned short int CRC16(char *nData, unsigned short int wLength);

#endif