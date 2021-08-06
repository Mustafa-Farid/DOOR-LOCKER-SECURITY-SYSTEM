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

#include"MC1.h"

//********************************* Global Variables ***********************************



int main (void)
{
	//********************************* Global Variables ***********************************

	/*
	 * a_firstPassword array of five elements to get first password wanted to be saved
	 * a_secondPassword is a second array of five elements to approve the password had been entered
	 * a_message array of five elements to make password ready to be sent by UART to another micro controller
	 * a_oldPass and a_oldPassMess is two array of five elements to store and send the old password
	 * firstTimeFlag is a flag to know if password already saved or no
	 * compare is a flag to know if the password entered is same with the approval password
	 * memValue is a unsigned character to hold the value in a memory to check if its first time to enter the program or not
	 * operation , screen and state are flags to control which screen to be shown in LCD
	 * wrongPW is a counter to count how many invalid password has been entered
	 */
	uint8 a_firstPassword[5];
	uint8 a_secondPassword[5];
	uint8 a_message[5];
	uint8 a_oldPass[5];
	uint8 a_oldPassMess[5];
	static uint8 firstTimeFlag = 0;
	uint8 compare ;
	uint8 memValue;
	uint8 operation;
	uint8 screen = 0;
	uint8 state;
	uint8 wrongPW = 0;
	/*
	 * structures to configure Modules
	 */
	Timer0_ConfigType Timer0_Config = {F_CPU_256};
	UART_ConfigType UART_Config = { ENABLED_EVEN , TWO_BIT_STOP , EIGHT_BIT};
	// ******************************** initialize modules***********************************
	LCD_init();
	UART_init(&UART_Config);
	SREG |=(1<<7);
	_delay_ms(50);
	while(1)
	{
		memValue = eeprom_read_byte((uint8 *)INTERNAL_MEMORY_ADD);
		if(memValue != INTERNAL_MEMORY_DATA)
		{
			firstTimeFlag = 0;
		}
		else if (memValue == INTERNAL_MEMORY_DATA)
		{
			firstTimeFlag = 1;
		}
		if(firstTimeFlag == 0)
			{

				LCD_displayString("enter 4 digit PW");
				getPassword(a_firstPassword);
				LCD_clearScreen();
				LCD_displayString("Re-enter 4 digit PW");
				getPassword(a_secondPassword);
				compare = strcmp(a_firstPassword ,a_secondPassword );
				if(compare == 0)
				{
					eeprom_write_byte((uint8 *)INTERNAL_MEMORY_ADD,INTERNAL_MEMORY_DATA);

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "password");
					LCD_displayStringRowColumn(1, 0, "Match");
					_delay_ms(1000);
					readyToSend(a_firstPassword , a_message);
					UART_sendByte(SAVE_PASSWORD);
					UART_sendString(a_message);

				}
				else
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "password");
					LCD_displayStringRowColumn(1, 0, " don't Match");
					_delay_ms(1000);
					LCD_clearScreen();

				}
			}
		else if(firstTimeFlag == 1)
		{
			if(screen == 0)
			{

				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "0:Open Door");
				LCD_displayStringRowColumn(1, 0, "1:Change PW");
				operation = KeyPad_getPressedKey();
				_delay_ms(400);
				if(operation == 0)
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "please enter PW");
					getPassword(a_firstPassword);
					readyToSend(a_firstPassword , a_message);
					UART_sendByte(OPEN_DOOR);
					UART_sendString(a_message);
					screen = 1;
				}
				else if(operation == 1)
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, " enter old PW");
					getPassword(a_firstPassword);
					for(uint8 i = 0 ; i < 5 ; i++)						// FIXING approving change password BUG
					{
						a_oldPass[i] = a_firstPassword[i];
					}
					readyToSend(a_oldPass , a_oldPassMess);				// END
					readyToSend(a_firstPassword , a_message);
					UART_sendByte(CHANGE_PASSWORD);
					UART_sendString(a_message);
					screen = 2 ;
				}
			}
			else if(screen == 1)
			{
				state = UART_recieveByte();
				LCD_clearScreen();
				if(state == CORRECT_PW)
				{
					LCD_displayStringRowColumn(0, 0, "OPENING DOOR 10s");
					timer0_init_normal_mode(&Timer0_Config);

					while(seconds != 10)
					{
						LCD_goToRowColumn(1,0);
						LCD_intgerToString(seconds+1);
					}
					seconds = 0;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "CLOSING DOOR 10s");
					timer0_init_normal_mode(&Timer0_Config);
					while(seconds != 10)
					{
						LCD_goToRowColumn(1,0);
						LCD_intgerToString(seconds+1);
					}
					LCD_clearScreen();
					wrongPW = 0;
					state = 0;
					screen = 0;
				}
				else if(state == WRONG_PASSWORD)
				{
					if(wrongPW != 3)
					{
					LCD_displayStringRowColumn(0, 0, "WRONG PW TRY AGAIN");
					_delay_ms(2000);
					}
					wrongPW++;
					screen = 0;
					state  = 0;
					if(wrongPW == 3)
					{
						LCD_displayStringRowColumn(0, 0, " ALARM !!!      ");
						timer0_init_normal_mode(&Timer0_Config);
						while(seconds != 10);
						wrongPW = 0;
						screen = 0;
						state  = 0;
					}

				}
			}
			else if(screen == 2)
			{
				state = UART_recieveByte();
				LCD_clearScreen();
				if (state == CORRECT_PW)
				{


					LCD_displayStringRowColumn(0, 0,"Enter 4-digit PW      ");
					getPassword(a_firstPassword);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Reenter 4-digit PW");
					getPassword(a_secondPassword);
					compare = strcmp(a_firstPassword ,a_secondPassword );
					if(compare == 0)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "password");
						LCD_displayStringRowColumn(1, 0, "Match");
						_delay_ms(1000);
						readyToSend(a_firstPassword , a_message);
						UART_sendByte(NEW_PASSWORD);
						UART_sendString(a_message);
						screen = 0;
						state  = 0;
					}
					else
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "password");
						LCD_displayStringRowColumn(1, 0, " don't Match");
						_delay_ms(1000);
						UART_sendByte(NEW_PASSWORD);
						UART_sendString(a_oldPassMess);
						LCD_clearScreen();

					}
					screen = 0;
				}
				else if (state == WRONG_PASSWORD)
				{

					LCD_displayStringRowColumn(0, 0, "WRONG PW TRY AGAIN");
					_delay_ms(2000);
					wrongPW++;
					screen = 0;
					state  = 0;
					if(wrongPW == 3)
					{
						LCD_displayStringRowColumn(0, 0, " ALARM !!!      ");
						timer0_init_normal_mode(&Timer0_Config);
						while(seconds != 10);
						wrongPW = 0;
						screen = 0;
						state  = 0;
					}
				}
			}

		}
	}

}
