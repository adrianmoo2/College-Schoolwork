/*
 * cyee008_lab1_part1.c
 *
 * Created: 4/3/2017 4:03:50 PM
 *  Author: Christopher Yee / 861224255
 */ 
 /*	Partner(s) Name & E-mail: None
 *	Lab Section: 022
 *	Assignment: Lab # 1 Exercise # 1 
 *	Exercise Description: [optional - include for your own benefit]
 *	Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a 
 *  light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates 
 *  an LED connected to PB0 (1 means illuminate) if the garage door is open at night.

 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA0 = 0x00;
	unsigned char tmpB = 0xFF;
	while(1)
	{
		tmpA0 = PINA & 0x01; //PA0
		tmpA1 = PINA & 0x02; //PA1
		
		if(tmpA0 == 0x01 && tmpA1 != 0x02){
			tmpB = (tmpB & 0xFE) | 0x01;
		}
		else{
			tmpB = (tmpB & 0xFE);
		}
		PORTB = tmpB;
	}
	return 0;
}