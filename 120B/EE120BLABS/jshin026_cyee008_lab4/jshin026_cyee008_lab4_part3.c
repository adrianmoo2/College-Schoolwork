/*
 * jshin026_cyee008_lab3_part2.c
 *
 * Created: 4/5/2017 4:18:44 PM
 *  Author: Christopher Yee, cyee008
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #3 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

enum States { Start, One, Two, Three, Four, Five, Six, Seven, Eight, Wait, WaitFall1, WaitFall2, WaitFall3, WaitFall4, WaitFall5, WaitFall6, WaitFall7, WaitFall0} State;
unsigned char tmpC = 0x00;
void Latch()
{
	unsigned char tmpA0 = ~PINA & 0x01;
	switch(State) {
		case Start:
			State = Wait;
			break;
			case Wait:
			if(tmpA0){
				State = WaitFall0;
				}
			break;

			case One:
			if(tmpA0){
				State = WaitFall1;
			}
			break;
			case Two:
			if(tmpA0){
				State = WaitFall2;
			}
			break;
			case Three:
			if(tmpA0){
				State = WaitFall3;
			}
			break;
			case Four:
			if(tmpA0){
				State = WaitFall4;
			}
			break;
			case Five:
			if(tmpA0){
				State = WaitFall5;
			}
			break;
			case Six:
			if(tmpA0){
				State = WaitFall6;
			}
			break;
			case Seven:
			if(tmpA0){
				State = WaitFall7;
			}
			break;
			case Eight:
			if(tmpA0){
				State = Wait;
			}
			break;
			default:
				State = Wait;
			break;
			//_________________________________________________________________

			case WaitFall0:
			if(tmpA0){
				State = WaitFall0;
			}
			else{
				State = One;
			}
			break;
			case WaitFall1:
			if(tmpA0){
				State = WaitFall1;
			}
			else{
				State = Two;
			}
			break;
			case WaitFall2:
			if(tmpA0){
				State = WaitFall2;
			}
			else{
				State = Three;
			}
			break;
			case WaitFall3:
			if(tmpA0){
				State = WaitFall3;
			}
			else{
				State = Four;
			}
			break;
			case WaitFall4:
			if(tmpA0){
				State = WaitFall4;
			}
			else{
				State = Five;
			}
			break;
			case WaitFall5:
			if(tmpA0){
				State = WaitFall5;
			}
			else{
				State = Six;
			}
			break;
			case WaitFall6:
			if(tmpA0){
				State = WaitFall6;
			}
			else{
				State = Seven;
			}
			break;
			case WaitFall7:
			if(tmpA0){
				State = WaitFall7;
			}
			else{
				State = Eight;
			}
			break;
			}
			//___________________

			switch(State) {
				case Start:
					tmpC = 0x00;
					break;
				case One:
					tmpC = 0x00;
					break;
				case Two:
					tmpC = 0x00;
					break;
				case Three:
				tmpC = 0x00;
					break;
				case Four:
				tmpC = 0x00;
					break;
				case Five:
				tmpC = 0x00;
					break;
				case Six:
				tmpC = 0x00;
					break;
				case Seven:
				tmpC = 0x00;
					break;
				case Eight:
				tmpC = 0x00;
					break;
				case WaitFall0:
					//tmpC = 0x00;
					tmpC =SetBit(tmpC,0,1);
					tmpC =SetBit(tmpC,2,1);
					tmpC =SetBit(tmpC,4,1);
					tmpC =SetBit(tmpC,6,1);
					break;
				case WaitFall1:
					tmpC =SetBit(tmpC,1,1);
					tmpC =SetBit(tmpC,3,1);
					tmpC =SetBit(tmpC,5,1);
					break;
				case WaitFall2:
					tmpC =SetBit(tmpC,0,1);
					tmpC =SetBit(tmpC,2,1);
					break;
				case WaitFall3:
					tmpC =SetBit(tmpC,1,1);
					tmpC =SetBit(tmpC,3,1);
					break;
				case WaitFall4:
					tmpC =SetBit(tmpC,2,1);
					tmpC =SetBit(tmpC,4,1);
					break;
				case WaitFall5:
					tmpC =SetBit(tmpC,3,1);
					tmpC =SetBit(tmpC,5,1);
					break;
				case WaitFall6:
					tmpC =SetBit(tmpC,4,1);
					tmpC =SetBit(tmpC,6,1);
					break;
				case WaitFall7:
					tmpC =SetBit(tmpC,0,1);
					tmpC =SetBit(tmpC,1,1);
					tmpC =SetBit(tmpC,2,1);
					tmpC =SetBit(tmpC,3,1);
					tmpC =SetBit(tmpC,4,1);
					tmpC =SetBit(tmpC,5,1);
					tmpC =SetBit(tmpC,6,1);
					break;
				default:
					tmpC = 0x00;
					break;
			}
		PORTC = tmpC;

}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	//B = 0x00;
	State = Start;

	while(1) {
		Latch();
	}
}

