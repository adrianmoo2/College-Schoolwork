/*
 * ATRAN059_LAB3_PART1.c
 * Lab Section: 24
 * Assignment: Lab 4 Part 3
 * Created: 1/18/2018 4:31:39 PM
 *  Author: student
 */ 

#include <avr/io.h>
enum States {Start, Init, WaitPush, Pushed} state;
	
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void Tick() {
	switch (state) {
		case Start:
			state = Init;
			break;
		case Init:
			state = WaitPush;
			break;
		case WaitPush:
			state = GetBit(PINA, 0) ? Pushed : state;
			break;
		case Pushed:
			state = !GetBit(PINA, 0) ? WaitPush : State;
			break;
		default:
			break;
	}
	
	switch (state) {
		case Start:
			break;
		case Init:
			PORTB = 0x00;
			break;
		case WaitPush:
			break;
		case Pushed:
			if (PORTB == 0x00 || PORTB = 0x10)
			{
				PORTB = 0x01;
			}
			else if (PORTB < 16)
			{
				PORTB = PORTB * 2;
			}
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	
    while(1)
    {
		Tick();
    }
}