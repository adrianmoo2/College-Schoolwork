#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	
	unsigned short my_short = ADC;
	
	unsigned char tempOne = 0x00;
	unsigned char tempTwo = 0x00;
	
	while (1)
	{
		//PORTB = 0xFF;
		//PORTD = 0xFF;
		
		my_short = ADC;
		tempOne = (char)my_short;
		tempTwo = (char)(my_short >> 8);
		tempTwo = tempTwo & 0x03;
		//PORTB = ~tempOne;
		//PORTD = ~tempTwo;
		if (my_short >= 0x02EF)
		{
			PORTB = 0x08;
		}
		else
		{
			PORTB = 0x00;
		}
	}
}