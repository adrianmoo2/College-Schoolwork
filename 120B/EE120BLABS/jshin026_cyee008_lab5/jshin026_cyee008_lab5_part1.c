/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

enum states {start, one, two, three} state;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void part1()
{
	TimerSet(1000);
	TimerOn();
	
	unsigned tmpB0 = 0xFE;
	unsigned tmpB1 = 0xFD;
	unsigned tmpB2 = 0xFB;
	
	switch(state) {
		case start:
			state = one;
			break;
		case one:
			state = two;
			break;
		case two:
			state = three;
			break;
		case three:
			state = start;
			break;
		default:
			state = start;
			break;
	}
	
	switch(state) {
		case start:
			break;
		case one:
			tmpB0 = ~tmpB0;	// Toggle PORTB; Temporary, bad programming style
			PORTB = tmpB0;
			while (!TimerFlag);	// Wait 1 sec
			TimerFlag = 0;
			break;
		case two:
			tmpB1 = ~tmpB1;	// Toggle PORTB; Temporary, bad programming style
			PORTB = tmpB1;
			while (!TimerFlag);	// Wait 1 sec
			TimerFlag = 0;
			break;
		case three:
			tmpB2 = ~tmpB2;	// Toggle PORTB; Temporary, bad programming style
			PORTB = tmpB2;
			while (!TimerFlag);	// Wait 1 sec
			TimerFlag = 0;
			break;
		default:
			break;
	}
}

int main(void) {
	DDRB = 0xFF;
	PORTB = 0xFF;
	while(1) {
		part1();
	}
}

/*void main()
{
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
	while(1) {
		// User code (i.e. synchSM calls)
		tmpB = ~tmpB;	// Toggle PORTB; Temporary, bad programming style
		PORTB = tmpB;
		while (!TimerFlag);	// Wait 1 sec
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
}*/