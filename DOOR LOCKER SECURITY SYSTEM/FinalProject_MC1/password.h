 /******************************************************************************
 *
 * Module: password.h
 *
 * File Name: password.h
 *
 * Date: 12/9/2020
 *
 * Description: header file for password
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "keypad.h"
#include "lcd.h"

void getPassword(uint8 array[]);

void readyToSend(uint8 array[], uint8 array2[]);

#endif /* PASSWORD_H_ */
