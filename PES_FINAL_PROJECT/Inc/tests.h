/*
 * tests.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Nalin Saxena
 */

#ifndef TESTS_H_
#define TESTS_H_
#include"I2C_bitbanging_approach.h"
#include"mpu6050_driver.h"
#include<stdio.h>
#include"delay.h"
#include<stdlib.h>

void check_mpu_presenece();
void test_mpu_reads();
void test_run_suite();
#endif /* TESTS_H_ */
