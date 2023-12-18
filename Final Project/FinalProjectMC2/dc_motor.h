 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTOR_PORT PORTD_ID
#define MOTOR_PIN1 PIN4_ID
#define MOTOR_PIN2 PIN5_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	STOP,CW,A_CW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state);


#endif /* DC_MOTOR_H_ */
