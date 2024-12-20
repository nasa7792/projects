/*
 * LED_module.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Nalin Saxena
 */

#ifndef LED_MODULE_H_
#define LED_MODULE_H_
#include <stm32f091xc.h>
#include "utilities.h"
#include <stdlib.h>
#include "timer_pwm.h"
#include "delay.h"

/*
Configures  leds linked to tim3 ch1,ch2,ch3,ch4 to afr functioanlity
Configure PB4->tim3 ch1
Configure PB5->tim3 ch2
Configure PB0->tim3 ch3
Configure PB1->tim3 ch4
 *
 * Parameters:
 * 			 none
 *
 * Returns:
 * 			none
 */
void configure_display_LEDS();
void update_led_brightness_values(float roll, float pitch);

/*
 * sets brigthness of positive roll led
 * Parameters:
 * 			 value brightness level - inputed in respective ccr value
 * Returns:
 * 			none
 */
void set_positive_roll(int value);

/*
 * sets brigthness of negative roll led
 * Parameters:
 * 			 value brightness level - inputed in respective ccr value
 * Returns:
 * 			none
 */
void set_negative_roll(int value);

/*
 * sets brigthness of positive pitch  led
 * Parameters:
 * 			 value brightness level - inputed in respective ccr value
 * Returns:
 * 			none
 */
void set_positive_pitch(int value);

/*
 * sets brigthness of negative pitch  led
 * Parameters:
 * 			 value brightness level - inputed in respective ccr value
 * Returns:
 * 			none
 */
void set_negative_pitch(int value);

/*
 * executes a special led sequence eveytime a jump is detected
 * Parameters:
 * 			 int jump_count nubmer of times the jump sequence has to be executed
 * Returns:
 * 			none
 */
void execute_jump_sequence(int jump_count);

/*
 * configures pa0 as an external interupt to match the configuration of mpu interrupt pin
 * Parameters:
 * 			none
 * Returns:
 * 			none
 */
void configure_Mcu_MPU_pin(void);

/*
 * configures exti interupt for pa0
 * Parameters:
 * 			none
 * Returns:
 * 			none
 */
void configure_exti_interupt(void);

#endif /* LED_MODULE_H_ */
