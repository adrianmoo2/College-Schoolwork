/*
 * TEST3.c
 *
 * Created: 2/28/2018 12:05:09 AM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

enum SW_States {SW_Start, SW_Init, SW_Up, SW_Down} SW_state;
enum ON_States {ON_Start, ON_Init, ON_On, ON_StayOn, ON_Off} ON_state;
double freq = 0;

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

void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64                    // 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void incFreq()
{
	if (freq == 261.63)
	{
		freq = 293.66;
	}
	else if (freq == 293.66)
	{
		freq = 329.63;
	}
	else if (freq == 329.63)
	{
		freq = 349.23;
	}
	else if (freq == 349.23)
	{
		freq = 392.00;
	}
	else if (freq == 392.00)
	{
		freq = 440.00;
	}
	else if (freq == 440.00)
	{
		freq = 493.88;
	}
	else if (freq == 493.88)
	{
		freq = 523.25;
	}
}

void decFreq()
{
	if (freq == 523.25)
	{
		freq = 493.88;
	}
	else if (freq == 493.88)
	{
		freq = 440.00;
	}
	else if (freq == 440.00)
	{
		freq = 392.00;
	}
	else if (freq == 392.00)
	{
		freq = 349.23;
	}
	else if (freq == 349.23)
	{
		freq = 329.63;
	}
	else if (freq == 329.63)
	{
		freq = 293.66;
	}
	else if (freq == 293.66)
	{
		freq = 261.63;
	}
	
}

void ON_Tick()
{
	unsigned char A0 = ~PINA & 0x01;
	
	switch(ON_state)
	{
		case ON_Start:
			ON_state = ON_Init;
			break;
		case ON_Init:
			ON_state = A0 ? ON_On : ON_state;
			break;
		case ON_On:
			ON_state = A0 ? ON_Off : ON_StayOn;
			break;
		case ON_StayOn:
			ON_state = A0 ? ON_Off : ON_state;
			break;
		case ON_Off:
			ON_state = ON_Init;
			break;
	}
	
	switch (ON_state)
	{
		case ON_Start:
			break;
		case ON_Init:
			break;
		case ON_On:
			PWM_on();
			freq = 261.63;
			set_PWM(freq);
			break;
		case ON_StayOn:
			break;
		case ON_Off:
			PWM_off();
			break;
	}
}

void SW_Tick()
{
	unsigned char A1 = ~PINA & 0x02;
	unsigned char A2 = ~PINA & 0x04;
	
	switch(SW_state)
	{
		case SW_Start:
			SW_state = SW_Init;
			break;
		case SW_Init:
			SW_state = A1 ? SW_Up : SW_state;
			SW_state = A2 ? SW_Down : SW_state;
			break;
		case SW_Up:
			SW_state = SW_Init;
			break;
		case SW_Down:
			SW_state = SW_Init;
			break;
	}
	
	switch(SW_state)
	{
		case SW_Start:
			break;
		case SW_Init:
			break;
		case SW_Up:
			incFreq();
			set_PWM(freq);
			break;
		case SW_Down:
			decFreq();
			set_PWM(freq);
			break;
	}
}

void main()
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	
	
	SW_state = SW_Start;
	ON_state = ON_Start;
	
	const unsigned long timerPeriod = 100;
	
	unsigned long SW_elapsedTime = 0;
	unsigned long ON_elapsedTime = 0;
	
	TimerSet(100);
	TimerOn();
	
	while (1)
	{
		if (ON_elapsedTime >= 200)
		{	
			ON_Tick();
			ON_elapsedTime = 0;
		}
		if (SW_elapsedTime >= 200)
		{
			SW_Tick();
			SW_elapsedTime = 0;
		}
		while (!TimerFlag) {}
			TimerFlag = 0;
			ON_elapsedTime += timerPeriod;
			SW_elapsedTime += timerPeriod;
	}
}