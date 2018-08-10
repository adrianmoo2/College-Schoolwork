/*
 * ATRAN059_LAB3_PART1.c
 * Lab Section: 24
 * Assignment: Lab 3 Part 1
 * Created: 1/18/2018 4:31:39 PM
 *  Author: student
 */ 


#include <avr/io.h>
enum States {Start, Init, WhatPush, Locked, NumPressed, YPressed, XPressed} state;
char correctSequence[4] = {0x03, 0x05, 0x04, 0x05};
char buttonSequence[4];
int i;	

char areEqual(char arr1[], char arr2[])
{
    for (int i=0; i<3; i++)
	{
         if (arr1[i] != arr2[i])
         {
			  return 0;
		 }
	}
    // If all elements were same.
    return 1;
}


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
			if (i == 4 && areEqual(buttonSequence, correctSequence))
			{
				i = 0;
				if (GetBit(PORTB, 0))
				{
					PORTB = SetBit(PORTB, 0, 0);
				}
				else {
					PORTB = SetBit(PORTB, 0, 1);
				}
			}
			break;
		case Locked:
			PORTC = 0x02;
			PORTB = SetBit(PORTB, 0, 0);
			break;
		case NumPressed:
			PORTC = 0x03;
			buttonSequence[i] = 0x03;
			if (!(buttonSequence[i] == correctSequence[i]))
			{
				i = 0;
			}
			else {
				++i;
			}
			break;
		case YPressed:
			PORTC = 0x04;
			buttonSequence[i] = 0x04;
			if (!(buttonSequence[i] == correctSequence[i]))
			{
				i = 0;
			}
			else {
				++i;
			}
			break;
		case XPressed:
			PORTC = 0x05;
			buttonSequence[i] = 0x05;
			if (!(buttonSequence[i] == correctSequence[i]))
			{
				i = 0;
			}
			else {
				++i;
			}
			if (i == 3 && (buttonSequence != correctSequence))
			{
				i = 0;
			}
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
	
	i = 0;
	
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
				if (i == 4 && areEqual(buttonSequence, correctSequence))
				{
					i = 0;
					if (GetBit(PORTB, 0))
					{
						PORTB = SetBit(PORTB, 0, 0);
					}
					else {
						PORTB = SetBit(PORTB, 0, 1);
					}
				}
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
				buttonSequence[i] = 0x03;
				if (!(buttonSequence[i] == correctSequence[i]))
				{
					i = 0;
				}
				else {
					++i;
				}
				break;
			case YPressed:
				PORTC = 0x04;
				state = WhatPush;
				buttonSequence[i] = 0x04;
				if (!(buttonSequence[i] == correctSequence[i]))
				{
					i = 0;
				}
				else {
					++i;
				}
				break;
			case XPressed:
				PORTC = 0x05;
				state = WhatPush;
				buttonSequence[i] = 0x05;
				if (!(buttonSequence[i] == correctSequence[i]))
				{
					i = 0;
				}
				else {
					++i;
				}
				if (i == 3 && (buttonSequence != correctSequence))
				{
					i = 0;
				}
				break;
		}*/
    }
}