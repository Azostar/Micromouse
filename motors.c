/*
 * motors.c
 *
 *  Created on: 2 Feb 2019
 *      Author: richardnock
 */
#include "hardware.h"
#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"


/****************************************************************************************
 * This function controls the direction and speed of the left motor
 * speedval controls the speed of the motor and can be in the range of 0-255
 * dir controls the direction of the motor, either FORWARDS or BACKWARDS
 *
 ***************************************************************************************/
void setLMOTOR ( unsigned char speedval, char dir )
{
    if ( dir == FORWARDS )
    {
    	if ( LFORWARDS )
    		PORTD |= 1 << LEFTDIR;
    	else
    	    PORTD &= ~(1 << LEFTDIR	);

    	leftPWM(255-speedval);  		// swap for speedval if you change LFORWARDS
    }
    else
    {
    	if ( !LFORWARDS )
    	    PORTD |= 1 << LEFTDIR;
    	else
    		PORTD &= ~(1 << LEFTDIR	);

    	leftPWM(speedval); 				// swap for 255-speedval; if you change LFORWARDS
    }
}
/****************************************************************************************
 * This function controls the direction and speed of the right motor
 * speedval controls the speed of the motor and can be in the range of 0-255
 * dir controls the direction of the motor, either FORWARDS or BACKWARDS
 *
 ***************************************************************************************/
void setRMOTOR ( unsigned char speedval, char dir )
{
    if ( dir == FORWARDS )
    {
    	if ( RFORWARDS )
    	    PORTD |= 1 << RIGHTDIR;
    	else
    	    PORTD &= ~(1 << RIGHTDIR);

        rightPWM(255-speedval);  			// swap for speedval; if you change RFORWARDS
    }
    else
    {
    	if ( !RFORWARDS )
    		PORTD |= 1 << RIGHTDIR;
    	else
    		PORTD &= ~(1 << RIGHTDIR);

        rightPWM(speedval); 				// swap for 255-speedval; if you change RFORWARDS

    }
}

void leftPWM ( unsigned char pwmval )
{
	OCR0B = pwmval;
}

void rightPWM ( unsigned char pwmval )
{
	OCR0A = pwmval;
}
