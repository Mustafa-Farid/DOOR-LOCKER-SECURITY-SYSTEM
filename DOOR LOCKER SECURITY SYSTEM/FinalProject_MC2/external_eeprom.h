/******************************************************************************
 *
 * Module: external_eeprom
 *
 * File Name: external_eeprom.h
 *
 * Date: 12/9/2020
 *
 * Description: header file for external_eeprom
 *
 * Author: Mustafa Farid
 *
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1
#define FIRST_LOC_EEPROM 0x0311
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
void EEPROM_readPassword(uint8 buffer[],uint8 k);
 
#endif /* EXTERNAL_EEPROM_H_ */
