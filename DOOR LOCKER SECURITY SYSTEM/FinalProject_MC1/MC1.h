 /******************************************************************************
 *
 * Module: MC1
 *
 * File Name: MC1.c
 *
 * Date: 12/9/2020
 *
 * Description: Source file first micro controller
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef MC1_H_
#define MC1_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#include"keypad.h"
#include"lcd.h"
#include"Timer0.h"
#include"uart.h"
#include"password.h"
#include<string.h>
#include<avr/eeprom.h>

extern uint8 seconds;

#define INTERNAL_MEMORY_ADD  0x0F
#define INTERNAL_MEMORY_DATA 0x10

#endif /* MC1_H_ */
