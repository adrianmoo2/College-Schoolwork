/*
 * ATRAN059_LAB2_PART1.cpp
 *
 * Created: 1/10/2018 3:49:59 PM
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char counter = 0x00;
	
	while (1)
	{
		counter = 0x00;
		for(unsigned char i = 0x00; i < 0x08; ++i)
		{
			if (GetBit(PINA, i))
			{
				++counter;
			}
			if (GetBit(PINB, i))
			{
				++counter;
			}
		}
		
		PORTC = counter;
	}
	return 0;
}