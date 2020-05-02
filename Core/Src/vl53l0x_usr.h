/*
 * vl53l0x.h
 *
 *  Created on: 30 ���. 2019 �.
 *      Author: Igor
 */

#ifndef VL53L0X_USR_H_
#define VL53L0X_USR_H_

#include "stm32f1xx_hal.h"

void ledOn(void);
void ledOff(void);
void error(void);
void sensor_ini(void);
uint8_t read_id(void);
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg);
static void I2Cx_WriteData(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value);
uint8_t sensor_io_read(uint16_t DeviceAddr, uint8_t RegisterAddr);
uint8_t sensor_io_write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value);

#endif /* VL53L0X_USR_H_ */
