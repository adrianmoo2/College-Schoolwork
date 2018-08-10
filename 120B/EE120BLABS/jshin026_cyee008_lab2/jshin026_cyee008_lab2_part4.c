/*
 * jshin026_cyee008_lab2_part4.c
 *
 * Created: 4/10/2017 3:33:42 PM
 *  Author: Christopher Yee/861224255
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #4 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = PINA >> 4;
		PORTC = PINA << 4 | 0x00;
    }
}

