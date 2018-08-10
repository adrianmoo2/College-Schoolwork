
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
unsigned char SM2_output = 0x00;
unsigned char SM3_output = 0x00;
unsigned char pause = 0;
unsigned char counter = 16;

unsigned char keypadValue = '\0';

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.

enum GetKeypad_States {wait, zero, one, onewait, two, three, four, five, six, seven, eight, nine, 
						star, sharp, A, B, C, D}state;

int GetKeypad() {
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
		case zero: state = wait;break;
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

		case onewait:
			if(!(GetBit(PINC,0)==0)){
				state = wait;
			} 
			break;
			
		default: state = wait;break;
	}

	switch(state) {
		case wait: PORTB = 0xFF;break;

		case zero: PORTB = 0x00;break;
		case one: PORTB = 0x01;break;
		case two: PORTB = 0x02;break;
		case three: PORTB = 0x03;break;
		case four: PORTB = 0x04;break;
		case five: PORTB = 0x05;break;
		case six: PORTB = 0x06;break;
		case seven: PORTB = 0x07;break;
		case eight: PORTB = 0x08;break;
		case nine: PORTB = 0x09;break;
		case star: PORTB = 0x0E;break;
		case sharp: PORTB = 0x0F;break;
		case A: PORTB = 0x0A;break;
		case B: PORTB = 0x0B;break;
		case C: PORTB = 0x0C;break;
		case D: PORTB = 0x0D;break;

		//case onewait: PORTB = 0x01;break;
		//case threewait: PORTB = 0x03;break;

		default: keypadValue = '\0';break;

	}
	//PORTB = keypadValue;
	return state;
}


enum lcd_states{start};

int lcd_tick(int state){
//LCD_Cursor(16);
	switch(state){
		case start: break;
		default: state = start;break;
	}
	switch(state){
		case start: LCD_DisplayString(counter, " CS120B is Legend... wait for it DARY!");break;
		default: break;
	}
	PORTB = ~PORTB;
	counter = counter - 1;
	return state;
}

enum SM1_States { SM1_wait, SM1_press, SM1_release };

// Monitors button connected to PA0. 
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {

	// Local Variables
	unsigned char press = ~PINA & 0x01;

	//State machine transitions
	switch (state) {
	case SM1_wait: 	if (press == 0x01) {	// Wait for button press
state = SM1_press;
}
break;

	case SM1_press:	state = SM1_release;
break;

	case SM1_release:	if (press == 0x00) {	// Wait for button release
state = SM1_wait;
}
break;

	default:		state = SM1_wait; // default: Initial state
				break;
	}

	//State machine actions
	switch(state) {
	case SM1_wait:	break;

	case SM1_press:	pause = (pause == 0) ? 1 : 0; // toggle pause
break;

	case SM1_release:	break;

	default:		break;
	}

	return state;
}

//Enumeration of states.
enum SM2_States { SM2_wait, SM2_blink };

// If paused: Do NOT toggle LED connected to PB0
// If unpaused: toggle LED connected to PB0
int SMTick2(int state) {

	//State machine transitions
	switch (state) {
	case SM2_wait:	if (pause == 0) {	// If unpaused, go to blink state
state = SM2_blink;
}
break;

	case SM2_blink:	if (pause == 1) {	// If paused, go to wait state
state = SM2_wait;
}
break;

	default:		state = SM2_wait;
break;
	}

	//State machine actions
	switch(state) {
	case SM2_wait:	break;

	case SM2_blink:	SM2_output = (SM2_output == 0x00) ? 0x01 : 0x00; //toggle LED
break;

	default:		break;
	}

	return state;
}

//Enumeration of states.
enum SM3_States { SM3_wait, SM3_blink };

// If paused: Do NOT toggle LED connected to PB1
// If unpaused: toggle LED connected to PB1
int SMTick3(int state) {
	//State machine transitions
	switch (state) {
	case SM3_wait:	if (pause == 0) {	// If unpaused, go to blink state
state = SM3_blink;
}
break;

	case SM3_blink:	if (pause == 1) {	// If paused, go to wait state
state = SM3_wait;
}
break;

	default:		state = SM3_wait;
				break;
	}

	//State machine actions
	switch(state) {
	case SM3_wait:	break;

	case SM3_blink:	SM3_output = (SM3_output == 0x00) ? 0x02 : 0x00; //toggle LED
				break;

	default:		break;
	}

	return state;
}


//Enumeration of states.
enum SM4_States { SM4_display };

// Combine blinking LED outputs from SM2 and SM3, and output on PORTB
int SMTick4(int state) {
	// Local Variables

	unsigned char output;

	//State machine transitions
	switch (state) {
	case SM4_display:	break;

	default:		state = SM4_display;
				break;
	}

	//State machine actions
	switch(state) {
	case SM4_display:	output = SM2_output | SM3_output; // write shared outputs
									// to local variables
break;

	default:		break;
	}

	PORTB = output;	// Write combined, shared output variables to PORTB

	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
LCD_init();

// Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
DDRA = 0xFF; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xF0; PORTC = 0x0F;
DDRD = 0xFF; PORTD = 0x00;

// . . . etc

// Period for the tasks
unsigned long int SMTick1_calc = 1000;
unsigned long int SMTick2_calc = 500;
unsigned long int SMTick3_calc = 1000;
unsigned long int SMTick4_calc = 10;

//Calculating GCD
unsigned long int tmpGCD = 1;
//tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
//tmpGCD = findGCD(tmpGCD, SMTick3_calc);
//tmpGCD = findGCD(tmpGCD, SMTick4_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int SMTick1_period = SMTick1_calc/GCD;
unsigned long int SMTick2_period = SMTick2_calc/GCD;
unsigned long int SMTick3_period = SMTick3_calc/GCD;
unsigned long int SMTick4_period = SMTick4_calc/GCD;

//Declare an array of tasks 
static task task1, task2, task3, task4;
task *tasks[] = { &task1, &task2, &task3, &task4};
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
/*
 //Task 1
task1.state = -1;//Task initial state.
task1.period = SMTick1_period;//Task Period.
task1.elapsedTime = SMTick1_period;//Task current elapsed time.
task1.TickFct = &GetKeypad;//Function pointer for the tick.
//PORTB = 0xFF;
*/
 //Task 1
 task1.state = -1;//Task initial state.
 task1.period = SMTick1_period;//Task Period.
 task1.elapsedTime = SMTick1_period;//Task current elapsed time.
 task1.TickFct = &lcd_tick;//Function pointer for the tick.
/*
// Task 1
task1.state = -1;//Task initial state.
task1.period = SMTick1_period;//Task Period.
task1.elapsedTime = SMTick1_period;//Task current elapsed time.
task1.TickFct = &SMTick1;//Function pointer for the tick.

// Task 2
task2.state = -1;//Task initial state.
task2.period = SMTick2_period;//Task Period.
task2.elapsedTime = SMTick2_period;//Task current elapsed time.
task2.TickFct = &SMTick2;//Function pointer for the tick.

// Task 3
task3.state = -1;//Task initial state.
task3.period = SMTick3_period;//Task Period.
task3.elapsedTime = SMTick3_period; // Task current elasped time.
task3.TickFct = &SMTick3; // Function pointer for the tick.

// Task 4
task4.state = -1;//Task initial state.
task4.period = SMTick4_period;//Task Period.
task4.elapsedTime = SMTick4_period; // Task current elasped time.
task4.TickFct = &SMTick4; // Function pointer for the tick.

// Set the timer and turn it on
TimerSet(GCD);
TimerOn();
*/
unsigned short i; // Scheduler for-loop iterator
//LCD_ClearScreen(void);
//	LCD_DisplayString(-10, "Legend ...wait for it DARY!");
while(1) {

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
		--counter;
		if(counter < -37){
			counter = 5;
		}
	}
	while(!TimerFlag);
	TimerFlag = 0;
	//counter--;
	/*if(counter < -37){
		counter = 16;
	}*/
	//GetKeypad();
	//LCD_Cursor(10);
}

// Error: Program should not exit!
return 0;
}
