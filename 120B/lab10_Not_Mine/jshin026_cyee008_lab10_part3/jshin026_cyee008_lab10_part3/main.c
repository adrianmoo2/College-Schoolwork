#include <avr/io.h>
#include <avr/interrupt.h>
#include <ucr/bit.h>
#include <ucr/timer.h>
#include <stdio.h>
#include "io.c"

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
unsigned char SM2_output = 0x00;
unsigned char SM3_output = 0x00;
unsigned char pause = 0;

unsigned char keypadValue = '\0';
unsigned char keypadInt = 0;

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.

enum GetKeypad_States {wait, zero, one, onewait, two, three, four, five, six, seven, eight, nine, 
						star, sharp, A, B, C, D}state;

int GetKeypad(int state) {
	//LCD_Cursor(1);

	switch(state) {
		case wait:
			PORTC = 0x7F;
			asm("nop");
			if (GetBit(PINC,0)==0) { state = A; }
			if (GetBit(PINC,1)==0) { state = B; }
			if (GetBit(PINC,2)==0) { state = C; }
			if (GetBit(PINC,3)==0) { state = D; }
			
				PORTC = 0xBF;
				asm("nop");
				if (GetBit(PINC,0)==0) { state = three; }
				if (GetBit(PINC,1)==0) { state = six; }
				if (GetBit(PINC,2)==0) { state = nine; }
				if (GetBit(PINC,3)==0) { state = sharp; }
			
			PORTC = 0xDF;
			asm("nop");
			if (GetBit(PINC,0)==0) { state = two; }
			if (GetBit(PINC,1)==0) { state = five; }
			if (GetBit(PINC,2)==0) { state = eight; }
			if (GetBit(PINC,3)==0) { state = zero; }
			PORTC = 0xEF;
			asm("nop");
			if (GetBit(PINC,0)==0) { state = one; }
			if (GetBit(PINC,1)==0) { state = four; }
			if (GetBit(PINC,2)==0) { state = seven; }
			if (GetBit(PINC,3)==0) { state = star; }
			
			break;
		case zero: state = wait; break;
		case one: state = wait;break;
		case two: state = wait;break;
		case three: state = wait;break;
		case four: state = wait;break;
		case five: state = wait;break;
		case six: state = wait;break;
		case seven: state = wait;break;
		case eight: state = wait;break;
		case nine: state = wait;break;
		case star: state = wait;break;
		case sharp: state = wait;break;
		case A: state = wait;break;
		case B: state = wait;break;
		case C: state = wait;break;
		case D: state = wait;break;
/*
		case onewait:
			if(!(GetBit(PINC,0)==0)){
				state = wait;
			} 
			break;
*/			
		default: state = wait;break;
	}

	switch(state) {
		case wait: 
			//if(keypadValue == '\0') {
			//	LCD_WriteData(keypadInt + '0');
			//}
			//else {
				//LCD_WriteData(5 + '0');
			//}
		break;//LCD_ClearScreen();break;

		case zero: keypadValue = (0 + '0');LCD_ClearScreen(); break;//LCD_WriteData(0 + '0'); break;
		case one: keypadValue = (1 + '0');LCD_ClearScreen(); break;//LCD_WriteData(1 + '0');break;
		case two: keypadValue = (2 + '0');LCD_ClearScreen(); break;//LCD_WriteData(2 + '0');break;
		case three: keypadValue = (3 + '0');LCD_ClearScreen(); break;//LCD_WriteData(3 + '0');break;
		case four: keypadValue = (4 + '0');LCD_ClearScreen(); break;//LCD_WriteData(4 + '0');break;
		case five: keypadValue = (5 + '0');LCD_ClearScreen(); break;//LCD_WriteData(5 + '0');break;
		case six: keypadValue = (6 + '0');LCD_ClearScreen(); break;//LCD_WriteData(6 + '0');break;
		case seven: keypadValue = (7 + '0');LCD_ClearScreen(); break;//LCD_WriteData(7 + '0');break;
		case eight: keypadValue = (8 + '0');LCD_ClearScreen(); break;//LCD_WriteData(8 + '0');break;
		case nine: keypadValue = (9 + '0');LCD_ClearScreen(); break;//LCD_WriteData(9 + '0');break;
		case star: keypadValue = ('*');LCD_ClearScreen(); break;//LCD_WriteData('*');break;
		case sharp: keypadValue = ('#');LCD_ClearScreen(); break;//LCD_WriteData('#');break;
		case A: keypadValue = ('A');LCD_ClearScreen(); break;//LCD_WriteData('A');break;
		case B: keypadValue = ('B');LCD_ClearScreen(); break;//LCD_WriteData('B' );break;
		case C: keypadValue = ('C');LCD_ClearScreen(); break;//LCD_WriteData('C' );break;
		case D: keypadValue = ('D');LCD_ClearScreen(); break;//LCD_WriteData('D');break;

		//case onewait: PORTB = 0x01;break;
		//case threewait: PORTB = 0x03;break;
		LCD_ClearScreen();
		default: break;//LCD_ClearScreen();break;

	}
	//PORTB = keypadValue;
	return state;
}
enum SM_ticks { display };
int SM_tick(int state){
	switch(state){
		case display: break;
		default: state = display; break;
	}
	switch(state){
		case display: LCD_Cursor(1);LCD_WriteData(keypadValue);
		break;
		default: break;
	}
	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
LCD_init();
//LCD_ClearScreen();
// Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
DDRA = 0xFF; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xF0; PORTC = 0x0F;
DDRD = 0xFF; PORTD = 0x00;

// . . . etc

// Period for the tasks
unsigned long int SMTick1_calc = 50;
unsigned long int SMTick2_calc = 10;

//Calculating GCD
unsigned long int tmpGCD = 1;
tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int SMTick1_period = SMTick1_calc/GCD;
unsigned long int SMTick2_period = SMTick2_calc/GCD;

//Declare an array of tasks 
static task task1, task2;
task *tasks[] = { &task1, &task2};
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

 //Task 1
task1.state = -1;//Task initial state.
task1.period = SMTick1_period;//Task Period.
task1.elapsedTime = SMTick1_period;//Task current elapsed time.
task1.TickFct = &GetKeypad;//Function pointer for the tick.

 //Task 2
 task2.state = -1;//Task initial state.
 task2.period = SMTick2_period;//Task Period.
 task2.elapsedTime = SMTick2_period;//Task current elapsed time.
 task2.TickFct = &SM_tick;//Function pointer for the tick.
//PORTB = 0xFF;

// Set the timer and turn it on
TimerSet(GCD);
TimerOn();
//LCD_ClearScreen();
unsigned short i; // Scheduler for-loop iterator
while(1) {
//LCD_ClearScreen();
	// Scheduler code
	for ( i = 0; i < numTasks; i++ ) {
		// Task is ready to tick
		if ( tasks[i]->elapsedTime == tasks[i]->period ) {
			// Setting next state for task
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			// Reset the elapsed time for next tick.
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
	
	//GetKeypad();
}

// Error: Program should not exit!
return 0;
}
