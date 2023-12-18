#include "uart.h"
#include "lcd.h"
#include <avr/io.h>
#include "timer.h"
#include "keypad.h"
#include <util/delay.h>

#define MC1_READY 0x11
#define MC2_READY 0x01
#define OPEN_DOOR 'O'
#define RESET_PASS 'R'
#define ENTER_PASS 'E'
#define ALARM 'X'

void sendStatus(uint8 status);
void mainOptions();

Timer1_ConfigType timer15sec={0,60000,F_CPU_1024,COMPARE};  // Two ticks
Timer1_ConfigType timer3sec={0,24000,F_CPU_1024,COMPARE};
uint8 ticks=0;

void passReset(){
	uint8 reEnter=1;
	uint8 pass[6];
	uint8 passRe[6];
	uint8 enter;
	LCD_clearScreen();

	while(reEnter){
		reEnter=0;
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		for(uint8 i=0;i<5;i++){
			pass[i]= KEYPAD_getPressedKey();
			_delay_ms(750);
			LCD_intgerToString(pass[i]);
		}
		while(enter !='*'){
			enter=KEYPAD_getPressedKey();
			_delay_ms(750);
		}
		enter=0;
		LCD_moveCursor(0,0);
		LCD_displayStringRowColumn(0,0,"plz re_enter the");
		LCD_displayStringRowColumn(1,0,"same pass:");
		for(uint8 i=0;i<5;i++){
			passRe[i]=KEYPAD_getPressedKey();
			_delay_ms(750);
			LCD_intgerToString(passRe[i]);
		}
		while(enter !='*'){
			enter=KEYPAD_getPressedKey();
			_delay_ms(750);
		}
		enter=0;
		LCD_clearScreen();
		pass[5]='#';
		passRe[5]='#';
		//while(UART_recieveByte() != MC2_READY){}
		UART_sendString(pass);
		UART_sendString(passRe);
		UART_sendByte(MC1_READY);
		reEnter=UART_recieveByte();
	}

}

uint8 enterPass(){
	uint8 pass[6];
	uint8 correct=0;
	uint8 enter=0;
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,0);
	for(uint8 i=0;i<5;i++){
		pass[i]= KEYPAD_getPressedKey();
		_delay_ms(750);
		LCD_intgerToString(pass[i]);
	}
	while(enter !='*'){
		enter=KEYPAD_getPressedKey();
		_delay_ms(750);
	}
	pass[5]='#';
	sendStatus(ENTER_PASS);
	UART_sendString(pass);
	UART_sendByte(MC1_READY);
	correct=UART_recieveByte();
	LCD_displayCharacter(correct);
	return correct;
}

void sendStatus(uint8 status){
	UART_sendByte(status);
}

void display(){
	if(ticks==0){
		ticks++;
	}
	else if(ticks==1){
		LCD_clearScreen();
		LCD_displayString("Door is locking");
		ticks++;
	}
	else if(ticks==2){
		ticks++;
	}
	else if(ticks==3){
		ticks++;
	}
	else if(ticks==4){
		Timer1_deInit();
		ticks++;
	}
}

void openDoor(){
	LCD_clearScreen();
	LCD_displayString("Door is Unlocking");
	Timer1_init(&timer15sec);
	Timer1_setCallBack(display);
	return;
}



void alarm (){
	LCD_clearScreen();
	LCD_displayString("ERROR");
	sendStatus(ALARM);
	_delay_ms(60000);
	mainOptions();
}

void mainOptions(){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");
	uint8 choice = KEYPAD_getPressedKey();
	_delay_ms(750);
	if(choice=='+'){
		if(enterPass()){
			sendStatus(OPEN_DOOR);
			openDoor();
		}
		else{
			if(enterPass()){
				sendStatus(OPEN_DOOR);
				openDoor();
			}
			else{
				if(enterPass()){
					sendStatus(OPEN_DOOR);
					openDoor();
				}
				else{
					alarm();
				}
			}
		}

	}
	else if (choice=='-'){
		if(enterPass()){
			sendStatus(RESET_PASS);
			passReset();
		}
		else{
			if(enterPass()){
				sendStatus(RESET_PASS);
				passReset();
			}
			else{
				if(enterPass()){
					sendStatus(RESET_PASS);
					passReset();
				}
				else{
					alarm();
				}
			}
		}

	}
	while(ticks!=5);
	ticks=0;
	mainOptions();
}

int main(void){
	SREG |= (1<<7) ;

	Timer1_ConfigType timerConfig={0,5000,F_CPU_1024,COMPARE};
	Timer1_init(&timerConfig);
	LCD_init();
	UART_ConfigType uartConfig={EIGHT_BIT,EVEN,ONE_BIT,9600};
	UART_init(&uartConfig);

	passReset();
	mainOptions();

	while(1)
	{

	}
}



