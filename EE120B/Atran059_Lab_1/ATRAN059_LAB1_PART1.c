/*
 * ATRAN059_LAB1_PART1.c
 *
 * Created: 1/10/2018 12:57:32 PM
 *  Author: student
 */ 


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	
    while(1)
    {
        tmpA = PINA & 0x01;
		if (tmpA == 0x01)
		{
			tmpB = 0x01;
		}
		PORTB = tmpB;
    }
	return 0;
}