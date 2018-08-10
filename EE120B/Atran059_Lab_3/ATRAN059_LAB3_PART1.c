/*
 * ATRAN059_LAB3_PART1.c
 *
 * Created: 1/18/2018 4:31:39 PM
 *  Author: student
 */ 


#include <avr/io.h>
enum States {Init, WaitPush, Pressed} state;


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
	
	state = Init;
	
    while(1)
    {
        switch (state)
		{
			case Init:
				PORTB = SetBit(PORTB, 0, 1);
				state = WaitPush;
				break;
			case WaitPush:
				state = GetBit(PINA, 0) ? Pressed : state;
				break;
			case Pressed:
				if (GetBit(PORTB, 0))
				{
					PORTB = SetBit(PORTB, 0, 0);
					PORTB = SetBit(PORTB, 1, 1);
				}
				else if (GetBit(PORTB, 1))
				{
					PORTB = SetBit(PORTB, 0, 1);
					PORTB = SetBit(PORTB, 1, 0);
				}
				state = WaitPush;
				break;
		}
    }
}