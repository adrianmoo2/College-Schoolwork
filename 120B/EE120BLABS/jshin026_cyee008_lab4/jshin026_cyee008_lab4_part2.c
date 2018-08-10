/*
 * jshin026_cyee008_lab3_part2.c
 *
 * Created: 4/5/2017 4:18:44 PM
 *  Author: Christopher Yee, cyee008
 */ 
 /*	Partner(s) Name & E-mail: Jennifer Shin, jshin026
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #2 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>


enum States { Start, Increment, Decrement, Reset, Wait, WaitFall} State;
unsigned char tmpC = 0x00;
void Latch()
{
	unsigned char tmpA0 = ~PINA & 0x01;
	unsigned char tmpA1 = ~bPINA & 0x02;
	switch(State) {
		case Start:
			State = Wait;
			break;
		case Wait:
			if(tmpA0){
				State = Increment;
				}
			else if(tmpA1){
				State = Decrement;
				}
			else if(tmpA0 && tmpA1){
				State = Reset; 
				}
			else{
				State = Wait;
				}
				break;
			case Increment:
				if(!tmpA0 && !tmpA1){
					State = Wait;
				}
				if(tmpA0 && !tmpA1) {
					State = WaitFall;
				}
				else if(tmpA0 && tmpA1){
					State = Reset;
				}
				else{
					State = Increment;
				}
				break;
			case Decrement:
				if(!tmpA0 && !tmpA1){
					State = Wait;
				}
				if(!tmpA0 && tmpA1) {
					State = WaitFall;
				}
				else if(tmpA0 && tmpA1){
					State = Reset;
				}
				else{
					State = Decrement;
				}
				break;
			case Reset:
				if(!tmpA0 && !tmpA1){
					State = Wait;
				}
				else{
					State = Reset;
				}
				break;
			case WaitFall:
				if((tmpA0 && !tmpA1) || (!tmpA0 && tmpA1)) {
					State = WaitFall;
				}
				else if(tmpA0 && tmpA1) {
					State = Reset;
				}
				else {
					State = Wait;
				}
				break;
			default:
				State = Start;
				break;
			}
			switch(State) {
				case Start:
					tmpC = 0x00;
					break;
				case Increment:
					if(tmpC != 0x09){
					tmpC = tmpC + 1;
					}
					break;
				case Decrement:
					if(tmpC != 0x00){
					tmpC = tmpC - 1;
					}
					break;
				case Reset:
					tmpC = 0x00;
					break;
				case Wait:
					break;
				case WaitFall:
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

