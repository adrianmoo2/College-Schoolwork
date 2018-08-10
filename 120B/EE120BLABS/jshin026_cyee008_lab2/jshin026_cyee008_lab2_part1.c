/*
 * jshin026_lab2_part1.c
 *
 * Created: 4/5/2017 4:18:44 PM
 *  Author: Christopher Yee/861224255
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #1 
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char counter = 0x00;
	unsigned char mask = 0x01;
	unsigned char buttonA = 0x00;
	unsigned char buttonB = 0x00;
	
    while(1)
    {
// 		buttonA = PINA;
// 		buttonB = PINB;
// 		for(int i = 0; i < 8; ++i) {
// 			if (GetBit(buttonA, i)) { // True if PA0 is 1
// 				counter = counter + 0x01;
// 			}
// 			if (GetBit(buttonB, i)) { // True if PA0 is 1
// 				counter = counter + 0x01;
// 			}
// 		}
		mask = 0x01;
		for(int i = 0; i < 8; ++i) {
			buttonA = PINA & mask;
			if (GetBit(buttonA, i)) { // True if PA0 is 1
				counter = counter + 0x01;
			}
			mask = mask << 1;
		}
		
		mask = 0x01;
		
		for(int i = 0; i < 8; ++i) {
			buttonB = PINB & mask;
			if (GetBit(buttonB, i)) { // True if PA0 is 1
				counter = counter + 0x01;
			}
			mask = mask << 1;
		}
		
        PORTC = counter;
		counter = 0x00;
    }
}