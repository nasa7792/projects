/*
 * I2C_bitbanging_approach.h
 *
 *  Created on: Dec 11, 2024
 *      Author: Nalin Saxena
 * 
 * This file contains declarations related to systick and delay function
 */
#ifndef DELAY_H_
#define DELAY_H_

#include "stdint.h"
/*
 * Configures the sysTick timer with correct LOAD register value to configure it for 20 ms
 * Sets the priority with NVIC
 * Parameters:
 * 			 none
 *
 * Returns:
 * 			none
 */
void delay_init();

/*
 *returns number of ticks ellapsed  passed
 *
 * Parameters:
 * 			 none
 *
 * Returns:
 * 			millis uint64_t number of ticks ellapsed
 */
uint64_t millis();

/*
 *busy waits for a set number of milli seconds specified by the argument of the function
 *
 * Parameters:
 * 			 time number of milli seconds to delay
 *
 * Returns:
 * 			none
 */
void delay(uint32_t time);
#endif /* DELAY_H_ */
