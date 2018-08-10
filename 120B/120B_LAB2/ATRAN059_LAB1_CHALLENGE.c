/*
 * ATRAN059_LAB1_CHALLENGE.c
 *
 * Created: 1/11/2018 3:25:12 PM
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
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char weightA = 0x00;
	unsigned char weightB = 0x00;
	unsigned char weightC = 0x00;
	
    while(1)
    {
		weightA = 0x00;
		weightB = 0x00;
		weightC = 0x00;
		
		weightA = PINA;
		weightB = PINB;
		weightC = PINC;
		
		if (weightA + weightB + weightC > 0x8C)
		{
			PORTD = PORTD | 0x01;
		}
		if (weightC - weightA > 0x50 || weightC - weightA < -0x50 )
		{
			PORTD = PORTD | 0x02;
		}
		
    }
	return 0;
}