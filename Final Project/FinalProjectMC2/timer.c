/******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer 1 driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the overflow  */
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after compare match */
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	TCCR1A = 0x00;

	/* Clock Select bits CS12 CS11 CS10 (first three bits)*/
	/* select mode WGM12 = 0 -> Normal     WGM12 = 1 -> compare mode*/

	TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode)<<WGM12);

	/* Set initial value*/

	TCNT1 = Config_Ptr->initial_value;

	/* if operating in Compare mode set the compare value
	 * and enable the Compare A Match Interrupt Enable bit */

	if(Config_Ptr->mode){
		OCR1A = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE1A);
	}
	/* Else Overflow Interrupt Enable for normal mode */
	else{
		TIMSK |= (1<<TOIE1);
	}

}

void Timer1_deInit(void){
	/* Clear All Timer1 Registers */
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1 =  0x00;
	OCR1A =  0x00;

	/* Disable the interrupts */
	TIMSK &= ~(1<<OCIE1A);
	TIMSK &= ~(1<<TOIE1);

	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}

void Timer1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

