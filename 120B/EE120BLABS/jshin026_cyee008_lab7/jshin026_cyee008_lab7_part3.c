/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 
 #include <avr/io.h>
 #include <avr/interrupt.h>

enum states {start, one, two, three} state;
enum states2 {start2, one2, two2, three2} state2;
enum soundState {start4, soundOff, soundOn} state4;

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

unsigned char pat1 = 0xFF;
unsigned char pat2 = 0xFF;
unsigned char pat4 = 0xFF;

void part1()
{
	
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
			state = one;
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
			pat1 = tmpB0;
			//PORTB = pat1 | pat2;
			//while (!TimerFlag);	// Wait 1 sec
			//TimerFlag = 0;
			break;
		case two:
			tmpB1 = ~tmpB1;	// Toggle PORTB; Temporary, bad programming style
			pat1 = tmpB1;
			//PORTB = pat1 | pat2;
			//while (!TimerFlag);	// Wait 1 sec
			//TimerFlag = 0;
			break;
		case three:
			tmpB2 = ~tmpB2;	// Toggle PORTB; Temporary, bad programming style
			pat1 = tmpB2;
			//PORTB = pat1 | pat2;
			//while (!TimerFlag);	// Wait 1 sec
			//TimerFlag = 0;
			break;
		default:
			break;
	}
}


void part2()
{
	
	unsigned tmpB3 = 0x07;
	
	switch(state2) {
		case start2:
			state2 = one2;
			break;
		case one2:
			state2 = start2;
			break;
		default:
			state2 = start2;
			break;
	}
	
	switch(state2) {
		case start2:
			pat2 = 0x00;
			//PORTB = pat1 | pat2;
			break;
		case one2:
			tmpB3 = 0x08;	// Toggle PORTB; Temporary, bad programming style
			pat2 = tmpB3;
			//PORTB = pat1 | pat2;
			break;
		default:
			break;
	}
}

void part3()
{
	PORTB = pat1 | pat2 | pat4;
}

void part4()
{
	//unsigned tmpA2 = 0xFB;
	unsigned tmpA2 = ~PINA & 0x04;
	unsigned tmpB4 = 0xEF;

	switch(state4) {
		case start4:
			if(tmpA2) {
				state4 = soundOff;
			}
			else {
				state4 = start4;
			}
			break;
		case soundOff:
			if(tmpA2) {
				state4 = soundOn;
			}
			else {
				state4 = start4;
			}
			break;
		case soundOn:
			if(tmpA2) {
				state4 = soundOff;
			}
			else {
				state4 = start4;
			}
			break;
		default:
			state4 = start4;
			break;
	}

	switch(state4) {
		case start4:
			break;
		case soundOff:
			tmpB4 = 0x00;
			pat4 = tmpB4;
			break;
		case soundOn:
			tmpB4 = 0x10;
			pat4 = tmpB4;
			break;
		default:
			break;
	}
}

int main(void)
{
	unsigned long BL_elapsedTime = 1000;
	unsigned long TL_elapsedTime = 300;
	unsigned long sound_elapsedTime = 2;
	const unsigned long timerPeriod = 2;

	//B = 0;
	TimerSet(timerPeriod);
	//TimerSet(1000);
	TimerOn();
	DDRB = 0xFF; PORTB = 0x00; // LCD control lines
	DDRA = 0x00; PORTA = 0xFF;

	state = start;
	state2 = start2;
	//state3 = start3;
	state4 = start4;
	while(1) {
		if(TL_elapsedTime >= 300){
			part1();
			TL_elapsedTime = 0;
		}
		if (BL_elapsedTime >=1000) {
			part2();
			
			BL_elapsedTime = 0;
		}
		if (sound_elapsedTime >= 2) {
			part4();
			sound_elapsedTime = 0;
		}

		part3();
		while(!TimerFlag){}
		TimerFlag = 0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		sound_elapsedTime += timerPeriod;
	}
}
