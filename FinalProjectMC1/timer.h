 /******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer.h
 *
 * Description: Header file for the Timer 1 driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

typedef enum{
	NORMAL, COMPARE
}Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
