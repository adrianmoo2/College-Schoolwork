/*
 * ATRAN059_LAB3_PART1.c
 * Lab Section: 24
 * Assignment: Lab 4 Part 2
 * Created: 1/18/2018 4:31:39 PM
 *  Author: student
 */ 

#include <avr/io.h>
enum States {Start, Init, WhatPush, Increment, Decrement, BothPushed} state;
	
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void Tick() {
	switch (state) {
		case Start:
			state = Init;
			break;
		case Init:
			state = WhatPush;
			break;
		case WhatPush:
			state = GetBit(PINA, 0) ? Increment : state;
			state = GetBit(PINA, 1) ? Decrement : state;
			break;
		case Increment:
			state = BothPushed;
			break;
		case Decrement:
			state = BothPushed;
			break;
		case BothPushed:
			state = WhatPush;
		break;
	}
	
	switch (state) {
		case Start:
			break;
		case Init:
			PORTB = 0x07;
			break;
		case WhatPush:
			break;
		case Increment:
			if (PORTB < 0x09)
			{	PORTB = PORTB + 0x01;	}
			break;
		case Decrement:
			if (PORTB > 0x01)
			{	PORTB = PORTB - 0x01;	}
			break;
		case BothPushed:
			if (GetBit(PINA, 0) && GetBit(PINA, 1))
			{
				PORTB = 0x00;
			}
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	
    while(1)
    {
		Tick();
        /*switch (state) {
			case Init:
				PORTB = 0x07;
				state = WhatPush;
				break;
			case WhatPush:
				state = GetBit(PINA, 0) ? Increment : state;
				state = GetBit(PINA, 1) ? Decrement : state;
				break;
			case Increment:
				if (PORTB < 0x09)
				{	PORTB = PORTB + 0x01;	}
				state = BothPushed;
				break;
			case Decrement:
				if (PORTB > 0x01)
				{	PORTB = PORTB - 0x01;	}
				state = BothPushed;
				break;
			case BothPushed:
				if (GetBit(PINA, 0) && GetBit(PINA, 1))
				{
					PORTB = 0x00;
				}
				state = WhatPush;
				break;
		}*/
		
    }
}