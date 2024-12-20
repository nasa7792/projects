/*
 * LED_module.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Nalin Saxena
 */

#include "LED_module.h"
#include <stdio.h>

void configure_display_LEDS()
{
	// configure 4 channels for pwm
	//  Configure PB4 tim3 ch1
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER4, ESF_GPIO_MODER_ALT_FUNC); // alternate function mode
	MODIFY_FIELD(GPIOB->AFR[0], GPIO_AFRL_AFRL4, 1);

	// Configure PB5 tim3 ch2
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER5, ESF_GPIO_MODER_ALT_FUNC); // alternate function mode
	MODIFY_FIELD(GPIOB->AFR[0], GPIO_AFRL_AFRL5, 1);

	// Configure PB0 tim3 ch3
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER0, ESF_GPIO_MODER_ALT_FUNC); // alternate function mode
	MODIFY_FIELD(GPIOB->AFR[0], GPIO_AFRL_AFRL0, 1);

	// Configure PB1 tim3 ch4
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER1, ESF_GPIO_MODER_ALT_FUNC); // alternate function mode
	MODIFY_FIELD(GPIOB->AFR[0], GPIO_AFRL_AFRL1, 1);
}

void set_positive_roll(int value)
{
	TIM3->CCR1 = value;
}

void set_negative_roll(int value)
{
	TIM3->CCR3 = value;
}

void set_positive_pitch(int value)
{
	TIM3->CCR2 = value;
}

void set_negative_pitch(int value)
{
	TIM3->CCR4 = value;
}

void update_led_brightness_values(float roll, float pitch)
{
	// update led brightness based on roll and pitch values
	int roll_mapped = 0;
	int pitch_mapped = 0;
	// we upscale and  map vaules from a scale of 0-1000
	if (roll < 0)
	{ // update negative roll
		roll_mapped = -roll;
		roll_mapped = (int)(roll_mapped * 1000) / 180;
		set_negative_roll(roll_mapped);
		set_positive_roll(0);
	}
	else
	{ // update positive roll
		roll_mapped = (int)(roll * 1000) / 180;
		set_positive_roll(roll_mapped);
		set_negative_roll(0);
	}

	if (pitch < 0)
	{ // update negative pitch
		pitch_mapped = -pitch;
		pitch_mapped = (int)(pitch_mapped * 1000) / 90;
		set_negative_pitch(pitch_mapped);
		set_positive_pitch(0);
	}
	else
	{ // update positive pitch
		pitch_mapped = (int)(pitch * 1000) / 90;
		set_positive_pitch(pitch_mapped);
		set_negative_pitch(0);
	}
}

void execute_jump_sequence(int jump_count)
{
	//if jump is detected we execute a blink sequence
	printf("MPU JUMP detected !\n \r");
	printf("executing jump sequence %d times \n \r ", jump_count);
	//execute blink sequence for  jump_count times
	for (int i = 0; i < jump_count; i++)
	{
		set_positive_roll(PWM_MAX_DUTY_VALUE);
		set_negative_roll(PWM_MAX_DUTY_VALUE);
		set_positive_pitch(PWM_MAX_DUTY_VALUE);
		set_negative_pitch(PWM_MAX_DUTY_VALUE);
		delay(1000);
		set_positive_roll(0);
		set_negative_roll(0);
		set_positive_pitch(0);
		set_negative_pitch(0);
		delay(1000);
	}
}

void configure_Mcu_MPU_pin(void)
{
	// Enable GPIOA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// pa0 as input
	MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODER0, ESF_GPIO_MODER_INPUT);

	// configure pupdr register set as pull up
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;	 // Clear previous setting
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0; // Set PA0 to pull-up (0x01)
}

void configure_exti_interupt(void)
{
	// Enable SYSCFG clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

	// Map PA0 to EXTI0
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;

	// Configure EXTI0 for rising edge trigger (interrupt triggered when INT pin goes low)
	EXTI->RTSR |= EXTI_RTSR_TR0;  // Rising edge trigger enabled
	EXTI->FTSR &= ~EXTI_FTSR_TR0; // Disable falling edge trigger

	// Enable EXTI0 interrupt
	EXTI->IMR |= EXTI_IMR_MR0;

	// Enable EXTI0 interrupt in NVIC (nested vector interrupt controller)
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_SetPriority(EXTI0_1_IRQn, 2); // Set priority level (adjust as needed)
}
