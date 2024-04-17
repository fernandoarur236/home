/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: LCD	 		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 22 Aug 2022	 	**************/
/*********************************************************/

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_
/*in the IMTschool AVR kit we have one 2x16 LCD*/
/*Implement 4bit mode, float number, */


/*the Rows and Cols we have*/
typedef enum {
	ROW0_ID,
	ROW1_ID
};
typedef enum {
	COL0_ID,
	COL1_ID,
	COL2_ID,
	COL3_ID,
	COL4_ID,
	COL5_ID,
	COL6_ID,
	COL7_ID,
	COL8_ID,
	COL9_ID,
	COL10_ID,
	COL11_ID,
	COL12_ID,
	COL13_ID,
	COL14_ID,
	COL15_ID
};

typedef enum {
	SHIFT_LEFT,
	SHIFT_RIGHT
};

typedef enum {
	PATTERN0_ID,
	PATTERN1_ID,
	PATTERN2_ID,
	PATTERN3_ID,
	PATTERN4_ID,
	PATTERN5_ID,
	PATTERN6_ID,
	PATTERN7_ID
};

#define NUMBER_OF_COLS 16
#define NUMBER_OF_ROWS 2

void LCD_vInit();

void LCD_vDispChar(u8 A_u8Char);
void LCD_vDispStr(u8 *A_u8Str);
void LCD_vDispNum(s64 A_s64Num);
void LCD_vClrDisp();
void LCD_vDispFloat(f32 A_f32Num);

void LCD_vReturnHome();

void LCD_vShiftDisp(u8 A_u8ShiftDir);
void LCD_vShiftCursor(u8 A_u8ShiftDir);

void LCD_vSetPosition (u8 row, u8 col);

void LCD_vTurnOn();
void LCD_vTurnOff();

void LCD_vDispCustomChar(u8 A_u8PatternId, u8 A_u8Row, u8 A_u8Col);

#endif /* HAL_LCD_LCD_INT_H_ */
