/*
 * ATRAN059_LAB5_PART1.c
 *
 * Created: 2/1/2018 3:57:38 PM
 *  Author: student
 */ 


#include <avr/io.h>
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks	
enum States {Start, Init, Wait, SwitchOne, SwitchTwo, SwitchThree} state;
enum States2 {Start2, Init2, Wait2, SwitchOne2, SwitchTwo2, SwitchThree2} state2;
//enum States3 {Start3, Init3, Wait3, SwitchOne3, SwitchTwo3, SwitchThree3} state3;
//enum SPKStates {SPKStart, SPKInit, SPKOn, SPKOff} SPKState;

unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char combineLED;
	
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void TimerISR() {
	TimerFlag = 1;
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

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

void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64                    // 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

	
void Tick() {
		switch (state) {
		case Start:
			state = Init;
			break;
		case Init:
			state = Wait;
			break;
		case Wait:
			state = GetBit(PINA, 0) ? SwitchOne : state; 
			state = GetBit(PINA, 1) ? SwitchTwo : state;
			state = GetBit(PINA, 2) ? SwitchThree: state;
			break;
		case SwitchOne:
			state = Wait;
			break;
		case SwitchTwo:
			state = Wait;
			break;
		case SwitchThree:
			state = Wait;
			break;
		default:
			break;
	}
	
	switch (state) {
		case Start:
			break;
		case Init:
			break;
		case Wait:
			break;
		case SwitchOne:
			break;
		case SwitchTwo:
			set_PWM(293.66);
			break;
		case SwitchThree:
			set_PWM(329.63);
			break;
		default:
			break;
	}
	

	
	
}

/*void BL_Tick()
{
			switch (state2) {
				case Start:
				state2 = Init;
				break;
				case Init:
				state2 = Wait;
				break;
				case Wait:
				state2 = blinkingLED = 0x00 ? SwitchOne : state2;
				state2 = blinkingLED == 0x08 ? SwitchTwo : state2;
				state2 = blinkingLED == 0x01 ? SwitchOne: state2;
				break;
				case SwitchOne:
				break;
				case SwitchTwo:
				break;
				case SwitchThree:
				break;
				default:
				break;
			}
			
			switch (state2) {
				case Start:
				break;
				case Init:
				blinkingLED = 0x00;
				break;
				case Wait:
				break;
				case SwitchOne:
				blinkingLED = 0x08;
				break;
				case SwitchTwo:
				threeLEDs = 0x01;
				break;
				case SwitchThree:
				break;
				default:
				break;
			}
}

void CB_Tick()
{
					switch (state3) {
						case Start:
						state3 = Init;
						break;
						case Init:
						break;
						default:
						break;
					}
					switch (state3) {
						case Start:
						combineLED = 0x00;
						break;
						case Init:
						combineLED = threeLEDs | blinkingLED;
						PORTB = combineLED;
						break;
						default:
						break;
					}
}

void SP_Tick()
{
	switch (SPKStates)
	{
		case Start:
			SPKState = Init;
			break;
		case Init:
			SPKState = GetBit(PINA, 2) ? SPKOn : SPKOff;
			break;
		case SPKOn:
			SPKState = Init;
			break;
		case SPKOff:
			SPKState = Init;
			break;
		default:
			break;
		
			
		case Start:
			break;
		case Init:
			break;
		case SPKOn:
			PORTB = SetBit(PORTB, 4, 1);
			break;
		case SPKOff:
			PORTB = SetBit(PORTB, 4, 0);
			break;
			default:
			break;
	}
}*/



int main(void)
{
	state = Start;
	DDRA = 0x00; PINA = 0xFF;
	DDRB = 0xFF; PINB = 0x00;
    while(1)
    {

        Tick();
		/*while (!TimerFlag) {}
		TimerFlag = 0;*/
    }
}