/*
 * ATRAN059_LAB2_PART4.c
 *
 * Created: 1/11/2018 4:18:38 PM
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
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	
    while(1)
    {	
		for (unsigned int i = 0; i < 8; ++i)
		{
			if (i > 3)
			{
				PORTB =  SetBit(PORTB, i-4 , GetBit(PINA, i));
			}
			else if (i <= 3)
			{
				PORTC = SetBit(PORTC, i+4, GetBit(PINA, i));
			}
		}
    }
	return 0;
}