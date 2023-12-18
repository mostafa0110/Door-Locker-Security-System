 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/

#include "pwm.h"
#include "avr/io.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle){
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	TCNT0 = 0;
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	OCR0 = (duty_cycle*255)/100;


}

