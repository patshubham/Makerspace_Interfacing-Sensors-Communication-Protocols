/*
 * timer1.c
 *
 * Created: 2/2/2019 5:37:41 PM
 * Author : Siddharth Reddy
 */ 

#include <avr/io.h>
#define F_CPU 1000000
void Delay()
{
	TCCR0 = (1<<CS02) | (1<<CS00) | (1<<CS01);
	TCCR0 = ~(1<<WGM01) | ~(1<< WGM00);
	
	
	TCNT0 = 5;
	while((TIFR&(1<<TOV0))==0);
	TIFR = (1<<TOV0);
}




int main(void)
{{
	DDRB|=1<<PINB0;
	while(1)
	{
		PORTB ^=1 << PINB0;
		Delay();
	}
}



{

	TCNT0 =0xBA;
	TCCR0 =0x01;
	while ((TIFR & 0x1)==0);
	TCCR0 = 0;
	TIFR =0x1;

}
}

