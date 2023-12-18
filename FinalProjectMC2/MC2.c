#include "uart.h"
#include <avr/io.h>
#include "dc_motor.h"
#include "timer.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include <util/delay.h>


#define MC2_READY 0x01
#define MC1_READY 0x11
#define OPEN_DOOR 'O'
#define RESET_PASS 'R'
#define ENTER_PASS 'E'
#define ALARM 'X'

uint8 savedPass[5];
uint8 ticks=0;

Timer1_ConfigType timer15sec={0,60000,F_CPU_1024,COMPARE}; //Two ticks
Timer1_ConfigType timer3sec={0,24000,F_CPU_1024,COMPARE};

void savePass(){
	uint16 address=0x0311;
	for(uint8 i=0;i<5;i++){
		EEPROM_writeByte(address,savedPass[i]);
		_delay_ms(10);
		address++;
	}
	return;
}

void checkPass(){
	uint8 pass[6];
	uint8 passRe[6];
	uint8 reEnter=1;
	while(reEnter){
		reEnter=0;
		//UART_sendByte(MC2_READY);
		UART_receiveString(pass);
		UART_receiveString(passRe);
		for(uint8 i=0;i<5;i++){
			if(pass[i] != passRe[i]){
				reEnter=1;
			}
		}
		while(UART_recieveByte() != MC1_READY){}
		UART_sendByte(reEnter);
	}
	for(uint8 i=0;i<5;i++){savedPass[i]=pass[i];}
}



void comparePass(){
	uint8 correct=1;
	uint8 pass[6];
	uint8 temp;
	uint16 address=0x0311;
	UART_receiveString(pass);
	for(uint8 i=0;i<5;i++){
		EEPROM_readByte(address,&temp);
		_delay_ms(10);
		if(pass[i] != temp){
			correct=0;
		}
		address++;
	}
	/*for(uint8 i =0;i<5;i++){
		if(pass[i] != savedPass[i]){
			correct=0;
		}
	}*/
	while(UART_recieveByte() != MC1_READY){}
	UART_sendByte(correct);
}

uint8 getStatus(){
	return UART_recieveByte();
}

void controlMotor(){
	if(ticks<4){
		ticks++;
	}
	else if(ticks==4){
		DcMotor_Rotate(STOP);
		ticks++;
	}
	else if(ticks==5){
		DcMotor_Rotate(A_CW);
		ticks++;
	}
	else if((ticks>5)&&(ticks<9)){
		ticks++;
	}
	else{
		DcMotor_Rotate(STOP);
		ticks=0;
		Timer1_deInit();
	}

}

int main(void){
	SREG |= (1<<7) ;

	UART_ConfigType uartConfig={EIGHT_BIT,EVEN,ONE_BIT,9600};
	UART_init(&uartConfig);

	EEPROM_init();
	DcMotor_Init();
	Buzzer_init();
	checkPass();
	savePass();

	while(1)
	{
		uint8 status =getStatus();
		if(status==ENTER_PASS){
			comparePass();
		}
		else if(status==OPEN_DOOR){
			DcMotor_Rotate(CW);
			Timer1_init(&timer3sec);
			Timer1_setCallBack(controlMotor);
		}
		else if(status==RESET_PASS){
			checkPass();
			savePass();
		}
		else if(status==ALARM){
			Buzzer_on();
			_delay_ms(60000);
			Buzzer_off();
		}
		status=0;
	}
}
