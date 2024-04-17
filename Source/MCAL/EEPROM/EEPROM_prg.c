/*
 * EEPROM_prg.c
 *
 *  Created on: 31 Dec 2022
 *      Author: 20109
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EEPROM_int.h"
#include "EEPROM_reg.h"

void EEPROM_vWrite(u16 A_u16Address, u8 A_u16Data){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = A_u16Address;
	EEDR = A_u16Data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

u8 EEPROM_u8Read(u16 A_u16Address){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = A_u16Address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

