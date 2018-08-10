/*
 * ATRAN059_LAB1_PART2.cpp
 *
 * Created: 1/11/2018 9:19:00 PM
 * Author : Adrian
 */ 

/*
 * ATRAN059_LAB1_PART2.c
 *
 * Created: 1/10/2018 1:03:56 PM
 *  Author: student
 */ 


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char cntavail = 0x00;
	
	while(1)
	{
		tmpA = PINA & 0x0F;
		
		if (tmpA == 0x00)
		{
			cntavail = 0x04;
		}
		else if (tmpA == 0x01 | tmpA == 0x02 | tmpA == 0x04 | tmpA == 0x08)
		{
			cntavail = 0x03;
		}
		else if (tmpA == 0x0C | tmpA == 0x0A | tmpA == 0x09 | tmpA == 0x06 | tmpA == 0x05 | tmpA == 0x03)
		{
			cntavail = 0x02;
		}
		else if (tmpA == 0x0E | tmpA == 0x0D | tmpA == 0x07 | tmpA == 0x0B)
		{
			cntavail = 0x01;
		}
		else if (tmpA == 0x0F)
		{
			cntavail = 0x00;
		}
		
		PORTC = cntavail;
	}
	return 0;
}