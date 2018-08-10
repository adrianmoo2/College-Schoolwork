/*
 * jshin026_cyee008_lab2_part3.c
 *
 * Created: 4/10/2017 1:19:00 PM
 *  Author: Christopher Yee, cyee008
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.

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
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	while(1)
	{
		tmpA = ~PINA & 0x0F;
		if(tmpA == 0){
			tmpC = SetBit(tmpC, 6, 1);
		}
		if(tmpA == 1 || tmpA == 2) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 6, 1);
		}
		if(tmpA == 3 || tmpA == 4) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 4, 1);
			tmpC = SetBit(tmpC, 6, 1);
		}
		if(tmpA == 5 || tmpA == 6) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 4, 1);
			tmpC = SetBit(tmpC, 3, 1);
		}
		if(tmpA == 7 || tmpA == 8 || tmpA == 9) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 4, 1);
			tmpC = SetBit(tmpC, 3, 1);
			tmpC = SetBit(tmpC, 2, 1);
		}
		if(tmpA == 10 || tmpA == 11 || tmpA == 12) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 4, 1);
			tmpC = SetBit(tmpC, 3, 1);
			tmpC = SetBit(tmpC, 2, 1);
			tmpC = SetBit(tmpC, 1, 1);
		}
		if(tmpA == 13 || tmpA == 14 || tmpA == 15) {
			tmpC = SetBit(tmpC, 5, 1);
			tmpC = SetBit(tmpC, 4, 1);
			tmpC = SetBit(tmpC, 3, 1);
			tmpC = SetBit(tmpC, 2, 1);
			tmpC = SetBit(tmpC, 1, 1);
			tmpC = SetBit(tmpC, 0, 1);
		}

		tmpA = PINA;
		if(GetBit(tmpA, 4) && GetBit(tmpA, 5) && !GetBit(tmpA, 6)) {
			tmpC = SetBit(tmpC, 7, 1);
		}
		
		PORTC = tmpC;
		tmpC = 0x00;
	}
}