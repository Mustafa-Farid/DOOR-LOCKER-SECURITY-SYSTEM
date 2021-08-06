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

// this functions is responsible of taking password from the user
// this array which the password will store in

void getPassword(uint8 array[])
{
	sint8 i;
	uint8 key;
	for (i = 0 ; i < 5 ; i++ )
	{
		key = KeyPad_getPressedKey();
		// last element in password
		if(i == 4)
		{
			/*
			 * reset the password in case of miss writing it
			 */
			if ( key == '*')
			{
				LCD_displayStringRowColumn(1, 0, "                ");
							i = -1;
							continue ;
			}
			// enter
			else if(key == 13)
			{
				break;
			}
			else
			{
				i = i-1;
				continue;
			}
		}
		// first 3 elements of the password
		else
		{

			/*
				* reset the password in case of miss writing it
			 */
					if (key == '*')
					{
						LCD_displayStringRowColumn(1, 0, "                ");
						i = -1;
						continue ;
					}
					// full filling the password array
					else if (key >= 0 && key<=9)
					{
						array[i] = key;
					}
					// in case of entering wrong number
					else
					{
						i = i-1;
						continue;
					}
					_delay_ms(500);
					LCD_goToRowColumn(1 , i);
					LCD_displayCharacter('*');
		}


	}

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
