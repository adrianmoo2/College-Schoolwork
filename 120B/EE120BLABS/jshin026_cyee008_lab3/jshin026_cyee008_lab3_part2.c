/*
 * jshin026_cyee008_lab3_part2.c
 *
 * Created: 4/5/2017 4:18:44 PM
 *  Author: Christopher Yee, cyee008
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #2  Exercise #2 
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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x07; // Configure port C's 8 pins as outputs,
	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpC = 0x07;
	unsigned char flag = 0x00;
    while(1)
    {
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		if(!flag) {
			//flag = 1;
			if(tmpA0 && !tmpA1) {
				tmpC++;
				flag = 1;
			}
			else if(!tmpA0 && tmpA1) {
				tmpC--;
				flag =1;
			}
			else if(tmpA0 && tmpA1) {
				tmpC = 0;
				flag = 1;
			}
		}
		else if(!tmpA0 && !tmpA1){
				flag = 0;
		}
		else if(tmpA0 && tmpA1){
			tmpC = 0;
		}
		else if(tmpA0 && !tmpA1) {
				tmpC++;
				//flag = 1;
			}
			else if(!tmpA0 && tmpA1) {
				tmpC--;
			//	flag =1;
			}
		
		PORTC = tmpC;
    }
}