/*
 * I2C_bitbanging_approach.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Nalin Saxena
 *
 * This file contains function definitions related to i2c bit banging implementation
 */

#include "I2C_bitbanging_approach.h"

void I2C_bitbanging_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable GPIOB clock

	// configure scl and sda as output pins
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER8, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER9, ESF_GPIO_MODER_OUTPUT);

	// set as open drain
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;

	GPIOB->PUPDR &= ~((3U << GPIO_PUPDR_PUPDR8_Pos) | (3U << GPIO_PUPDR_PUPDR9_Pos));
	GPIOB->PUPDR |= (1U << GPIO_PUPDR_PUPDR8_Pos) | (1U << GPIO_PUPDR_PUPDR9_Pos);

	// both lines are idle high
	SCL_HIGH();
	SDA_HIGH();
}

void I2C_start_condition()
{
	SCL_HIGH();
	SDA_HIGH();
	SDA_LOW(); // sda goes low first while scl is high
	SCL_LOW();
}

void I2C_stop_condition()
{
	SCL_LOW();
	SDA_LOW();
	SCL_HIGH(); // scl goes high first
	SDA_HIGH();
}

uint8_t SDA_READ(void)
{
	return (GPIOB->IDR & (1 << 9)) ? 1 : 0; // checks if sda pin is high or low
}

void I2C_write_byte(uint8_t data)
{
	// write 8 bits
	for (int i = 0; i < 8; i++)
	{
		if (data & MSB_flag)
		{
			SDA_HIGH();
		}
		else
		{
			SDA_LOW();
		}
		// clock pulse;
		SCL_HIGH();
		SCL_LOW();
		data <<= 1; // get next msb by shifting by 1
	}
	// send one more clock pulse to check for ack release sda line
	SDA_HIGH();
	SCL_HIGH();
	if (SDA_READ() == 0)
	{
	}
	SCL_LOW();
}

uint8_t I2C_read_byte()
{
	uint8_t data = 0;
	// Set as input sda
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER9, ESF_GPIO_MODER_INPUT);
	for (int i = 0; i < 8; i++)
	{
		data <<= 1;
		SCL_HIGH();
		if (SDA_READ()) // check status of sda pin
		{
			data |= 1;
		}
		SCL_LOW();
	}
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER9, ESF_GPIO_MODER_OUTPUT);
	return data;
}

void I2C_WRITE_REGISTER(uint8_t reg, uint8_t data)
{
	I2C_start_condition();					 // first generate i2c start condition
	I2C_write_byte(MPU_DEVICE_ADDRESS << 1); // write device address
	I2C_write_byte(reg);					 // send register address
	I2C_write_byte(data);					 // send data
	I2C_stop_condition();					 // stop i2c communications
}

uint8_t I2C_READ_REGISTER(uint8_t reg)
{
	uint8_t data;
	I2C_start_condition();						 // first generate i2c start condition
	I2C_write_byte(MPU_DEVICE_ADDRESS << 1);	 // write the "write address "
	I2C_write_byte(reg);						 // send register address
	I2C_start_condition();						 // send repeated start condition
	I2C_write_byte(MPU_DEVICE_ADDRESS << 1 | 1); // send read address
	data = I2C_read_byte();						 // read data  byte
	I2C_stop_condition();						 // stop i2c comms
	return data;
}
