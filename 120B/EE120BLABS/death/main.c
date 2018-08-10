/*
 * cyee008_music_game.c
 *
 * Created: 5/31/2017 2:39:05 PM
 * Author : maro8
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
/* taken from http://maxembedded.com/2011/06/the-adc-of-the-avr/
*/
void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}
/*

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

// ====================
// SM1: DEMO LED matrix
// ====================
enum SM1_States {sm1_display} state;
int SM1_Tick() {
	// === Local Variables ===
	static unsigned char column_val = 0x01; // sets the pattern displayed on columns
	static unsigned char column_sel = 0x7F; // grounds column to display pattern

	// === Transitions ===
	switch (state) {
		case sm1_display: break;
		default: state = sm1_display;
		break;
	}

	// === Actions ===
	switch (state) {
		case sm1_display: // If illuminated LED in bottom right corner
		if (column_sel == 0xFE && column_val == 0x80) {
			column_sel = 0x7F; // display far left column
			column_val = 0x01; // pattern illuminates top row
		}
		// else if far right column was last to display (grounded)
		else if (column_sel == 0xFE) {
			column_sel = 0x7F; // resets display column to far left column
			column_val = column_val << 1; // shift down illuminated LED one row
		}
		// else Shift displayed column one to the right
		else {
			column_sel = (column_sel >> 1) | 0x80;
		}
		break;
		default: break;
	}

	PORTA = column_val; // PORTA displays column pattern
	PORTC = column_sel; // PORTB selects column to display pattern
	return state;
};

*/
void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTD = 0x08;
		// set SER = next bit of data to be sent.
		PORTD |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTD |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTD |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTD = 0x00;
}
//enum states{up, down} state;
void tick(){
/*
	if(adc_read(0) > 800){
		PORTD = 0xFF;
		}
		else if( adc_read(0) < 400){
		PORTD = 0xF0;
		}
		else{
		PORTD = 0x00;
		}
		*/
		//uint16_t mid = adc_read(0);
		//if(mid > 700){
		//	PORTD = mid;
		//}
		//else{
		//	PORTD = 0;
		//}
		uint16_t x = adc_read(0);
		int vert = analogRead(0);
		uint16_t y = adc_read(1);
		if( x == 1023){
		PORTD = 5;
		}
		else if(x + 401 < 400){
		PORTD = 10;
		}
		else{
		PORTD = 0x00;
		}
	//	x = x-512;
	//	y = y-512;

	//	PORTD = x - y;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	//TimerSet(100);
	//TimerOn();
	//state = sm1_display;
	adc_init();
	
    /* Replace with your application code */
    while (1) 
    {
		//uint16_t hi = adc_read(0);
		tick();
		//transmit_data(15);
		//SM1_Tick();
		//while(!TimerFlag);
		//TimerFlag = 0;
		//if(adc_read(0) > 1012){
		//	transmit_data(adc_read(0) >> 2);//adc_read(0);
		//}
		//else{
		//	PORTB = 0x00;
		//}
    }
}

