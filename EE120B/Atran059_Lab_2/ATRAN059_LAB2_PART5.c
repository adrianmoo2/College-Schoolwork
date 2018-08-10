/*
 * ATRAN059_LAB2_PART5.c
 *
 * Created: 1/11/2018 4:40:43 PM
 *  Author: student
 */ 


#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;
	
	unsigned char tempWeight = 0x00;
   
    while(1)
    {
		tempWeight = PIND;
		
		if (GetBit(PORTB, 0))
		{
			if (tempWeight >= 0x45)
			{
				PORTB = SetBit(PORTB, 1, 1);
			}
			else if (tempWeight >= 0x04)
			{
				PORTB = SetBit(PORTB, 1, 0);
				PORTB = SetBit(PORTB, 2, 1);
			}
		}
		else
		{
				if (tempWeight >= 0x46)
				{
					PORTB = SetBit(PORTB, 1, 1);
				}
				else if (tempWeight >= 0x05)
				{
					PORTB = SetBit(PORTB, 1, 0);
					PORTB = SetBit(PORTB, 2, 1);
				}
		}
    }
}