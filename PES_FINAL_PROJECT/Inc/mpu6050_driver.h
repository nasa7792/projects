/*
 * mpu6050_driver.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Nalin Saxena
 * 
 * File contains register map information of the mpu 6050
 * Also has function declarations for mpu init and other functions used to convert raw mpu values
 * 
 * Refrences- taken register map from https://controllerstech.com/how-to-interface-mpu6050-gy-521-with-stm32/
 * and for interrupt register -https://github.com/jarzebski/Arduino-MPU6050
 */

#ifndef MPU6050_DRIVER_H_
#define MPU6050_DRIVER_H_
#include "I2C_bitbanging_approach.h"
#include <math.h>

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75
#define MPU_ADDRESS 0x68
#define INT_ENABLE_REG 0x38
#define MPU6050_REG_FF_DURATION 0x1E
#define MPU6050_REG_FF_THRESHOLD 0x1D
#define MPU6050_REG_INT_STATUS 0x3A
#define MPU6050_REG_MOT_DETECT_STATUS 0x61
#define MPU6050_REG_INT_PIN_CFG 0x37
#define MPU6050_REG_CONFIG 0x1A
#define MPU6050_REG_MOT_THRESHOLD 0x1f
#define MPU6050_REG_MOT_DURATION 0x20
#define LSB_SENSITIVITY_ACCEL (16384.0)
#define LSB_SENSITIVITY_GYRO (131.0)
#define FILTER_COEF 0.98 // Complementary filter coefficient
#define MPU_POS_Z_DIRECTION_MASK 2

/*
 * configures and initalizes MPU accelorometer gyroscope and motion sensing interupt
 * Parameters:
 * 			 none
 * Returns:
 * 			none
 */
void MPU_INIT();

/*
 * Fetch accelorometer values
 * Parameters:
 * 			 int16_t *ACCEL_X, : accelration in x
 *           int16_t *ACCEL_Y  : accelration in y
 *           int16_t *ACCEL_Z  : accelration in z
 * Returns:
 * 			none
 */
void get_ACCEL_VALUES(int16_t *ACCEL_X, int16_t *ACCEL_Y, int16_t *ACCEL_Z);
/*
 * Fetch gryo angle change
 * Parameters:
 * 			 int16_t *GYRO_X_RAW, : angle change  in x
 *           int16_t *GYRO_Y_RAW  : angle change  in y
 *           int16_t *GYRO_Z_RAW  : angle change  in z
 * Returns:
 * 			none
 */
void get_GYRO_VALUES(int16_t *GYRO_X_RAW, int16_t *GYRO_Y_RAW, int16_t *GYRO_Z_RAW);

/*
 * calcaulte pitch and roll values from accelorometer values
 * Parameters:
 * 			 accel_x_raw : accelration in x
 *           accel_y_raw : accelration in y
 *           accel_z_raw  : accelration z
 *           *pitch       :caclulated pitch value
 *            *roll       :caclulated roll value
 * Returns:
 * 			none
 */
void calculate_pitch_roll_values(float *pitch, float *roll, int16_t accel_x_raw, int16_t accel_y_raw, int16_t accel_z_raw);
#endif /* MPU6050_DRIVER_H_ */
