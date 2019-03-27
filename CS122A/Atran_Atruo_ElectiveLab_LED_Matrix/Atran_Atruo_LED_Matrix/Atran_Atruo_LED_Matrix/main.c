/*
 * Atran_Atruo_LED_Matrix.c
 *
 * Created: 10/24/2018 6:20:46 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include "scheduler.h"

enum LED_States {checkButton, shiftUp, shiftDown};

int LED_Tick(int state)
{
	static unsigned char pattern = 0xFF;
	static unsigned char row = 0xFE;
	
	unsigned A0 = ~PINA & 0x01; // shift up
	unsigned A1 = ~PINA & 0x02; // shift down
	
	switch(state)
	{
		case checkButton:
			state = A0 ? shiftUp : state;
			state = A1 ? shiftDown: state;
			break;
		case shiftUp:
			state = A0 ? shiftUp : checkButton;
			break;
		case shiftDown:
			state = A1 ? shiftDown: checkButton;
			break;
		default:
			state = checkButton;
			break;
	}
	
	switch(state)
	{
		case checkButton:
			break;
		case shiftUp:
			if (row >= 0xBF)
			{
				row = (row << 1) | 0x01;
			}
			break;
		case shiftDown:
			if (row <= 0xFD)
			{
				row = (row >> 1) | 0x01;
			}
			break;
		default:
			break;
	}
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	tasksNum = 2;
	task tsks[1];
	tasks = tsks;
	
	unsigned char i = 0;
	tasks[i].state = -1;
	tasks[i].period = 100;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &LED_Tick;
	
	TimerSet(100);
	TimerOn();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

