/*
 * motors.h
 *
 *  Created on: 2 Feb 2019
 *      Author: richardnock
 */

#ifndef MOTORS_H_
#define MOTORS_H_

void setLMOTOR ( unsigned char speedval, char dir );
void setRMOTOR ( unsigned char speedval, char dir );
void rightPWM ( unsigned char pwmval );
void leftPWM ( unsigned char pwmval );

#endif /* MOTORS_H_ */
