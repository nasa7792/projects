/*
 * mpu6050.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Nalin Saxena
 * 
 * This file containts function definitions related to mpu setup and converting of raw accelration 
 * and gyroscope values
 */

#include "mpu6050_driver.h"
#include <stdio.h>

void MPU_INIT()
{
	uint8_t data = 0;
	I2C_WRITE_REGISTER(PWR_MGMT_1_REG, data);

	// set sample rate of 1khz

	data = 0x07;
	I2C_WRITE_REGISTER(SMPLRT_DIV_REG, data);

	// configure accl and gyro registers setting 2g range for acc 250 for gyro
	data = 0;
	I2C_WRITE_REGISTER(GYRO_CONFIG_REG, data);
	I2C_WRITE_REGISTER(ACCEL_CONFIG_REG, data);

    //configuring interupt pin of the mpu
	data = 0x50;
	I2C_WRITE_REGISTER(MPU6050_REG_INT_PIN_CFG, data);

	data = 0x5;
	I2C_WRITE_REGISTER(ACCEL_CONFIG_REG, data);

	data = 0x03; // Set DLPF to 44Hz for accel and 42Hz for gyro
	I2C_WRITE_REGISTER(MPU6050_REG_CONFIG, data);

	data = 0x50; //motion threshold
	I2C_WRITE_REGISTER(MPU6050_REG_MOT_THRESHOLD, data);

	data = 4; //motion duration threshold
	I2C_WRITE_REGISTER(MPU6050_REG_MOT_DURATION, data);

	data = 0x40; // enable motion interupt
	I2C_WRITE_REGISTER(INT_ENABLE_REG, data);
}

void get_ACCEL_VALUES(int16_t *ACCEL_X, int16_t *ACCEL_Y, int16_t *ACCEL_Z)
{//read values of acceleration starting from ACCEL_XOUT_H_REG one by one  bytes
	uint8_t accel_values[6];
	for (int i = 0; i < 6; i++)
	{
		accel_values[i] = I2C_READ_REGISTER(ACCEL_XOUT_H_REG + i);
	}
	//data comens in msb and then lsb so we use shift <<8 for MSB and then | for LSB
	*ACCEL_X = (int16_t)(accel_values[0] << 8 | accel_values[1]);
	*ACCEL_Y = (int16_t)(accel_values[2] << 8 | accel_values[3]);
	*ACCEL_Z = (int16_t)(accel_values[4] << 8 | accel_values[5]);
}

void get_GYRO_VALUES(int16_t *GYRO_X_RAW, int16_t *GYRO_Y_RAW, int16_t *GYRO_Z_RAW)
{//read values of gyro starting from GYRO_XOUT_H_REG one by one  bytes
	uint8_t gyro_valueS[6];
	for (int i = 0; i < 6; i++)
	{
		gyro_valueS[i] = I2C_READ_REGISTER(GYRO_XOUT_H_REG + i);
	}
	*GYRO_X_RAW = (int16_t)(gyro_valueS[0] << 8 | gyro_valueS[1]);
	*GYRO_Y_RAW = (int16_t)(gyro_valueS[2] << 8 | gyro_valueS[3]);
	*GYRO_Z_RAW = (int16_t)(gyro_valueS[4] << 8 | gyro_valueS[5]);
}

void calculate_pitch_roll_values(float *pitch, float *roll, int16_t accel_x_raw, int16_t accel_y_raw, int16_t accel_z_raw)
{
	float ax = accel_x_raw / LSB_SENSITIVITY_ACCEL; // convert values to angle changes
	float ay = accel_y_raw / LSB_SENSITIVITY_ACCEL;
	float az = accel_z_raw / LSB_SENSITIVITY_ACCEL;

	*roll = atan2(ay, az) * 180 / M_PI;
	*pitch = -atan2(ax, sqrt(ay * ay + az * az)) * 180 / M_PI;
}

