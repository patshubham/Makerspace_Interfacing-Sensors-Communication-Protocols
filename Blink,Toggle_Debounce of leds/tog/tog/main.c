/*
 * tog.c
 *
 * Created: 1/27/2019 4:03:44 PM
 * Author : Siddharth Reddy
 */ 

//LED start

#include <avr/io.h>
int main(void)
{
	DDRB = 0b00000001; //Data Direction Register setting pin0 to output and the remaining pins as input
	PORTB = 0b00000001; //Set pin0 to 5 volts
	while(1)
	{
		//Code would be in here if it needed to execute over and over and over ... endlessly
	}
}
//LED Blink

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 1 << PINB0;
	while (1)
	{
		PORTB ^= 1 << PINB0;
		_delay_ms(100);
	}
}

/*Button Debouncing*/

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB |= 1 << PINB0; //Set Direction for output on PINB0
	PORTB |= 1 << PINB0; //Toggling only Pin 0 on port b
	DDRB |= 1 << PINB2; //Set Direction for Output on PINB2
	DDRB &= ~(1 << PINB1); //Data Direction Register input PINB1
	PORTB |= 1 << PINB1; //Set PINB1 to a high reading
	int Pressed = 0; //Initialize/Declare the Pressed variable

	while (1)
	{
		if (bit_is_clear(PINB, 1)) //Check is the button is pressed
		{
			//Make sure that the button was released first
			if (Pressed == 0)
			{
				PORTB ^= 1 << PINB0;
				_delay_ms(1000); //Toggle LED in pin 0
				PORTB ^= 1 << PINB2;
				_delay_ms(1000); //Toggle LED on pin 2
				Pressed = 1;
			}
		}
		else
		{
			//This code executes when the button is not pressed.
			Pressed = 0;
		}
	}
}

//Button Debouncing 2

int main(void)
{
	DDRB |= 1 << PINB0; //For Notes on what these actions mean
	PORTB ^= 1 << PINB0;
	DDRB |= 1 << PINB2;
	DDRB &= ~(1 << PINB1);
	PORTB |= 1 << PINB1;

	int Pressed = 0;
	int Pressed_Confidence_Level = 0; //Measure button press cofidence
	int Released_Confidence_Level = 0; //Measure button release confidence

	while (1)
	{
		if (bit_is_clear(PINB, 1))
		{
			Pressed_Confidence_Level ++; //Increase Pressed Conficence
			Released_Confidence_Level = 0; //Reset released button confidence since there is a button press
			if (Pressed_Confidence_Level >500) //Indicator of good button press
			{
				if (Pressed == 0)
				{
					PORTB ^= 1 << PINB0;
					PORTB ^= 1 << PINB2;
					Pressed = 1;
				}
				//Zero it so a new pressed condition can be evaluated
				Pressed_Confidence_Level = 0;
			}
		}
		else
		{
			Released_Confidence_Level ++; //This works just like the pressed
			Pressed_Confidence_Level = 0; //Reset pressed button confidence since the button is released
			if (Released_Confidence_Level >500
			{
				Pressed = 0;
				Released_Confidence_Level = 0;
			}
		}
	}
}



//Button Game

#include <avr/io.h>
#include <util/delay.h>

void ProcessPressedButton(int ButtonPressed);
void ProcessReleasedButton(int ButtonReleased);
int Pressed_Confidence_Level[2];
int Released_Confidence_Level[2];
int Pressed[2];
int LEDNumber[2];
int main(void)
{
	DDRB = 0b01111111;
	DDRD = 0b01111111;
	PORTB = 0b10000000;
	PORTD = 0b10000000;

	while (1)
	{
		if (bit_is_clear(PINB, 7))
		{
			ProcessPressedButton(0);
		}
		else
		{
			ProcessReleasedButton(0);
		}
		if (bit_is_clear(PIND, 7))
		{
			ProcessPressedButton(1);
		}
		else
		{
			ProcessReleasedButton(1);
		}
	}
}

void ProcessPressedButton(int ButtonPressed)
{
	Pressed_Confidence_Level[ButtonPressed] ++;
	if (Pressed_Confidence_Level[ButtonPressed] > 500)
	{
		if (Pressed[ButtonPressed] == 0)
		{
			Pressed[ButtonPressed] = 1;
			if (ButtonPressed == 0) PORTB |= 1 << LEDNumber[ButtonPressed];
			if (ButtonPressed == 1) PORTD |= 1 << LEDNumber[ButtonPressed];
			LEDNumber[ButtonPressed] ++;
			if (LEDNumber[ButtonPressed] >6)
			{
				for(int i=0;i < 10;i++)
				{
					if (ButtonPressed == 0) PORTB = 0b11111111;
					if (ButtonPressed == 1) PORTD = 0b11111111;
					_delay_ms(10);
					if (ButtonPressed == 0) PORTB = 0b10000000;
					if (ButtonPressed == 1) PORTD = 0b10000000;
					_delay_ms(10);
				}
				LEDNumber[0] = 0;
				LEDNumber[1] = 0;
				PORTB = 0b10000000;
				PORTD = 0b10000000;
			}
		}
		Pressed_Confidence_Level[ButtonPressed] = 0;
	}
}

void ProcessReleasedButton(int ButtonReleased)
{
	Released_Confidence_Level[ButtonReleased] ++;
	if (Released_Confidence_Level[ButtonReleased] > 500)
	{
		Pressed[ButtonReleased] = 0;
		Released_Confidence_Level[ButtonReleased] = 0;
	}
}

