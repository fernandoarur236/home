/*
 * EEPROM_int.h
 *
 *  Created on: 31 Dec 2022
 *      Author: 20109
 */

#ifndef MCAL_EEPROM_EEPROM_INT_H_
#define MCAL_EEPROM_EEPROM_INT_H_

void EEPROM_vWrite(u16 A_u16Address, u8 A_u16Data);
u8 EEPROM_u8Read(u16 A_u16Address);

#endif /* MCAL_EEPROM_EEPROM_INT_H_ */
