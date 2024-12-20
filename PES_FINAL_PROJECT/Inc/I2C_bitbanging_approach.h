/*
 * I2C_bitbanging_approach.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Nalin Saxena
 * 
 * This file contains macro definitions regarding I2C pins 
 * and function definitions for fundamental i2c modules
 */

#ifndef I2C_BITBANGING_APPROACH_H_
#define I2C_BITBANGING_APPROACH_H_
#include <stm32f091xc.h>
#include "delay.h"
#include "utilities.h"
#include <stdint.h>

//define macros for scl and sda high and low conditions
#define SCL_set_high GPIO_BSRR_BS_8
#define SCL_set_low GPIO_BSRR_BR_8
#define SDA_set_high GPIO_BSRR_BS_9
#define SDA_set_low GPIO_BSRR_BR_9
#define MSB_flag 0x80

#define SCL_HIGH() (GPIOB->BSRR |= SCL_set_high)
#define SCL_LOW() (GPIOB->BSRR |= SCL_set_low)
#define SDA_HIGH() (GPIOB->BSRR |= SDA_set_high)
#define SDA_LOW() (GPIOB->BSRR |= SDA_set_low)
#define MPU_DEVICE_ADDRESS 0x68

/*
 * initalizes scl and sda configures them for i2c communication
 * Parameters:

 * Returns:
 * 			none
 */
void I2C_bitbanging_init();

/*
 * generates i2c start condition
 * Parameters:

 * Returns:
 * 			none
 */
void I2C_start_condition();

/*
 * generates i2c stop condition
 * Parameters:
 *          none
 * Returns:
 * 			none
 */
void I2C_stop_condition();

/*
 * checks the status of sda pin
 * Parameters:
 *           none
 * Returns:
 * 			none
 */
uint8_t SDA_READ();

/*
 * writes a byte of data 
 * Parameters:
 *           data:to be written
 * Returns:
 * 			none
 */
void I2C_write_byte(uint8_t data);

/*
 * reads a byte of data
 * Parameters:
 *           none
 * Returns:
 * 			uint8_t- data returned
 */
uint8_t I2C_read_byte();

/*
 * reads a register
 * Parameters:
 *           reg- register address
 * Returns:
 * 			uint8_t- data returned
 */
uint8_t I2C_READ_REGISTER(uint8_t reg);


/*
 * writes to  a register
 * Parameters:
 *           reg- register address
 *           data- data to be written
 * Returns:
 * 		none
 */
void I2C_WRITE_REGISTER(uint8_t reg, uint8_t data);

#endif /* I2C_BITBANGING_APPROACH_H_ */
