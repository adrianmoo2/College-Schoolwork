/*
 * cyee008_lab1_part2.c
 *
* Created: 4/3/2017 5:06:44 PM
 *  Author: Christopher Yee
 */ 
 /* Partner(s) Name & E-mail: None
 *	Lab Section: 022
 *	Assignment: Lab # 1 Exercise # 2 
 *	Exercise Description: [optional - include for your own benefit]
 *	Port A's pins 3 to 0, each connect to a parking space sensor,
 * 1 meaning a car is parked in the space, of a four-space parking lot. 
 * Write a program that outputs in binary on port C the number of available spaces
 * (Hint: declare a variable "unsigned char cntavail"; you can assign a number to a port as follows: PORTC = cntavail;).
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpA = 0;
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

	PORTC = cntavail;
	}
	return 0;
}