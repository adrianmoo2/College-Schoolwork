/*
 * ATRAN059_LAB3_PART3.c
 *
 * Created: 1/17/2018 3:23:36 PM
 *  Author: student
 */ 


#include <avr/io.h>
enum States {Init, WhatPush, Locked, NumPressed, YPressed, XPressed} state;
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

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = Init;
	
	i = 0;
	
    while(1)
    {
        switch (state)
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
		}
    }
}