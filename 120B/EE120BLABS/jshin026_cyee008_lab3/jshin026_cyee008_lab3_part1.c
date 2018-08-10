/*
 * jshin026_cyee008_lab3_part1.c
 *
 * Created: 4/10/2017 3:47:41 PM
 *  Author: student
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
	DDRB = 0xFF; PORTB = 0x01;
	unsigned char flag = 0x00;
	unsigned char tmpB = PINB;
    while(1)
    {
		if(PINA == 1) {
			if(!flag) {
				flag = 1;
				if(GetBit(PINB, 0)) {
					tmpB = SetBit(tmpB, 0, 0);
					tmpB = SetBit(tmpB, 1, 1);
				}
				else {
					tmpB = SetBit(tmpB, 0, 1);
					tmpB = SetBit(tmpB, 1, 0);
				}
			}
		}
		else {
			flag = 0;
		}
		
		PORTB = tmpB;
    }
}