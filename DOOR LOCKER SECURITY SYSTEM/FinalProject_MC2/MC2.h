 /******************************************************************************
 *
 * Module: MC2
 *
 * File Name: MC2.h
 *
 * Date: 12/9/2020
 *
 * Description: header file for second  micro controller
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef MC2_H_
#define MC2_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#include"Timer0.h"
#include"uart.h"
#include"i2c.h"
#include"external_eeprom.h"
#include<string.h>
#include<avr/eeprom.h>
#include"password.h"
#include"lcd.h"
#include"DC_Motor.h"

extern uint8 seconds;

#define FIRST_LOC_EEPROM 0x0311
#define N 5
#define MED_SPEED 	20000
#define HIGH_SPEED	50000

#endif /* MC2_H_ */
