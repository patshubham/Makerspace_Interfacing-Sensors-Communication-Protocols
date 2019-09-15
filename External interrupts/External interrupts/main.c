/*
 * External interrupts.c
 *
 * Created: 2/2/2019 10:33:32 AM
 * Author : Siddharth Reddy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>




int main(void)
{
    DDRE &= ~(1<<PINE6);
	DDRB |= (1<<PINB1);
	DDRB |= (1<<PINB0);
	PORTE |= (1<<PINE6);
	
	EICRB &= ~(1<<ISC61);
	EICRB |= (1<<ISC60);
	EIMSK |= (1<<INT6);
	sei();
	
	
    while (1) 
    {
		PORTB ^= (1<<PINB0);
		_delay_ms(1000);
	}
}

ISR(INT6_vect)
{
	PORTB &= ~(1<<PINB0);
	PORTB |= (1<<PINB1);
	_delay_ms(1000);
	PORTB &= ~(1<<PINB1); 
	
}

