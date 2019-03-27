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

char SPI_receivedData = 0x00;


void SPI_ServantInit(void) {
	// set DDRB to have MISO line as output and MOSI, SCK, and SS as input
	DDRB = 0x80;
		//PB7 = MISO
		//PB6 = SCK
		//PB5 = SS
	// set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
	// make sure global interrupts are enabled on SREG register (pg. 9)
}


ISR(SPI_STC_vect) { // this is enabled in with the SPCR register’s “SPI
	// Interrupt Enable”
	// SPDR contains the received data, e.g. unsigned char receivedData =
	// SPDR;
}

char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}


int servantTick(int state) {
	switch(state) {
		case -1:
			SPI_receivedData = SPI_SlaveReceive();
			PORTB = SPI_receivedData;
		break;
		default:
		state = -1;
		break;
		return state;
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
	tasks[i].TickFct = &servantTick;
	
	TimerSet(1000);
	TimerOn();
	
	SPI_ServantInit();
	
    while (1) 
    {
    }
}

