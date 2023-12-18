 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/
#include "buzzer.h"
#include"gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	Buzzer_off();
}

void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}


