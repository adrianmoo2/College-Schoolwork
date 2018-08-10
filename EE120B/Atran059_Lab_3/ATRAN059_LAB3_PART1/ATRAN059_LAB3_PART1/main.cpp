/*
 * ATRAN059_LAB3_PART1.cpp
 *
 * Created: 1/15/2018 2:18:15 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
enum States {Init, PUSH1, PUSH2} state;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	enum States {Init, PUSH1, PUSH2} state;
	state = Init;
		
	while (1) {
		tick();
	}
				

}

void tick() {
			switch(state){
				case Init:
					PORTB = 0x01;
					state = GetBit(PINA, 0) ? PUSH1 : Init;break;
				case PUSH1:
					PORTB = 0x02;
					state = !GetBit(PINA, 0) ? PUSH2 : PUSH1;break;
				case PUSH2:
					PORTB = 0x01;
				default:
					break;
			}
}

