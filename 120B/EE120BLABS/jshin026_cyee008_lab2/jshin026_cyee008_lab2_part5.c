/*
* jshin026_cyee008_lab2_part5.c
*
* Created: 4/9/2017 9:25:13 PM
 *  Author: Christopher Yee/861224255
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #5 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char tmpD = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmp2B = 0x00;

	while(1)
	{
	tmpD = PIND;
	tmp2B = GetBit(PINB, 1);

	if(tmpD >= 35){
		tmpB = SetBit(tmpB, 1, 1);
	}
	else if( tmpD < 35 && tmpD > 2) {
		tmpB = SetBit(tmpB, 2, 1);
	}

	PORTB = tmpB;
	tmpB = tmpB & 0x01;
	}
}