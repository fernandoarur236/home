/*
 * LCD_cfg.h
 *
 *  Created on: 22 Aug 2022
 *      Author: 20109
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

#define LCD_DATA_PORT PORTC_ID

#define LCD_EN_PORT PORTA_ID
#define LCD_EN_PIN  PIN6_ID

#define LCD_RW_PORT PORTA_ID
#define LCD_RW_PIN  PIN4_ID

#define LCD_RS_PORT PORTA_ID
#define LCD_RS_PIN  PIN7_ID

/*Case of 4bit mode this is used*/
#define LCD_D4_ID PIN4_ID
#define LCD_D5_ID PIN5_ID
#define LCD_D6_ID PIN6_ID
#define LCD_D7_ID PIN7_ID

/*Not yet used*/
#define LCD_VCC_PORT PORTC_ID
#define LCD_VCC_PIN  PIN3_ID

#define LCD_MODE FOUR_BIT_MODE


#endif /* HAL_LCD_LCD_CFG_H_ */
