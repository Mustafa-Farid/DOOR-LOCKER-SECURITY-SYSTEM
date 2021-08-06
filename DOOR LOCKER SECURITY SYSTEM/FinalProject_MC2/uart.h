 /******************************************************************************
 *
 * Module: uart
 *
 * File Name: uart.h
 *
 * Date: 12/9/2020
 *
 * Description: header file for UART
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE	9600
// UART MESSAGES
#define CHECK_PASSWORD	0x0A
#define SAVE_PASSWORD	0x0B
#define WRONG_PASSWORD  0x0C
#define OPEN_DOOR		0x0D
#define CHANGE_PASSWORD 0x0E
#define CORRECT_PW		0x0F
#define NEW_PASSWORD	0x10
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	DISABLED=0,ENABLED_EVEN=2,ENABLED_ODD=3
}UART_ParityType;

typedef enum
{
	ONE_BIT_STOP,TWO_BIT_STOP
}UART_StopBit;

typedef enum
{
	FIVE_BIT,SIX_BIT,SEVEN_BYTE,EIGHT_BIT
}UART_CharSize;

typedef struct
{
	UART_ParityType parity;
	UART_StopBit 	stopBit;
	UART_CharSize	charSize;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(UART_ConfigType *Config_PTR);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
