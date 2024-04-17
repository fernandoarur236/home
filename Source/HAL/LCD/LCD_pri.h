/*
 * LCD_pri.h
 *
 *  Created on: 22 Aug 2022
 *      Author: 20109
 */

#ifndef HAL_LCD_LCD_PRI_H_
#define HAL_LCD_LCD_PRI_H_

/*Available modes*/
#define FOUR_BIT_MODE 1
#define EIGHT_BIT_MODE 0

/* Case of 4bit mode: HIGHEST_NIPPLE or LOWES_NIPPLE
 * Case of 8bit mode: N/A
 * */
#define HIGHEST_NIPPLE 1
#define LOWEST_NIPPLE  0
#define NA            2

/*Available commands*/

#define CMD_CLEAR_DISP      0b00000001
#define CMD_RETURN_HOME     0b00000010

/*Increment cursor when writing to the LCD*/
#define CMD_ENTRY_MODE_INC  0b00000110

/*Decreament cursor when writing to the LCD*/
#define CMD_ENTRY_MODE_DEC  0b00000100

/*Display on, cursor off*/
#define CMD_DISPLAY_ON      0b00001100

/*Display off*/
#define CMD_DISPLAY_OFF     0b00001000

/*Eight bit mode, 2 lines, 5x7 dots*/
#define CMD_EIGHT_BIT_MODE  0b00111000

/*Four bit mode, 2 lines, 5x7 dots*/
#define CMD_FOUR_BIT_MODE   0b00101000

/*You add the position (address) to this value*/
#define CMD_SET_CURSOR_POSITION 0b10000000

#define CMD_SHIFT_DISP_RIGHT 0b00011100

#define CMD_SHIFT_DISP_LEFT  0b00011000

#define CMD_CGRAM_ADDRESS    0b01000000

/*send a command to the LCD*/
static void LCD_vSendCmd(u8 A_u8Cmd);

/*send data to the LCD*/
static void LCD_vSendData(u8 A_u8Cmd);

/*Returns pointer to chars*/
static u8* u8IntToString(s64 A_s64Num);

static void floatToString(f32 A_f32Num, u8 *A_u8Arr, u8 A_u8AfterDecimal);


/*Available patterns*/
static u8 G_u8Pattern0[] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04};/*Space ship*/
static u8 G_u8Pattern1[] = {0x00, 0x00, 0xA, 0x15, 0x11, 0xA, 0x04};/*heart*/
static u8 G_u8Pattern2[] = {0x0E,0x0E,0x04,0x04,0x1F,0x04,0x0A,0x0A};/*a man*/
static u8 G_u8Pattern3[] = {  0x04,
							  0x0E,
							  0x15,
							  0x04,
							  0x04,
							  0x04,
							  0x04,
							  0x00 }; /*Arrow*/

static void LCD_vCreateCustomPattern(u8 *A_u8Patten, u8 A_u8Loc);

#endif /* HAL_LCD_LCD_PRI_H_ */
