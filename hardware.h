/*
 * hardware.h
 *
 *  Created on: 2 Feb 2019
 *      Author: richardnock
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

// function prototypes
void setup ( void );
void PutChar ( char in );
void simpleprintf ( char string[] );

// defines
#define F_CPU 16E6 // the crystal frequency is 16 MHz on the Arduino, uncomment if delays are not functioning as expected
#define HIGH 	1
#define LOW 	0

#define LEFTPWM		PD5
#define RIGHTPWM	PD6
#define LEFTDIR		PD2
#define RIGHTDIR	PD3
#define ENMOTORS	PB5

#define FORWARDS     HIGH  // do NOT change this
#define BACKWARDS    LOW   // do NOT change this

#define LFORWARDS    HIGH   // if your left motor runs backwards, change high to low or vice versa - other changes needed in SETLMOTOR
#define RFORWARDS    HIGH   // if your right motor runs backwards, change high to low or vice versa - other changes needed in SETRMOTOR

#define GREENLED	 PB1
#define REDLED 		 PD4

#define BUTTON1 	 PD7
#define BUTTON2 	 PB0
#define LEFTSENS	 1<<REFS0 | 1<<MUX1 | 1<<MUX0 // select an appropiate adc MUX
#define RIGHTSENS    1<<REFS0 | 1<<MUX2 | 1<<MUX0
#endif /* HARDWARE_H_ */
