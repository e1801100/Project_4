#include "i2c.h"
#include "bme280.h"
#include <string.h>
#include <stdlib.h>

void bme280_start(struct bme280_dev *dev) {
	//int8_t rslt;

	dev->dev_id = BME280_I2C_ADDR_PRIM;
	dev->intf = BME280_I2C_INTF;
	bme280_init(dev);

	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	bme280_set_sensor_settings(BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL, dev);
}
int8_t bme280_read(float *temperature, float *humidity, struct bme280_dev *dev)
 {
	int8_t rslt;
	struct bme280_data comp_data;

	rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
	delay_ms(40);
	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
    if(rslt == BME280_OK) {
		*temperature = comp_data.temperature / 100.0;	/* °C  */
		*humidity = comp_data.humidity / 1024.0;		/* %   */
		return 1;
	}
	return 0;
}

int8_t i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	if (HAL_I2C_Master_Transmit(&hi2c1, (id << 1), &reg_addr, 1, 10) != HAL_OK)
		return -1;
	if (HAL_I2C_Master_Receive(&hi2c1, (id << 1) | 0x01, data, len, 10) != HAL_OK)
		return -1;

	return 0;
}

void delay_ms(uint32_t period)
{
    OS_ERR os_err;
    HAL_Delay(period);
}

int8_t i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	int8_t *buf;
	buf = malloc(len + 1);
	buf[0] = reg_addr;
	memcpy(buf + 1, data, len);

	if (HAL_I2C_Master_Transmit(&hi2c1, (id << 1), (uint8_t *)buf, len + 1, HAL_MAX_DELAY) != HAL_OK)
		return -1;

	free(buf);
	return 0;
}