/*
 * cyee008_lab1_part3.c
 *
 * Created: 4/3/2017 5:06:44 PM
 *  Author: Christopher Yee 861224255
 */ 
 /*	Partner(s) Name & E-mail:None
 *	Lab Section: 022
 *	Assignment: Lab #1  Exercise #3 
 *	Exercise Description: [optional - include for your own benefit]
 *	Extend the previous program to still write the available spaces number, but only to PC3..PC0, and to set PC7 to 1 if the lot is full.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpA = 0x00;
	unsigned char tmpToMask = 0x00;
	unsigned char cntavail = 0x00;
	while(1)
	{
		cntavail = 0x00;
		tmpA = (PINA << 4);
		
		for(int i = 0; i < 4; i++) {
			tmpToMask = (tmpA & 0x80);
			if (tmpToMask ==  0x00) {
				cntavail++;
			}
			tmpA = (tmpA << 1);
		}

		PORTC = cntavail | (PINC & 0x70);
		if(cntavail == 0) {
			 PORTC = PINC | 0x80;
		}
		
	}
	return 0;
}