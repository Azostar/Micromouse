/*
 * mouse.c
 *
 * Created: 29/01/2019 12:39:19
 * Author : Rich
 */

#include "hardware.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "motors.h"

#define SPEED         90    // this is the speed the robot will drive at (range 0 - 255).
#define STARTSPEED    120    // initial speed to overcome stiction
#define STARTTIME     150   // drive 'blind' for this many ms to overcome stiction
#define Rbias         0     // no two motors are the same. Adjust this if your robot does not follow a straight line on a plain matt black surface
#define Lbias         0     // no two motors are the same. Adjust this if your robot does not follow a straight line on a plain matt black surface

long left;        // a long 32 bit number used for the left sensor measurement
long right;       // a long 32 bit number used for the right sensor measurement
int error;        // the error from the line. The magnitude indicates how far from the line
// and the sign which side of the line we are on.

float Kp = 0.15; // this is initial value. It will probably need changing!

float FBVal;      // the feedback value from the sensors and the P controller
// which will be used to change the motors speed
int LSpeed = 0;   // variable to store the final PWM value for the left motor
int RSpeed = 0;   // variable to store the final PWM value for the right motor


int ADC_Conversion(void)
{
	ADCSRA |= 1<<ADSC;		//Slide 31
	while(ADCSRA & 1<<ADSC);	//Slide 32
	return(ADC);		//Slide 23
}

void printValue(char string[], int value){
	char temp[50];
	_delay_ms(100);
	sprintf(temp,string,value);
	simpleprintf(temp);
}

/*-------------------------------------*/


int main(void)
{
	setup();		// a function in hardware.c that sets up the micro's registers etc

	setLMOTOR(0, FORWARDS);
	setRMOTOR(0, FORWARDS);

	// to see printf etc, plug the usb cable into the arduino nano module. Use Cool term (preferably) or bray's terminal to monitor output. This will prove invaluable for debugging.
	simpleprintf("Aston Mouse with AVR C");

	// turn on the GREEN LED
	PORTB |= 1 << GREENLED;

	// wait for BUT1 to be pressed
	while ( PIND & (1 << BUTTON1) );
	_delay_ms(1000);
	
	// turn the RED LED on.
	PORTD |= 1 << REDLED;	
	// enable motors
	PORTB |= 1 << ENMOTORS;
	setLMOTOR(STARTSPEED, FORWARDS);    // Set the speed
	setRMOTOR(STARTSPEED, FORWARDS);
	_delay_ms(STARTTIME);
	/* Replace with your application code */
    while (1)
    {
		// you need to add code here and in the setup function to use your sensors.
		ADMUX = LEFTSENS;
		left = ADC_Conversion();
		//printValue("Left Sensor: %d", left);
		ADMUX = RIGHTSENS;
		right = ADC_Conversion();
		//printValue("Right Sensor: %d", right);
		// code here needs to follow a line. This example just sets the left motor to spin backwards after the user presses button 1.
		error = left - right;
		//printValue("Error Value: %d", error);

		FBVal = error * Kp;                       // work out the proportional term, you may try adding integral and derviative terms!
		//printValue("Forward Bias: %d", FBVal);
		// the proportional term is simply the error multiplied by a coeffficient, Kp

		// calculate the final PWM value, i.e. our speed plus the correcion. Bias is used to counteract any difference in the
		// motors.
		LSpeed = (SPEED + Lbias)  -FBVal;           // this forms a rotational controller. We speed the left wheel up
		//printValue("Left Speed: %d", LSpeed);
		RSpeed = (SPEED + Rbias ) +FBVal;           // and speed the right wheel down. If your robot corrects the wrong way,
		//printValue("Right Speed: %d", RSpeed);
		//^                 // swap the signs of the plus and minus as shown
		
		// constrain the range of PWM values
		if ( LSpeed > 255 )
		LSpeed = 255;
		if ( LSpeed < 0 )
		LSpeed = 0;
		if ( RSpeed > 255 )
		RSpeed = 255;
		if ( RSpeed < 0 )
		RSpeed = 0;

    	setRMOTOR(RSpeed, FORWARDS);
		setLMOTOR(LSpeed, FORWARDS);

		if ( !(PINB & (1 << BUTTON2)) )	// if button 2 is pressed, stop the motors.
		{
			setLMOTOR(0, FORWARDS);
			setRMOTOR(0, FORWARDS);
			PORTB &= ~(1 << ENMOTORS);
			while(1);
		}
    }
}


