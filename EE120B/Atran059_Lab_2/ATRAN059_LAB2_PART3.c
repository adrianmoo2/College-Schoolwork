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

unsigned char GetKey(unsigned char x)
{
	return GetBit(x, 4);
}

unsigned char GetSeated(unsigned char x)
{
	return GetBit(x, 5);
}

unsigned char GetBelt(unsigned char x)
{
	return GetBit(x, 6);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned int fuelLevel = 0;
	unsigned char tmpA = 0x00;
	
	while (1)
	{
		fuelLevel = 0;
		tmpA = 0x00;
		
		fuelLevel = GetBit(PINA, 0) ? fuelLevel+1 : fuelLevel;
		fuelLevel = GetBit(PINA, 1) ? fuelLevel+2 : fuelLevel;
		fuelLevel = GetBit(PINA, 2) ? fuelLevel+4 : fuelLevel;
		fuelLevel = GetBit(PINA, 3) ? fuelLevel+8 : fuelLevel;
		
		tmpA = fuelLevel == 1 || fuelLevel == 2 ? 0x20 : tmpA;
		tmpA = fuelLevel == 3 || fuelLevel == 4 ? 0x30 : tmpA;
		tmpA = fuelLevel == 5 || fuelLevel == 6 ? 0x38 : tmpA;
		tmpA = fuelLevel >= 7 && fuelLevel <= 9 ? 0x3C : tmpA;
		tmpA = fuelLevel >= 10 && fuelLevel <= 12 ? 0x3E : tmpA;
		tmpA = fuelLevel >= 13 && fuelLevel <= 15 ? 0x3F : tmpA;
		
		if (fuelLevel <= 4)
		{
			tmpA = tmpA | 0x40; 
		}
		
		PORTC = tmpA;
		
		if (GetKey(PINA) && GetSeated(PINA) && !GetBelt(PINA))
		{
			PORTC = PORTC | 0x80;
		}
	}
	return 0;
}