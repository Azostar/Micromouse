/*
 * hardware.c
 *
 *  Created on: 3 Feb 2019
 *      Author: richardnock
 */
#include "hardware.h"

#include <avr/io.h>
#include <util/delay.h>

void setup ( void )
{
	// setup UART
	UCSR0B = 1 << TXEN0;
	UBRR0 = 103;

	// setup DDR for motor control pins and LEDs
	DDRD |= 1 << LEFTPWM | 1 << RIGHTPWM | 1 << LEFTPWM | 1 << RIGHTPWM | 1 << REDLED;
	DDRB |= 1 << ENMOTORS | 1 << GREENLED;

	OCR0B = 128;
	OCR0A = 12;

	TCCR0A = 1 << COM0B1 | 1<< COM0A1 | 1 << WGM01 | 1 << WGM00;
	TCCR0B = 1 << CS01;
	
	// add code here to setup the ADC and add functions below
	ADMUX = 1<<REFS0 | 1<<MUX1 | 1<<MUX0;	//Slides 8 - 15
	DIDR0 = 1<<ADC3D | 1<< ADC2D;				//Slides 26 - 27
	ADCSRA = 1<<ADEN | 1<<ADPS2 | 1<<ADPS0;		//Slides 16 - 22
}

void PutChar ( char in )
{
	while((UCSR0A & 1 << UDRE0 ) == 0 );
	UDR0 = in;
}

void simpleprintf ( char string[] )
{
	int i = 0;
	while( string[i] != 0 )
	{
		PutChar(string[i]);
		i++;
	}
	PutChar('\r');
}
