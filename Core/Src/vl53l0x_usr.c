/*
 * vl53l0x.c
 *
 *  Created on: 30 ���. 2019 �.
 *      Author: Igor
 */
//#include "vl53l0x.h"
#include "vl53l0x_usr.h"
#include "stm32f1xx_hal.h"

extern volatile uint32_t sysTick_Time;
extern I2C_HandleTypeDef hi2c1;
extern uint8_t ctrl_a, ctrl_b;
//HAL_StatusTypeDef status = HAL_OK;
uint8_t test = 0x00;
uint8_t a, b = 0;
uint8_t value = 0;

void delay(uint32_t delayTime){
	uint32_t startTime =  sysTick_Time;
	while ( (sysTick_Time - startTime) < delayTime );
}

void error(void) {
	ledOn();
	HAL_Delay(500);
	ledOff();
	HAL_Delay(500);
}

uint8_t sensor_io_read(uint16_t DeviceAddr, uint8_t RegisterAddr) {
	return I2Cx_ReadData(DeviceAddr, RegisterAddr);
	return HAL_OK;
}

uint8_t sensor_io_write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value) {
	I2Cx_WriteData(DeviceAddr, RegisterAddr, Value);
	return HAL_OK;
}

static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg) {
	HAL_StatusTypeDef status = HAL_OK;
	value = 0;
	status = HAL_I2C_Mem_Read(&hi2c1, Addr<<1, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	if(status != HAL_OK)
	{
		a = 1;
	    error();
	}
	return value;
}

static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value) {
	HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)(Reg<<1), I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);
    /* Check the communication status */
    if(status != HAL_OK)
    {
    /* Execute user timeout callback */
    error();
    }
}

void ledOn(void) {
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET);
}

void ledOff(void) {
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET);
}

uint8_t read_id_a(void) {
	//HAL_Delay(1000);
	ctrl_a = 0x00;
	ctrl_a = sensor_io_read(0x30, 0xC0);
	return ctrl_a;
}

uint8_t read_id_b(void) {
	ctrl_b = 0x00;
	ctrl_b = sensor_io_read(0x51, 0xC0);
	return ctrl_b;
}


void sensor_ini(void) {
	read_id_a();
	read_id_b();
	HAL_Delay(1000);
	if (read_id_a()==0xEE) {
		a = 2;
	}
	else if (read_id_b()==0xEE) {
		b = 2;
	}
	else error();
}


