 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Mostafa Hesham
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT PORTB_ID
#define BUZZER_PIN PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
#endif /* BUZZER_H_ */
