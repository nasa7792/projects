/*
 * timer_pwm.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Nalin Saxena
 */

#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_

#define F_TIM_CLOCK (48000000L) // frequency of clock
#define PWM_FREQUENCY (500)
#define PWM_MAX_DUTY_VALUE ((F_TIM_CLOCK / (PWM_FREQUENCY * PWM_PRESCALER)) - 1) // calculate pwm max duty value
#define PWM_PRESCALER (96)                                                       // to get max value of pwm CCR2 to ~ 1000
#define PWM_MODE 6                                                               // pwm mode is selected by writing 110 as mentioned in the documentation

/*
 * Configures  the TIM3 channel 1,2,3,4 and sets them all as pwm output chaannels
 *
 * Parameters:
 * 			 none
 *
 * Returns:
 * 			none
 */
void setup_pwm_channels();

#endif /* TIMER_PWM_H_ */
