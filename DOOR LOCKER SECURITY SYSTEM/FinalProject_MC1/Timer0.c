 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.c
 *
 * Date: 12/9/2020
 *
 * Description: source file  TIMER0
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#include"Timer0.h"

/**********************************************************************************************
 * 								GLOBAL Variables
 *
 *********************************************************************************************/
uint8 g_tick;							// ticker counts how many ISR been executed
uint8 seconds;							// when ISR executed 144 so seconds increment by one
#define NUMBER_OF_OVS_PER_SECOND 144	// numbers of ISR to count a second



/************************************** interrupt Routine Service *****************************
 *
 ********************************************************************************************/
// every 144 interrupt will happen it will be one second
ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVS_PER_SECOND)
	{
		seconds++;
		g_tick = 0;
	}
}


/************************************** function Definitions ********************************
 *
 ********************************************************************************************/

/* Description :
 * For clock=8Mhz and prescale F_CPU/256 every count will take 32micro second
 * so put initial timer counter = 0  0 --> 255 (8.192ms per overflow)
 * so we need timer to overflow 144 times to count 1 second
 */
void timer0_init_normal_mode(Timer0_ConfigType *Config_Ptr)
{
	TCNT0 = 0; //Set Timer initial value to 0
	TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 	  configurable Cock
	 */

	TCCR0 = (1<<FOC0) ;
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
	seconds = 0;			// every time Timer0 initialize seconds will be zero
}
