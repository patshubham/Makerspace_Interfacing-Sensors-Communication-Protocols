/*
 * ir sen 1.c
 *
 * Created: 1/28/2019 7:39:47 PM
 * Author : Siddharth Reddy
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PINB0);
	DDRB |= (1<<PINB2);
	DDRB &= ~(1<<PINB1);
	
	
	void glow()
	{
		PORTB &= ~(1<<PINB2);
		PORTB ^= (1<<PINB0);
		
		
		
	}
	void off()
	{
		PORTB &= ~(1<<PINB0);
		PORTB ^= (1<<PINB2);
		
		
	}
	
	while (1)
	{
		if (PINB1 == 0b00000010)
		{
			glow();
			_delay_ms(1000);
		}
		else
		{
			off();
			_delay_ms(1000);
		}
	}
}


