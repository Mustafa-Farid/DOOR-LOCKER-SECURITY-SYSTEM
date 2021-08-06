 /******************************************************************************
 *
 * Module: password
 *
 * File Name: password.h
 *
 * Date: 12/9/2020
 *
 * Description: headere file for password
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define PASSWORD_DIGITS 4

void getPassword(uint8 array[]);

uint8 PW_checkPassword(uint8 array1[] , uint8 array2[]);

void readyToSend(uint8 array[], uint8 array2[]);


#endif /* PASSWORD_H_ */
