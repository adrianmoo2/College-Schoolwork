/*
 * ATRAN059_LAB3_PART1.c
 * Lab Section: 24
 * Assignment: Lab 3 Part 1
 * Created: 1/18/2018 4:31:39 PM
 *  Author: student
 */ 


#include <avr/io.h>
enum States {Start, Init, WhatPush, Locked, NumPressed, YPressed, XPressed} state;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void Tick()
{
	switch (state)
	{
		case Start:
			state = Init;
			break;
		case Init:
			state = WhatPush;
			break;
		case WhatPush:
			state = PINA == 0x80 ? Locked : state;
			state = PINA == 0x04 ? NumPressed : state;
			state = PINA == 0x02 ? YPressed : state;
			state = PINA == 0x01 ? XPressed : state;
			break;
		case Locked:
			state = WhatPush;
			break;
		case NumPressed:
			state = WhatPush;
			break;
		case YPressed:
			state = WhatPush;
			break;
		case XPressed:
			state = WhatPush;
			break;
		default:
			break;
	}
	switch (state)
	{
		case Start:
			break;
		case Init:
		PORTB = 0x00;
			PORTC = 0x00;
			break;
		case WhatPush:
			break;
		case Locked:
			PORTC = 0x02;
			PORTB = SetBit(PORTB, 0, 0);
			break;
		case NumPressed:
		PORTC = 0x03;
			break;
		case YPressed:
			if (PORTC == 0x03)
			{
				if (GetBit(PORTB, 0))
				{
					PORTB = SetBit(PORTB, 0, 0);
				}
				else
				{
					PORTB = SetBit(PORTB, 0, 1);
				}
			}
			PORTC = 0x04;
			break;
		case XPressed:
			PORTC = 0x05;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Start;
	
    while(1)
    {
		Tick();
        /*switch (state)
		{
			case Init:
				PORTB = 0x00;
				PORTC = 0x00;
				state = WhatPush;
				break;
			case WhatPush:
				state = PINA == 0x80 ? Locked : state;
				state = PINA == 0x04 ? NumPressed : state;
				state = PINA == 0x02 ? YPressed : state;
				state = PINA == 0x01 ? XPressed : state;
				break;
			case Locked:
				PORTC = 0x02;
				PORTB = SetBit(PORTB, 0, 0);
				state = WhatPush;
				break;
			case NumPressed:
				PORTC = 0x03;
				state = WhatPush;
				break;
			case YPressed:
				if (PORTC == 0x03)
				{
					if (GetBit(PORTB, 0))
					{
						PORTB = SetBit(PORTB, 0, 0);
					}
					else
					{	
						PORTB = SetBit(PORTB, 0, 1);
					}
				}
				PORTC = 0x04;
				state = WhatPush;
				break;
			case XPressed:
				PORTC = 0x05;
				state = WhatPush;
				break;
		}*/
    }
}