/*
 * timer_pwm.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Nalin Saxena
 *
 * File contain init function for setting up all channels of timer 3 as pwm mode
 */

#include "timer_pwm.h"
#include "utilities.h"
#include <stm32f091xc.h>

void setup_pwm_channels()
{
	// Configure TIM3 counter and prescaler
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = PWM_PRESCALER - 1;
	TIM3->ARR = PWM_MAX_DUTY_VALUE;
	TIM3->CR1 = 0; // count down

	// Configure TIM3 channel 1 for pwm
	TIM3->CCR1 = 0;										 // by default LED off
	TIM3->CCER |= TIM_CCER_CC1P;						 // active low polarity
	MODIFY_FIELD(TIM3->CCMR1, TIM_CCMR1_OC1M, PWM_MODE); // Select PWM mode
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;						 // Enable preload register
	TIM3->CCER |= TIM_CCER_CC1E;						 // Enable channel output on channel 1

	// Configure TIM3 channel 2 for pwm
	TIM3->CCR2 = 0;										 // by default LED off
	TIM3->CCER |= TIM_CCER_CC2P;						 // active low polarity
	MODIFY_FIELD(TIM3->CCMR1, TIM_CCMR1_OC2M, PWM_MODE); // Select PWM mode
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;						 // Enable preload register
	TIM3->CCER |= TIM_CCER_CC2E;						 // Enable channel output on channel 2

	// Configure TIM3 channel 3 for pwm
	TIM3->CCR3 = 0;										 // by default LED off
	TIM3->CCER |= TIM_CCER_CC3P;						 // active low polarity
	MODIFY_FIELD(TIM3->CCMR2, TIM_CCMR2_OC3M, PWM_MODE); // Select PWM mode
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE;						 // Enable preload register
	TIM3->CCER |= TIM_CCER_CC3E;						 // Enable channel output on channel 3

	// Configure TIM3 channel 4 for pwm
	TIM3->CCR4 = 0;										 // by default LED off
	TIM3->CCER |= TIM_CCER_CC4P;						 // active low polarity
	MODIFY_FIELD(TIM3->CCMR2, TIM_CCMR2_OC4M, PWM_MODE); // Select PWM mode
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE;						 // Enable preload register
	TIM3->CCER |= TIM_CCER_CC4E;						 // Enable channel output on channel 4

	TIM3->EGR |= TIM_EGR_UG;	// Generate update
	TIM3->BDTR |= TIM_BDTR_MOE; // Enable main output
	TIM3->CR1 |= TIM_CR1_CEN;
}
