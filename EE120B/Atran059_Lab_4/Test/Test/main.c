/*
 * Test.c
 *
 * Created: 1/24/2018 3:52:43 PM
 * Author : Adrian
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0x0F;
    }
}

