/*
 * cyee008_lab1_part4.c
 *
* Created: 4/5/2017 11:25:53 AM
 * Author : Christopher Yee / 861224255
 */ 
 /*	Partner(s) Name & E-mail: None
 *	Lab Section: 22
 *	Assignment: Lab # 1 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	Challenge
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00; 
	
	unsigned char tmpB = 0x00; 	
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00; 
	unsigned char tmpD = 0x00;
	while(1)
	{
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;
		if (tmpA +tmpB + tmpC > 140) { 
			tmpD = (tmpD & 0xFE) | 0x01; 
		}
		else{
			tmpD = tmpD & 0xFE;
		}
		
		if(tmpC - tmpA > 80 || tmpA - tmpC > 80){
			tmpD = (tmpD & 0xFD) | 0x02; 
		}
		else{
			tmpD = tmpD & 0xFD;
		}
		PORTD = tmpD;
	}
	return 0;
}