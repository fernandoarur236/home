/*
 * EEPROM_reg.h
 *
 *  Created on: 31 Dec 2022
 *      Author: 20109
 */

#ifndef MCAL_EEPROM_EEPROM_REG_H_
#define MCAL_EEPROM_EEPROM_REG_H_

#define EEARL	*((volatile u8*) 0x3E)
#define EEARH	*((volatile u8*) 0x3F)
#define EEAR	*((volatile u8*) 0x3E)

/* The EEPROM Data Register */
#define EEDR	*((volatile u8*) 0x3D)

/* The EEPROM Control Register  */
#define EECR	*((volatile u8*) 0x3C)
/* Bits */
#define EERE	0
#define EEWE	1
#define EEMWE	2
#define EERIE	3

#endif /* MCAL_EEPROM_EEPROM_REG_H_ */
