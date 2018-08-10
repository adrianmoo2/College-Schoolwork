/*
 * ATRAN059_LAB3_PART2.c
 *
 * Created: 1/17/2018 3:09:55 PM
 *  Author: student
 */ 


#include <avr/io.h>
enum States {Init, WhatPush, Increment, Decrement, BothPushed} state;
	
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
	
	PORTC = 0x07;
	
	state = Init;
	
    while(1)
    {
        switch (state) {
			case Init:
				PORTC = 0x07;
				state = WhatPush;
				break;
			case WhatPush:
				state = GetBit(PINA, 0) ? Increment : state;
				state = GetBit(PINA, 1) ? Decrement : state;
				break;
			case Increment:
				if (PORTC < 0x09)
				{	PORTC = PORTC + 0x01;	}
				state = BothPushed;
				break;
			case Decrement:
				if (PORTC > 0x01)
				{	PORTC = PORTC - 0x01;	}
				state = BothPushed;
				break;
			case BothPushed:
				if (GetBit(PINA, 0) && GetBit(PINA, 1))
				{
					PORTC = 0x00;
				}
				state = WhatPush;
				break;
		}
		
    }
}