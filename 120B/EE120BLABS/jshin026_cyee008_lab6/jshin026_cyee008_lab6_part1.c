#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//volatile unsigned char TimerFlag = 0;

//void TimerISR(){
//	TimerFlag = 1;
//}

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

enum States{Start, Increment, Increment_wait, Decrement, Decrement_wait, Reset} State;
unsigned char count = 0;

void Latch(){
	TimerSet(1000);
	TimerOn();
	//while (!TimerFlag);	// Wait 1 sec
	//TimerFlag = 0;
	unsigned char A0 = ~PINA & 0x01;
	unsigned char A1 = ~PINA & 0x02;
	switch(State) {
		case Start:
			if(A0){
				State = Increment;
			}
			else if(A1){
				State = Decrement;
			}
			break;
		case Increment:
			while (!TimerFlag);	// Wait 1 sec
			TimerFlag = 0;
			A0 = ~PINA & 0x01;
			A1 = ~PINA & 0x02;
			if(A1 && A0){
				State = Reset;
			}
			else if(A0){
				State = Increment_wait;
			}
			else if(!A0){
				State = Start;
			}
			break;
		case Increment_wait:
		while (!TimerFlag);	// Wait 1 sec
		TimerFlag = 0;
		A0 = ~PINA & 0x01;
		A1 = ~PINA & 0x02;
			if(!A0){
				State = Start;
			}
			else if(A0 && A1){
				State = Reset;
				//LCD_DisplayString(1, "hello");
			}
			break;
			
		case Decrement:
		while (!TimerFlag);	// Wait 1 sec
		TimerFlag = 0;
		A0 = ~PINA & 0x01;
		A1 = ~PINA & 0x02;
			if(!A1){
				State = Start;
			}
			else if(A0 && A1){
				State = Reset;
				//LCD_DisplayString(1, "byebye");
			}
			else if(A1){
				State = Decrement_wait;
			}
			break;
			
		case Decrement_wait:
		while (!TimerFlag);	// Wait 1 sec
		TimerFlag = 0;
		A0 = ~PINA & 0x01;
		A1 = ~PINA & 0x02;
			if(!A1){
				State = Start;
			}
			else if(A1 && A0){
			//LCD_DisplayString(1, "byebye");
				State = Reset;

			}
			break;
			
		case Reset:
			if(!A1 && !A0){
				State = Start;
			}
			break;
		default:
			State = Start;
			break;
	}
	switch(State){
		case Start:
			break;
		case Increment:
		if(count < 9) {
			++count;
		}
		//while (!TimerFlag);	// Wait 1 sec
		//TimerFlag = 0;
			break;
		case Increment_wait:
						
						//while (!TimerFlag);	// Wait 1 sec
						//TimerFlag = 0;
						if(count < 9) {
							++count;
						}
			break;
		case Decrement:
			if(count > 0) {
				--count;
			}
			//while (!TimerFlag);	// Wait 1 sec
			//TimerFlag = 0;
			break;
		case Decrement_wait:
						
						//while (!TimerFlag);	// Wait 1 sec
						//TimerFlag = 0;
						if(count > 0) {
							--count;
						}
			break;
		case Reset:
			 count = 0;
			 break;
		default:
			count = 0;
			break;
	}
	//PORTC = count;
	//LCD_WriteData(count);
	LCD_WriteData(count + '0');
	LCD_Cursor(1);
	//while (!TimerFlag);	// Wait 1 sec
	//TimerFlag = 0;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	

	// Initializes the LCD display
	LCD_init();
	
	// Starting at position 1 on the LCD screen, writes Hello World
	//LCD_DisplayString(1, "0");
	State = Start;
	LCD_ClearScreen();
	while(1) {
		Latch();
		//LCD_DisplayString(1, );
	}
}