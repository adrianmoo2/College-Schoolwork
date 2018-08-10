/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
//NOTE*** THIS NEW CODE TARGETS PB6 NOT PB3

void set_PWM(double frequency) {
	
	
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency
	// changes, plays music uninterrupted.
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; //stops timer/counter
		else TCCR3B |= 0x03; // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) OCR3A = 0xFFFF;
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) OCR3A = 0x0000;
		
		// set OCR3A based on desired frequency
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; // resets counter
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
enum states{start, wait, cat, dog, eek} state;

void tick()
{
	
	unsigned tmpA0 = ~PINA & 0x01;
	unsigned tmpA1 = ~PINA & 0x02;
	unsigned tmpA2 = ~PINA & 0x04;
	
	switch(state) {
		case start:
			state = wait;
			break;
		case wait:
			if(!tmpA2 && !tmpA0 && tmpA1){
				state = dog;
			}
			else if(tmpA2 && !tmpA0 && !tmpA1){
				state = eek;
			}
			else if(!tmpA2 && tmpA0 && !tmpA1){
				state = cat;
			}
			break;
		case cat:
			if(!tmpA2 && tmpA0 && !tmpA1){
				state = cat;
			}
			else{
				state = wait;
			}
			
			break;
		case dog:
			if(!tmpA2 && !tmpA0 && tmpA1){
				state = dog;
			}
			else{
				state = wait;
			}
			break;
		case eek:
			if(tmpA2 && !tmpA0 && !tmpA1){
				state = eek;
			}
			else{
				state = wait;
			}
			break;
		default:
			state = start;
			break;
	}
	
	switch(state) {
		case start:
			PWM_on();
			//set_PWM(200);
		break;
		case cat:
			set_PWM(261.63);
			//set_PWM(400.63);
			break;
		case dog:
			set_PWM(293.66);
			//set_PWM(261.63);
			break;
		case eek:
			set_PWM(329.63);
			break;
		default:
			PWM_on();
			break;
	}
}


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	state = start;
	PWM_on();
    while (1) 
    {
		//set_PWM(350);

		tick();
    }
}

