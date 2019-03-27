/*
 * Atran_Atruo_LED_Matrix.c
 *
 * Created: 10/24/2018 6:20:46 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include "scheduler.h"

enum LED_States {shiftOne, shiftTwo, shiftThree, shiftFour};
	
int index = 0;

static unsigned char row_array[4] = {0xBF, 0xDF, 0xEF, 0xF7};
static unsigned char pattern_array[4] = {0x7C, 0x44, 0x44, 0x7C};

int LED_Tick(int state)
{	
	unsigned A0 = ~PINA & 0x01; // shift up
	unsigned A1 = ~PINA & 0x02; // shift down
	
	switch(state)
	{
		case shiftOne:
			state = shiftTwo;
			break;
		case shiftTwo:
			state = shiftThree;
			break;
		case shiftThree:
			state = shiftFour;
			break;
		case shiftFour:
			state = shiftOne;
			break;
		default:
			state = shiftOne;
			break;
	}
	
	switch(state)
	{
		case shiftOne:
			index = 0;
			break;
		case shiftTwo:
			index = 1;
			break;
		case shiftThree:
			index = 2;
			break;
		case shiftFour:
			index = 3;
			break;
		default:
			index = 0;
			break;
	}
	
	PORTC = pattern_array[index];
	PORTC = row_array[index];
	return state;
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
	tasks[i].period = 25;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &LED_Tick;
	
	TimerSet(25);
	TimerOn();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

