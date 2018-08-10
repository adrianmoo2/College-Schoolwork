/*	Partner(s) Name & E-mail: Jennifer Shin (jshin026), Chris Yee (cyee008)
 *	Lab Section: 22
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    ADC_init();
	unsigned short my_adc = ADC;
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char light = 0x00;
    while (1) 
    {
		my_adc = ADC;
		tmpA = (char)my_adc;
		tmpC = (char)(my_adc >> 2);
		if (my_adc < 0x01B0) {
			light = 0x80;
		}
		else {
			light = 0x00;
		}
		PORTC = light;
		//PORTD = ~tmpC;
    }
}
