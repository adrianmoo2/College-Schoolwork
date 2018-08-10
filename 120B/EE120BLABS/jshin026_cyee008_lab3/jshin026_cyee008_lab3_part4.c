/*
 * jshin026_cyee008_lab3_part3.c
 *
 * Created: 4/5/2017 4:18:44 PM
 *  Author: Jennifer Shin, 861235693
 */ 
 /*	Partner(s) Name & E-mail: Chris Yee, cyee008
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #3 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

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
	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA2 = 0x00;
	unsigned char tmpA7 = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char flag = 0x00;
	unsigned char flag2 = 0x00;
	unsigned char lockSwitch = 0x01;
    while(1)
    {
        tmpA0 = PINA & 0x01;
        tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		tmpA7 = PINA & 0x80;
		
		tmpB = PINB;
		
		if(tmpA2 && !tmpA0 && !tmpA1)
		{
			flag = 1;
		}
		else if(flag && (!tmpA2 && !tmpA1 && !tmpA0))
		{
			flag2 = 1;
		}
		else if(flag && flag2) {}
		else
		{
			flag = 0;
			flag2 = 0;
		}
		
		if(flag && flag2 && (tmpA1 && !tmpA2 && !tmpA0))
		{
			tmpB = SetBit(tmpB,0,1);
			flag = 0;
			flag2 = 0;
			lockSwitch = !lockSwitch;
		}
		else if(flag && tmpA2) {}
		else if(!tmpA0 && !tmpA1 && !tmpA2){}
		else{
			flag2 = 0;
			flag = 0;
		}
		if(tmpA7 || lockSwitch)
		{
			tmpB = SetBit(tmpB,0,0);
		}
        
		PORTB = tmpB;
    }
}