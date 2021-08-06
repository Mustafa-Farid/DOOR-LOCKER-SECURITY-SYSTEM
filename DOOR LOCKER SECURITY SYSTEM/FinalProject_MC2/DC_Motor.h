 /******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.h
 *
 * Date: 12/9/2020
 *
 * Description: header file for DC motor
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define MOTOR_DIRECTION DDRC
#define MOTOR_OUTPUT PORTC
#define IN1 PC2
#define IN2 PC3
#define TOP 50000
void DCMOTOR_Init();
void DCMOTOR_onClockWise(uint16 duty_cycle);
void DCMOTOR_onAntiClockWise(uint16 duty_cycle);
void DCMOTOR_stop();

#endif /* DC_MOTOR_H_ */
