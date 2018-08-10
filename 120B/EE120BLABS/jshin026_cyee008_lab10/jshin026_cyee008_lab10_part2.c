/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include "io.c"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <ucr/bit.h>
#include <ucr/timer.h>
#include <stdio.h>

//--------Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

//--------End Task scheduler data structure-----------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char pause = 0;
unsigned char counter = 16;
unsigned char legendString[] = "CS120B is Legend... wait for it DARY!";
unsigned char* index = legendString;

unsigned char keypadValue = '\0';

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.


enum lcd_states{start}state;

int lcd_tick(int state){
LCD_ClearScreen();
//LCD_Cursor(16);
	switch(state){
		case start: break;
		default: state = start;break;
	}
	switch(state){
		case start: LCD_DisplayString(1, index);// *counter--;break;
		if(*index == '\0') {
			index = legendString;
		}
		else {
			index++;
		}
		break;
		default: break;
	}
	//PORTB = ~PORTB;
	//counter = counter - 1;
		//if(counter < -32){
			//counter = 16;
		//}

	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{

// Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
DDRA = 0xFF; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xF0; PORTC = 0x0F;
DDRD = 0xFF; PORTD = 0x00;

//LCD_ClearScreen();
LCD_init();
LCD_ClearScreen();

// . . . etc

// Period for the tasks
unsigned long int SMTick1_calc = 900;

//Calculating GCD
unsigned long int tmpGCD = 1;

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int SMTick1_period = 300;// SMTick1_calc/GCD;


//Declare an array of tasks 
static task task1;
task *tasks[] = {&task1};
const unsigned short numTasks = 1;//sizeof(tasks)/sizeof(task*);

 task1.state = start;//Task initial state.
 task1.period = SMTick1_period;//Task Period.
 task1.elapsedTime = SMTick1_period;//Task current elapsed time.
 task1.TickFct = &lcd_tick;//Function pointer for the tick.

unsigned short i; // Scheduler for-loop iterator
//LCD_ClearScreen(void);
//	LCD_DisplayString(-10, "Legend ...wait for it DARY!");


TimerSet(300);
TimerOn();
while(1) {

//LCD_DisplayString(1 ,"huashdusaid");


	// Scheduler code
	for ( i = 0; i < numTasks; i++ ) {
		// Task is ready to tick
		if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
			// Setting next state for task
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			// Reset the elapsed time for next tick.
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 300;
		//--counter;
	}
	
	//	lcd_tick();

	while(!TimerFlag);
	TimerFlag = 0;
	

}

// Error: Program should not exit!
return 0;
}
