/*
 * IR SEN.c
 *
 * Created: 1/27/2019 4:36:04 PM
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
		if (bit_is_clear(PINB,1))
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

