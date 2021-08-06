 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Date: 12/9/2020
 *
 * Description: header file  TIMER0
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/***************************************** Type Decleration *****************************************
 *
 ******************************************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer0_Clock;

typedef struct
{
	Timer0_Clock clock;

}Timer0_ConfigType;

/***************************************** Function Decelerations *****************************************
 *
 ******************************************************************************************************/

/* Description :
 * For clock=8Mhz and prescale F_CPU/256 every count will take 32micro second
 * so put initial timer counter = 0  0 --> 255 (8.192ms per overflow)
 * so we need timer to overflow 144 times to count 1 second
 */
void timer0_init_normal_mode(Timer0_ConfigType *Config_Ptr);


#endif /* TIMER0_H_ */
