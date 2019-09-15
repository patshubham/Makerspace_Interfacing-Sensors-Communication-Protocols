/*
 * GccApplication8.c
 *
 * Created: 09-02-2019 14:26:45
 * Author : Shubham
 */ 
h>
#include <util/delay.h>
#include <string.h>
#define F_CPU 8000000UL// Clock Speed
#include <avr/io.h>
#include <stdio.h>
//#define BAUD 9600
//#define myubrr (F_CPU/(16*BAUD))-1

void UART_Initialize( unsigned int ubrr );
void UART_Transmit( unsigned char data );
unsigned char UART_Receive( void );

int main(void)
{
	
	char mystr[] = "SensorKit";	
	unsigned int strLength = strlen(mystr);
	unsigned int i = 0;
	UART_Initialize (51); //function calling
	while(1)
	{
		//x=UART_Receive();/
		//_delay_ms(10);/
		UART_Transmit(mystr[i++]);
		_delay_ms(100);
		if(i >= strLength)
		i = 0;
	}
	return(0);
}



void UART_Initialize( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B |= (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C |= (1<<USBS)|(3<<UCSZ0);
}


void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


unsigned char UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
