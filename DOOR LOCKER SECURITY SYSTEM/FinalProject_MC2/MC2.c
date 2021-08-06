 /******************************************************************************
 *
 * Module: MC2
 *
 * File Name: MC2.c
 *
 * Date: 12/9/2020
 *
 * Description: Source file for second  micro controller
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/
#include"MC2.h"
uint8 seconds=0;

int main(void)
{
	//*********************************** Global Variables ************************************

	/*
	 * newPassword array of 5 elements to get the new password
	 * openPassword array of five elements to get the open password of the door
	 * changePassword array of five elements to to get the change password
	 * buffer an array to get the stored password in the EEPROM
	 * state and screen are flags to indicate the state of the microcontroller
	 * checkPassword is a flag to indicate if the password eneterd is true or not
	 * wrongCount counter to know how many password had been entered wrong
	 */
	uint8 newPassword[N];
	uint8 openPassword[N];
	uint8 changePassword[N];
	uint8 buffer[N];
	uint8 state = 0;
	uint8 screen = 0;
	uint8 checkPassword;
	uint8 wrongCount = 0;

	// structures to Configure modules

	Timer0_ConfigType Timer0_Config = {F_CPU_256};
	UART_ConfigType UART_Config = { ENABLED_EVEN , TWO_BIT_STOP , EIGHT_BIT};
	//*********************************** Initializing drivers ********************************
	TWI_init();
	UART_init(&UART_Config);
	EEPROM_init();
	SREG |= (1<<7);
	DCMOTOR_Init();
	_delay_ms(50);

	DDRD |= (1<<PD7);			// BUZZER output
	PORTD &= ~(1<<PD7);			// initially buzzer OFF
	while(1)
	{
		if(screen == 0)
		{
			state = UART_recieveByte();
			if (state == SAVE_PASSWORD)
			{
				UART_receiveString(newPassword);
				screen = 1;
				state = 0;
			}

			else if (state == OPEN_DOOR)
			{
				UART_receiveString(openPassword);
				screen = 2;
				state = 0;
			}
			else if (state == CHANGE_PASSWORD)
			{
				UART_receiveString(openPassword);
				screen = 3;
				state = 0;
			}

		}

		else if(screen == 1)
		{
			sint8 i = 0 ;
			while (newPassword[i] != '\0')
			{
				 EEPROM_writeByte(FIRST_LOC_EEPROM +i , newPassword[i]);
				 _delay_ms(50);
				 i++;
			}
			screen = 0;
		}
		else if(screen == 2)
		{
			EEPROM_readPassword(buffer,N);
			checkPassword = PW_checkPassword(buffer , openPassword);
			if(checkPassword == TRUE)
			{
				UART_sendByte(CORRECT_PW);
				DCMOTOR_onClockWise(MED_SPEED);
				timer0_init_normal_mode(&Timer0_Config);
				while(seconds != 10);
				DCMOTOR_onAntiClockWise(MED_SPEED);
				timer0_init_normal_mode(&Timer0_Config);
				while(seconds != 10);
				DCMOTOR_stop();
				wrongCount = 0;
				screen = 0;

			}
			else
			{
				UART_sendByte(WRONG_PASSWORD);
				wrongCount++;
				if(wrongCount == 3)
				{
					PORTD |= (1<<PD7);
					timer0_init_normal_mode(&Timer0_Config);
					while(seconds != 10);
					PORTD &= ~(1<<PD7);
					wrongCount = 0;
					screen = 0;
				}
				screen = 0;
			}

		}
		else if (screen == 3)
		{
			EEPROM_readPassword(buffer,N);
			checkPassword = PW_checkPassword(buffer , openPassword);
			if(checkPassword == TRUE)
			{
				UART_sendByte(CORRECT_PW);
				while(UART_recieveByte() != NEW_PASSWORD );
				UART_receiveString(changePassword);
				sint8 i = 0 ;
				while (changePassword[i] != '\0')
				{
					 EEPROM_writeByte(FIRST_LOC_EEPROM +i , changePassword[i]);
					 _delay_ms(50);
					 i++;
				}
				wrongCount = 0;
				screen = 0;
			}
			else
			{
				UART_sendByte(WRONG_PASSWORD);
				wrongCount++;
				if(wrongCount == 3)
				{
					PORTD |= (1<<PD7);
					timer0_init_normal_mode(&Timer0_Config);
					while(seconds != 10);
					PORTD &= ~(1<<PD7);
					wrongCount = 0;
					screen = 0;
				}
			screen = 0;
			}
		}

	}
}
