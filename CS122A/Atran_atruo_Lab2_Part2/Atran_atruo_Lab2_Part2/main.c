/*
 * atran_atruo_lab2_section1.c
 *
 * Created: 10/4/2018 9:05:34 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>
#include "usart_ATmega1284.h"
#include "scheduler.h"


volatile unsigned char PORTA_TEMP = 0x00;
volatile unsigned char PORTC_TEMP = 0x00;
unsigned char temp;
char led_state = 0x01;

int isLeader = 0;

enum USART_States {Wait, Init, LED_On, LED_Off};
	
enum LEADER_STATES {Send};
	
int TickFct_Receive(int state)
{
	unsigned char B0 = ~PINB & 0x01;
	if (B0 == 0x01)
	{
		PORTC_TEMP = 0x01;
		isLeader = 1;
	}
	else {
		PORTC_TEMP = 0x00;
		isLeader = 0;
	}
	if (isLeader ==  0)
	{
		switch (state)
		{
			case -1:
				state = Init;
			break;
			case Init:
				state = Wait;
			break;
			case Wait:
				if (USART_HasReceived(0))
				{
					state = LED_On;
				}
				else
				{
					state = LED_Off;
				}
			break;
			case LED_On:
				if (!USART_HasReceived(0))
				{
					state = Wait;
				}
			break;
			case LED_Off:
				if (USART_HasReceived(0))
				{
					state = LED_On;
				}			
			break;
			default:
				state = -1;
		}
	
		switch(state)
		{
			case -1:
			break;
			case Init:
				PORTA_TEMP = 0x00;
			break;
			case Wait:
				USART_Flush(0);
			break;
			case LED_On:
				temp = USART_Receive(0);
				PORTA_TEMP = temp;
				//PORTA = 0xFF;
			break;
			case LED_Off:
				PORTA_TEMP = 0x00;
			break;
			default:
				state = -1;
		}
	
		PORTA = PORTA_TEMP;
		PORTC = PORTC_TEMP;
	}
	return state;
}

int tick(int state) {
	unsigned char B0 = ~PINB & 0x01;
	if (B0 == 0x01)
	{
		PORTC_TEMP = 0x01;
		isLeader = 1;
	}
	else {
		PORTC_TEMP = 0x00;
		isLeader = 0;
	}
	if (isLeader == 1)
	{
	
		switch(state) {
			case -1:
				state = Send;
			break;
			case Send:
			break;
			default:
			state = -1;
			break;
			return state;
		}
	
		switch(state)
		{
			case -1:
			break;
			case Send:
				if (USART_IsSendReady(1)) {
					USART_Send(led_state, 1);
					if (USART_HasTransmitted(1)) {
						PORTA = led_state;
						led_state = ~led_state;
					}
				}
			break;
			default:
				state = -1;
		}
	
			PORTC = PORTC_TEMP;
		}
	return state;
}


int main(void)
{
	//initialize ports
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	//initialize uSART
    initUSART(0);
	initUSART(1);
	
	tasksNum = 2;
	task tsks[2];
	tasks = tsks;
	
	//define tasks
	unsigned char i = 0;
	tasks[i].state = -1;
	tasks[i].period = 600;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Receive;
	
	++i;
	
	tasks[i].state = -1;
	tasks[i].period = 1000;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &tick;
	
	const unsigned int period_sm_1 = 100;
	TimerSet(period_sm_1);
	TimerOn();
	
	
    while (1) 
    {
    }
}

