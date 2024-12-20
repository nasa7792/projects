/*
 * test.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Nalin Saxena
 * 
 * This file contains function definitions for a few simple test cases related to the mpu
 */


#include"tests.h"

//test mpu presenece
void check_mpu_presenece(){
	uint8_t mpu_id = I2C_READ_REGISTER(WHO_AM_I_REG);
	if(mpu_id!=MPU_ADDRESS){
		printf("\033[1;31m\n\r MPU NOT DETECTED TERMINATING PROGRAM !\033[0m\n\r");
		printf("\033[1;31m Press reset button on the MCU and try again !\033[0m\n\r");
		exit(1);
	}
	else{
		printf("\033[1;32m\n\rMPU DETECTED! TEST CASE PASSED SUCCESSFULLY \033[0m\n\r");
}
}
//do simple mpu read checks
void test_mpu_reads(){

	int16_t TEST_ACCEL_X_RAW;
	int16_t TEST_ACCEL_Y_RAW;
	int16_t TEST_ACCEL_Z_RAW;
	float test_accel_pitch = 0.0,  test_accel_roll = 0.0;

	printf("\033[1;33m PITCH MPU SENSOR UP OR DOWN !\033[0m\n\r");
	printf("\033[1;33m Begining 10 test measurements from mpu !\033[0m\n\n\r");
	for(int i=0;i<10;i++){
		get_ACCEL_VALUES(&TEST_ACCEL_X_RAW, &TEST_ACCEL_Y_RAW, &TEST_ACCEL_Z_RAW);
		calculate_pitch_roll_values(&test_accel_pitch, &test_accel_roll, TEST_ACCEL_X_RAW, TEST_ACCEL_Y_RAW, TEST_ACCEL_Z_RAW);
		printf("test pitch %f \n\r",test_accel_pitch);
	}
	printf("\033[1;32m Completed 10 reads from mpu TEST CASE PASSED ! \033[0m\n\r");
}

void test_run_suite(){
	check_mpu_presenece();
	test_mpu_reads();
}
