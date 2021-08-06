 /******************************************************************************
 *
 * Module: password
 *
 * File Name: password.c
 *
 * Date: 12/9/2020
 *
 * Description: Source file for password
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#include"password.h"

/******************************** Function Definitions************************************/



// this function will check the password which being sent by comparing it with the password in the external EEPROM

uint8 PW_checkPassword(uint8 array1[] , uint8 array2[])
{
	uint8 compare = 0;
	for(int i = 0 ; i < PASSWORD_DIGITS ; i++)
	{
		if(array1[i] == array2[i])
		{
			compare ++;
		}
	}

	if(compare == PASSWORD_DIGITS)
		return TRUE;
	else
		return FALSE;
}


 /*
  * we will change the password into a string to be sent
  * this function will take two arrays array 1 is the passowrd as number
  * and array2 is where we store the string
  */
void readyToSend(uint8 array1[], uint8 array2[])
 {
	sint8 i ;
	for(i = 0 ; i < 5 ; i++)
	{
		if(i==4)
		{
			array2[i] = '#';		//making last element of the array2 # as finishing the string
		}
		else
		{
		array2[i] = array1[i];		// storing all element of array1 into array2
		}
	}

 }
