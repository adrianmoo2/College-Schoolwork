#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


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

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum SM1_States { SM1_wait, SM1_press, SM1_release };

// Monitors button connected to PA0. 
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {

    // Local Variables
    unsigned char press = ~PINA & 0x01;

    //State machine transitions
    switch (state) {
    case SM1_wait:     if (press == 0x01) {    // Wait for button press
state = SM1_press;
}
break;

    case SM1_press:    state = SM1_release;
break;

    case SM1_release:    if (press == 0x00) {    // Wait for button release
state = SM1_wait;
}
break;

    default:        state = SM1_wait; // default: Initial state
                break;
    }

    //State machine actions
    switch(state) {
    case SM1_wait:    break;

    case SM1_press:    pause = (pause == 0) ? 1 : 0; // toggle pause
break;

    case SM1_release:    break;

    default:        break;
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
    case SM2_wait:    if (pause == 0) {    // If unpaused, go to blink state
state = SM2_blink;
}
break;

    case SM2_blink:    if (pause == 1) {    // If paused, go to wait state
state = SM2_wait;
}
break;

    default:        state = SM2_wait;
break;
    }

    //State machine actions
    switch(state) {
    case SM2_wait:    break;

    case SM2_blink:    SM2_output = (SM2_output == 0x00) ? 0x01 : 0x00; //toggle LED
break;

    default:        break;
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
    case SM3_wait:    if (pause == 0) {    // If unpaused, go to blink state
state = SM3_blink;
}
break;

    case SM3_blink:    if (pause == 1) {    // If paused, go to wait state
state = SM3_wait;
}
break;

    default:        state = SM3_wait;
                break;
    }

    //State machine actions
    switch(state) {
    case SM3_wait:    break;

    case SM3_blink:    SM3_output = (SM3_output == 0x00) ? 0x02 : 0x00; //toggle LED
                break;

    default:        break;
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
    case SM4_display:    break;

    default:        state = SM4_display;
                break;
    }

    //State machine actions
    switch(state) {
    case SM4_display:    output = SM2_output | SM3_output; // write shared outputs
                                    // to local variables
break;

    default:        break;
    }

    PORTB = output;    // Write combined, shared output variables to PORTB

    return state;
}


unsigned char GetKeypadKey() {

    PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('1'); }
    if (GetBit(PINC,1)==0) { return('4'); }
    if (GetBit(PINC,2)==0) { return('7'); }
    if (GetBit(PINC,3)==0) { return('*'); }

    // Check keys in col 2
    PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    if (GetBit(PINC,0)==0) { return('2'); }
    // ... *****FINISH*****

    // Check keys in col 3
    PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
    asm("nop"); // add a delay to allow PORTC to stabilize before checking
    // ... *****FINISH*****

    // Check keys in col 4    
    // ... *****FINISH*****

    return('\0'); // default value

}

int GetKeypad() {
	switch(state) {
		case Wait:
		
		PORTC = 0x7F;
		
		if (GetBit(PINC,0)==0) { state = A; }
		if (GetBit(PINC,1)==0) { state = B; }
		if (GetBit(PINC,2)==0) { state = C; }
		if (GetBit(PINC,3)==0) { state = D; }
		
		PORTC = 0xBF;

		if (GetBit(PINC,0)==0) { state = Three; }
		if (GetBit(PINC,1)==0) { state = Six; }
		if (GetBit(PINC,2)==0) { state = Nine; }
		if (GetBit(PINC,3)==0) { state = Pound; }
		
		PORTC = 0xDF;

		if (GetBit(PINC,0)==0) { state = Two; }
		if (GetBit(PINC,1)==0) { state = Five; }
		if (GetBit(PINC,2)==0) { state = Eight; }
		if (GetBit(PINC,3)==0) { state = Zero; }
			
		PORTC = 0xEF;
	
		if (GetBit(PINC,0)==0) { state = One; }
		if (GetBit(PINC,1)==0) { state = Four; }
		if (GetBit(PINC,2)==0) { state = Seven; }
		if (GetBit(PINC,3)==0) { state = Star; }
		break;
		
		case zero: 
		state = Wait;
		break;
		case one: 
		state = Wait;
		break;
		case two: 
		state = Wait;
		break;
		case three: 
		state = Wait;
		break;
		case four: 
		state = Wait;
		break;
		case five: 
		state = Wait;
		break;
		case six: 
		state = Wait;
		break;
		case seven: 
		state = Wait;
		break;
		case eight: 
		state = Wait;
		break;
		case nine: 
		state = Wait;
		break;
		case star: 
		state = Wait;
		break;
		case sharp: 
		state = Wait;
		break;
		case A: 
		state = Wait;
		break;
		case B: 
		state = Wait;
		break;
		case C: 
		state = Wait;
		break;
		case D: 
		state = Wait;
		break;

		}
		break;
		
		default: 
		state = 
		Wait;
		break;
	}

	}
	//PORTB = keypadValue;
	return state;
}



void Tick()
{
	unsigned char x;
	x = GetKeypadKey();
	
	switch (x) {
		    case '\0': PORTB = 0x1F; break; // All 5 LEDs on
		    case '1': PORTB = 0x01; break; // hex equivalent
		    case '2': PORTB = 0x02; break;

		    // . . . ***** FINISH *****

		    case 'D': PORTB = 0x0D; break;
		    case '*': PORTB = 0x0E; break;
		    case '0': PORTB = 0x00; break;
		    case '#': PORTB = 0x0F; break;
		    default: PORTB = 0x1B; break;
	}
}

int main(void)
{
    unsigned char x;
    DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
    DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    while(1) 
	{
		Tick();
    }
}
