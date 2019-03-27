/*
 * Atran_atruo_lab3_part1.c
 *
 * Created: 10/17/2018 6:44:58 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include "bit.h"
#include "keypad.h"
#include "lcd.h"
#include "scheduler.h"

char pattern_Value = 0x00;
char speed_Value = 0x00;
char data = 0x00;

enum TickStates {wait, send};

void SPI_MasterInit(void) {
	/* Set MOSI and SCK output, all others input */
	DDRB = 0xD0;
		//PB7 = MOSI
		//PB6 = SCK
		//PB5 = SS
		//PB4-0 = input
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(unsigned char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

int tick(int state) {
	switch(state) {
		case -1:
			state = wait;
		break;
		case wait:
			if (GetKeypadKey() != '\0')
			{
				state = send;
			}
		break;
		case send:
		break;
		default:
		state = -1;
		break;
	}
	
	switch(state){
		case -1:
		break;
		case wait:
		break;
		case send:
			if (GetKeypadKey() == 'A || GetKeypadKey() == 'B' || G)
			{
			}

		break;
		default:
		break;
	}
	
}

int main(void)
{
    /* Replace with your application code */
	tasksNum = 1; // declare number of tasks
	task tsks[1]; // initialize the task array
	tasks = tsks; // set the task array
	
	// define tasks
	unsigned char i=0; // task counter
	tasks[i].state = -1;
	tasks[i].period = 1000;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &tick;
	
	TimerSet(1000);
	TimerOn();
	
	SPI_MasterInit();
	
    while (1) 
    {
    }
}

