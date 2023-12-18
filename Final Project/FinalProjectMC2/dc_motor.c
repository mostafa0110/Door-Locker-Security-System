 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/

#include "dc_motor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void){
	GPIO_setupPinDirection(MOTOR_PORT ,MOTOR_PIN1,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT ,MOTOR_PIN2,PIN_OUTPUT);\
	GPIO_writePin(MOTOR_PORT ,MOTOR_PIN1,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT ,MOTOR_PIN2,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state){
	if(state==A_CW){
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN2,LOGIC_HIGH);
	}
	else if(state==CW){
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN1,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN2,LOGIC_LOW);
	}
	else{
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT ,MOTOR_PIN2,LOGIC_LOW);
	}
	//PWM_Timer0_Start(speed);

}
