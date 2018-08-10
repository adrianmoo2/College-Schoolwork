// ====================
// SM1: DEMO LED matrix
// ====================

#include <avr/io.h>
#include <avr/interrupt.h>

//Global variables

//States
enum SM1_States {sm1_display, sm1_pressed};
enum SM2_States {sm2_display};
	
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
	OCR1A = 125;    // Timer interrupt will be generated when TCNT1==OCR1A
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

	
int SM1_Tick(int state) {

	unsigned char D0 = ~PIND & 0x01;
	unsigned char D1 = ~PIND & 0x02;
	unsigned char D2 = ~PIND & 0x04;

	// === Local Variables ===
	static unsigned char column_val = 0x01; // sets the pattern displayed on columns
	static unsigned char column_sel = 0x7F; // grounds column to display pattern
	
	// === Transitions ===
	switch (state) {
		case sm1_display:
			//state = D0 ? sm1_pressed : state;   
			break;
		case sm1_pressed:
			break;
		default:               
			state = sm1_display;
			break;
	}
	
	// === Actions ===
	switch (state) {
		case sm1_display:   // If illuminated LED in bottom right corner
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
		case sm1_pressed:
			break;
		default:               
			break;
	}
	
	PORTA = column_val; // PORTA displays column pattern
	PORTB = column_sel; // PORTB selects column to display pattern

	return state;
};


/*void SM2_Tick(int sm2_state)
{
	unsigned char randLEDOne = 0x01;
	unsigned char randLEDTwo = 0x02;
	
	switch(sm2_state)
	{
		case sm2_display:
			break;
		default:
			break;
	}
	
	switch(sm2_state)
	{
		case sm2_display:
			PORTA = randLEDOne;
			PORTB = randLEDTwo;
			break;
		default:
			break;
	}
};*/

int main()
{
	const unsigned long timerPeriod = 100;
	
	//states
	int sm1_state = sm1_display;
	int sm2_state = sm2_display;
	
	//Inputs
	DDRD = 0x00; PORTD = 0xFF;
	
	//Outputs
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	
	//sm's timers
	unsigned long SM1_elapsedTime = 0;
	unsigned long SM2_elapsedTime = 0;
	
	TimerSet(timerPeriod);
	TimerOn();
	
	while (1)
	{
		SM1_Tick(sm1_state);
		/*if (SM1_elapsedTime >= 100)
		{
			//SM1_Tick();
			SM1_elapsedTime = 0;
		}
		if (SM2_elapsedTime >= 100)
		{
			SM2_Tick();
			SM2_elapsedTime = 0;
		}
		while (!TimerFlag) {}
			TimerFlag = 0;
			SM1_elapsedTime += timerPeriod;
			SM2_elapsedTime += timerPeriod;*/
	}
	
	return 1;
}
