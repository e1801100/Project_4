#ifndef _BME280_H
#define _BME280_H

typedef struct
{
	uint8_t temperature;
	uint8_t humidity;
}bme280_t;

//Initializes the BME280 humidity and temperature sensor
extern void BME280_Init(void);

extern void BME280_GetData(bme280_t* pSensorData);

#endif //_BME280_H
