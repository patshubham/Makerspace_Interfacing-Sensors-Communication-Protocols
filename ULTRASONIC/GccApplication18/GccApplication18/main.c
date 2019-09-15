/*
 * GccApplication18.c
 *
 * Created: 15-02-2019 06:42:22 PM
 * Author : Dhruv Patel
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define SCALE_FACTOR      3
#define clock_frequency     8000000UL
#define microseconds        clock_frequency/1000000
#define milliseconds        clock_frequency/1000
void init_usart(unsigned int baud);
void usart_putchar(char data);

void send2uart(char *buffer);
void send_ATcommand(char *buffer);
void print_uart(char *buffer);

char process_uart_data(char uart_buffer);



#define    BIT7    0x80
#define    BIT6    0x40
#define    BIT5    0x20
#define    BIT4    0x10
#define    BIT3    0x08
#define    BIT2    0x04
#define    BIT1    0x02
#define    BIT0    0x01


#define BAUD_9600     51


//#define BAUD_57600    8




char rx_buffer[20];  //rx buffer chat length
char buff_index;

void init_usart(unsigned int baud)   
{   
    UCSR0A=(0x00);   
    UCSR0B=0x98;      // reciever disabled, receive interrrupt disabled, tx enabled   
    UCSR0C=0x86;      // 8-bit mode   
    UBRR0H=baud>>8;   
    UBRR0L=baud;  
       
    }
 
void usart_putchar(char data)   
{   
   while(!(UCSR0A & BIT5));
   //Now write the data to USART buffer
   UDR0=data;      
} 

void send2uart(char *buffer)
{
  int i;
  for (i=0;buffer[i] != '\0' ;i++)
  usart_putchar(buffer[i]);
}

void send_ATcommand(char *buffer)
{
  send2uart(buffer);
  usart_putchar(0x0D);
}

void print_uart(char *buffer)
{
  int i;
  for (i=0;buffer[i] != '\0' ;i++)
  usart_putchar(buffer[i]);
  usart_putchar(0x0D);
  usart_putchar(0x0A);
  }


void integer_to_char(int integer_input, char* character_array, char type)
{
	int reminder,quotient;
	if (type == 2)
	{
		quotient = integer_input/10;
		reminder = integer_input%10;
		character_array[0] = quotient+0x30;
		character_array[1] = reminder+0x30;
		character_array[2] = '\0';
	}
	if (type == 3)
	{
		quotient = integer_input/100;
		reminder = integer_input%100;
		character_array[0] = quotient+0x30;
		quotient = reminder/10;
		reminder = reminder%10;
		character_array[1] = quotient+0x30;
		character_array[2] = reminder+0x30;
		character_array[3] = '\0';
	}
	if (type == 4)
	{
		quotient = integer_input/1000;	// 1234  -- 1
		reminder = integer_input%1000;	// 234
		character_array[0] = quotient+0x30;	    //'1'
		quotient = reminder/100;	       // 234  -- 2
		reminder = reminder%100;	       // 34
		character_array[1] = quotient+0x30;	  // '2'
		quotient = reminder/10;	        //  3
		reminder = reminder%10;
		character_array[2] = quotient+0x30;
		character_array[3] = reminder+0x30;
		character_array[4] = '\0';
	}
}


void hex_to_char(char hex,char character_array[3])
{
	if (((hex & 0xF0) >> 4 )>9)
	{
		character_array[0] = (((hex & 0xF0) >> 4 ) + 0x37);
	}
	else
	{
		character_array[0] = (((hex & 0xF0) >> 4 ) + 0x30);
	}
	if((hex & 0x0F)>9)
	{    character_array[1] = ((hex & 0x0F) + 0x37);
	}
	else
	{
		character_array[1] = ((hex & 0x0F) + 0x30);
	}
	character_array[2] = '\0';
}


char char2num(char character)
{
	char result = 0;
	if ((character >= 0x30) && (character <= 0x39))
	result =  (character-0x30);
	else
	result = 0;
	
	return result;
}


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int char_to_int(char character_array[3], char type)
{
	int integer = 0;
	if (type == 1)
	{
		integer += (character_array[0]-0x30);
	}
	else if (type == 2)
	{
		integer += ((character_array[0]-0x30)*10);
		integer += (character_array[1]-0x30);
	}
	else if (type == 3)
	{
		integer += ((character_array[0]-0x30)*100);
		integer += ((character_array[1]-0x30)*10);
		integer += (character_array[2]-0x30);
	}
	else if (type == 4)
	{
		integer += ((character_array[0]-0x30)*1000);
		integer += ((character_array[1]-0x30)*100);
		integer += ((character_array[2]-0x30)*10);
		integer += (character_array[3]-0x30);
	}
	return integer;
}
#define CON_CAT(a,b)                a ## b
#define DDR_(name)        CON_CAT(DDR,name)
#define PORT_(name)       CON_CAT(PORT,name)
#define PIN_(name)        CON_CAT(PIN,name)
#define BIT_(name)        CON_CAT(BIT,name)

/*Need to change according to connections*/
#define ULTRASONIC_PORT_IND        B              /*need to configure here */
#define ULTRASONIC_TRIGGER         0               /*need to configure trigger pin(0-7) */
#define ULTRASONIC_ECHO            1               /*need to configure echo pin(0-7) */

/*  ULTRASONIC 1  */

#define Ultrasonic_Triger_Port_Direction            DDR_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Triger_Port                      PORT_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Trigger_pin                      BIT_(ULTRASONIC_TRIGGER)


#define Ultrasonic_Echo_Port_Direction              DDR_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Echo_Port                        PORT_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Echo_Input                       PIN_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Echo_pin                         BIT_(ULTRASONIC_ECHO)

void init_Ultrasonic_sensor(void);
void trigger_Ultrasonic_sensor(void);
unsigned int read_Ultrasonic_sensor(void);
unsigned int get_distance_Ultrasonic_sensor(void);
unsigned int echo_duration;

void init_Ultrasonic_sensor(void)
{
	Ultrasonic_Triger_Port_Direction |= (Ultrasonic_Trigger_pin);    // Ultrasonic Trigger pin
	Ultrasonic_Triger_Port &= ~(Ultrasonic_Trigger_pin);   // Ultrasonic pin set to low
	
	Ultrasonic_Echo_Port_Direction &= ~(Ultrasonic_Echo_pin);   // Ultrasonic Echo pin set to input
	Ultrasonic_Echo_Port |= Ultrasonic_Echo_pin;      // Enable pullup
}

void trigger_Ultrasonic_sensor(void)
{
	Ultrasonic_Triger_Port &= ~(Ultrasonic_Trigger_pin);
	_delay_us(2);
	Ultrasonic_Triger_Port |= (Ultrasonic_Trigger_pin);
	_delay_us(10);
	Ultrasonic_Triger_Port &= ~(Ultrasonic_Trigger_pin);
}

unsigned int read_Ultrasonic_sensor(void)
{
	echo_duration = 0;
	while((Ultrasonic_Echo_Input&Ultrasonic_Echo_pin) != Ultrasonic_Echo_pin);
	while(((Ultrasonic_Echo_Input&Ultrasonic_Echo_pin) == Ultrasonic_Echo_pin) && (echo_duration<20000))
	{
		_delay_us(1);
		echo_duration++;
	}
	return echo_duration;
}


unsigned int get_distance_Ultrasonic_sensor(void)
{
	trigger_Ultrasonic_sensor();
	return read_Ultrasonic_sensor()/SCALE_FACTOR;
}

char data_buffer[4],buffer[50];

int distance = 0,c_m=0,m_m=0;

int convert_cm(int value)
{
 c_m = value/10;



  integer_to_char(c_m,data_buffer,3);
  send2uart(data_buffer);
  send2uart("cm");
  usart_putchar(0x0D);
  usart_putchar(0x0A);
  if(c_m<015)
  {
    sprintf(buffer,"OBSTACLE DETECTED\n");
	send2uart(buffer);
   }
}


int main(void)
{

_delay_ms(1000);
print_uart("OK");


DDRD&=~(BIT3);
PORTD |= BIT3;

init_Ultrasonic_sensor();

if((PIND&BIT3) == BIT3)
{
init_usart(BAUD_9600);
}
else
{
//init_usart(BAUD_57600);
}

while(1)
{
	distance = get_distance_Ultrasonic_sensor();
	convert_cm(distance);
	_delay_ms(100);
}

}

