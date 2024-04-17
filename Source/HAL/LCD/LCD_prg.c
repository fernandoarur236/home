/*
 * LCD_prg.c
 *
 *  Created on: 22 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LCD_pri.h"
#include "LCD_cfg.h"
#include "LCD_int.h"
#include <avr/delay.h>
#include <math.h>

static void LCD_vSendCmd(u8 A_u8Cmd){
	DIO_vSetPinVal(LCD_RS_PORT, LCD_RS_PIN, VAL_LOW);/*Choosing the instruction register*/
	DIO_vSetPinVal(LCD_RW_PORT, LCD_RW_PIN, VAL_LOW);/*Writing to the LCD*/
	DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/

	#if(LCD_MODE == EIGHT_BIT_MODE)
		DIO_vSetPortVal(LCD_DATA_PORT, A_u8Cmd); /*write the command*/
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/
	#else /*Four bit mode*/
		/*In 4Bit mode we send the higher nibble first then the lower nibble*/

		/*Sending the higher nibble*/
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Cmd, PIN4_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Cmd, PIN5_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Cmd, PIN6_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Cmd, PIN7_ID));
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/


		/*Sending the lower nibble*/
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Cmd, PIN0_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Cmd, PIN1_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Cmd, PIN2_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Cmd, PIN3_ID));
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/

	#endif

}

static void LCD_vSendData(u8 A_u8Data){
	DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
	DIO_vSetPinVal(LCD_RS_PORT, LCD_RS_PIN, VAL_HIGH);/*Choosing the data register*/
	DIO_vSetPinVal(LCD_RW_PORT, LCD_RW_PIN, VAL_LOW);/*Writing to the LCD*/
	#if(LCD_MODE == EIGHT_BIT_MODE)
		DIO_vSetPortVal(LCD_DATA_PORT, A_u8Data); /*write the data*/
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/
		_delay_us(5);
	#else
		/*In 4Bit mode we send the higher nibble first then the lower nibble*/

		/*Sending the higher nibble*/
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Data, PIN4_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Data, PIN5_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Data, PIN6_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Data, PIN7_ID));
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/


		/*Sending the lower nibble*/
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Data, PIN0_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Data, PIN1_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Data, PIN2_ID));
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Data, PIN3_ID));
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/

		_delay_us(10);
	#endif
}

void LCD_vInit(){
	_delay_ms(30); /*Specified in the data sheet to make a small delay before init*/

	#if(LCD_MODE == EIGHT_BIT_MODE)
		/*Initialize the ports*/
		DIO_vSetPortDir(LCD_DATA_PORT, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_EN_PORT, LCD_EN_PIN, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_RW_PORT, LCD_RW_PIN, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_RS_PORT, LCD_RS_PIN, DIR_OUTPUT);

		LCD_vSendCmd(CMD_EIGHT_BIT_MODE);/*Command to set 8bit mode, 2x16 lines, 5x7dots*/
		_delay_us(39);
		LCD_vSendCmd(CMD_DISPLAY_ON);/*Command to set the display ON*/
		_delay_us(39);
		LCD_vSendCmd(CMD_CLEAR_DISP);/*Command to clear display*/
		_delay_ms(1.53);
		LCD_vSendCmd(CMD_ENTRY_MODE_INC);/*Command to increament cursor*/

	#else /*4Bit mode*/
		DIO_vSetPinDir(LCD_EN_PORT, LCD_EN_PIN, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_RW_PORT, LCD_RW_PIN, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_RS_PORT, LCD_RS_PIN, DIR_OUTPUT);

		DIO_vSetPinDir(LCD_DATA_PORT, LCD_D4_ID, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_DATA_PORT, LCD_D5_ID, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_DATA_PORT, LCD_D6_ID, DIR_OUTPUT);
		DIO_vSetPinDir(LCD_DATA_PORT, LCD_D7_ID, DIR_OUTPUT);


		DIO_vSetPinVal(LCD_RS_PORT, LCD_RS_PIN, VAL_LOW);/*Choosing the instruction register*/
		DIO_vSetPinVal(LCD_RW_PORT, LCD_RW_PIN, VAL_LOW);/*Writing to the LCD*/
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D4_ID, VAL_LOW);
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D5_ID, VAL_HIGH);
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D6_ID, VAL_LOW);
		DIO_vSetPinVal(LCD_DATA_PORT, LCD_D7_ID, VAL_LOW);
		DIO_vSetPinVal(LCD_EN_PORT, LCD_EN_PIN, VAL_LOW);/*set the En high to make LCD read*/

		LCD_vSendCmd(CMD_FOUR_BIT_MODE);/*Command to set 4bit mode, 2x16 lines, 5x7dots*/
		_delay_us(39);
		LCD_vSendCmd(CMD_DISPLAY_ON);/*Command to set the display ON*/
		_delay_us(39);
		LCD_vSendCmd(CMD_CLEAR_DISP);/*Command to clear display*/
		_delay_ms(1.53);
		LCD_vSendCmd(CMD_ENTRY_MODE_INC);/*Command to increament cursor*/
	#endif
}

void LCD_vDispChar(u8 A_u8Char){
	LCD_vSendData(A_u8Char);
}

void LCD_vDispStr(u8 *A_u8Str){
	for(u8 i=0; A_u8Str[i] != '\0'; i++){
		LCD_vDispChar(A_u8Str[i]);
	}
}

void LCD_vClrDisp(){
	LCD_vSendCmd(CMD_CLEAR_DISP);
	_delay_ms(1.53);
}

void LCD_vSetPosition (u8 A_u8Row, u8 A_u8Col){
	u8 L_u8FirstRow = 0x00, L_u8SecondRow = 0x40;
	switch(A_u8Row){
		case ROW0_ID: LCD_vSendCmd(CMD_SET_CURSOR_POSITION + L_u8FirstRow + A_u8Col); break;
		case ROW1_ID: LCD_vSendCmd(CMD_SET_CURSOR_POSITION + L_u8SecondRow + A_u8Col); break;
	}
}

static u8* u8IntToString(s64 A_s64Num){
	u8 L_u8TempChars[10] = {};
	static u8 L_u8Chars[10] = {};

	u8 i;
	if(A_s64Num < 0){
		L_u8TempChars[0] = '-'; /*Apply "-"sign */
		A_s64Num *= -1; /*Making it positive number*/
		i = 1;
	} else {
		i=0;
	}

	for(; i<9; i++){
		L_u8TempChars[i] = (A_s64Num % 10) + 0x30;/*Get the number and convert to ASCII*/
		A_s64Num = A_s64Num/10;
		if(A_s64Num == 0)
		{
			L_u8TempChars[i+1] = '\0';/*Put the NILL to the end of the string*/
			break;
		}
	}

	s8 k;
	if(L_u8TempChars[0] == '-'){/*if we have a -ve number we want the sign to be the first*/
		L_u8Chars[0] = '-';
		k = 1;
	} else{
		k = 0;
	}

	u8 L_u8Counter = 0;
	for(; k<=i; k++){ /*Copy the array in the correct order*/
		L_u8Chars[k] = L_u8TempChars[i-L_u8Counter];
		L_u8Counter++;
		if(k==i){
			L_u8Chars[k+1] = '\0';
		}
	}
	return L_u8Chars;
}


/*You can use itoa/ltoa*/
void LCD_vDispNum(s64 A_s64Num){
	u8 *L_u8Str = u8IntToString(A_s64Num);

	for(u8 i=0; L_u8Str[i] != '\0'; i++){
		LCD_vDispChar(L_u8Str[i]);
	}

}

void LCD_vShiftDisp(u8 A_u8ShiftDir){
	switch(A_u8ShiftDir){
		case SHIFT_LEFT:  LCD_vSendCmd(CMD_SHIFT_DISP_LEFT); break;
		case SHIFT_RIGHT: LCD_vSendCmd(CMD_SHIFT_DISP_RIGHT); break;
	}
}

/*Need some work*/
static void floatToString(f32 A_f32Num, u8 *A_u8Arr, u8 A_u8AfterDecimal){
	u32 L_u32IntPart = (u32) A_f32Num;
	f32 L_f32FloatPart = A_f32Num - (f32)L_u32IntPart;

	u8 *L_u8Str = u8IntToString(L_u32IntPart);
	u8 L_u8StrLength = 0;

	while(L_u8Str[L_u8StrLength] != '\0'){ L_u8StrLength++; }

	for(u8 i=0; i<L_u8StrLength; i++){
		A_u8Arr[i] = L_u8Str[i];
	}

	A_u8Arr[L_u8StrLength] = '.';

	for(u8 i=0; i<A_u8AfterDecimal; i++) { A_u8AfterDecimal *= 10;}

	L_f32FloatPart = L_f32FloatPart * (f32) A_u8AfterDecimal;

	L_u8Str = u8IntToString((u32)L_f32FloatPart);

	for(u8 i=0; i<A_u8AfterDecimal+1; i++){
		A_u8Arr[L_u8StrLength + 1 + i] = L_u8Str[i];
	}
}

void LCD_vDispFloat(f32 A_f32Num){
	u8 L_u8Chars [10] = {};
	floatToString(A_f32Num, L_u8Chars, 3);

	LCD_vDispStr(L_u8Chars);
}

void LCD_vReturnHome(){
	LCD_vSendCmd(CMD_RETURN_HOME);
}


void LCD_vShiftCursor(u8 A_u8ShiftDir){

}

/* Creating a custom patterns
 * we multiply by 8 as we have 8 locations (5x8 dots, 8 rows) for each cell (only can create 8 patterns)
 * */
static void LCD_vCreateCustomPattern(u8 *A_u8Pattern, u8 A_u8Loc){
	LCD_vSendCmd(CMD_CGRAM_ADDRESS + A_u8Loc*8);
	_delay_us(45);
	for(u8 i=0; i<8; i++){
		LCD_vSendData(A_u8Pattern[i]);
	}
}

void LCD_vDispCustomChar(u8 A_u8PatternId, u8 A_u8Row, u8 A_u8Col){
	switch(A_u8PatternId){
		case PATTERN0_ID: LCD_vCreateCustomPattern(G_u8Pattern0, 0); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN1_ID: LCD_vCreateCustomPattern(G_u8Pattern1, 1); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(1); break;
		case PATTERN2_ID: LCD_vCreateCustomPattern(G_u8Pattern2, 2); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(2); break;
		case PATTERN3_ID: LCD_vCreateCustomPattern(G_u8Pattern3, 3); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(3); break;
		/*
		case PATTERN4_ID: LCD_vCreateCustomPattern(G_u8Pattern4, 4); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN5_ID: LCD_vCreateCustomPattern(G_u8Pattern5, 5); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN6_ID: LCD_vCreateCustomPattern(G_u8Pattern6, 6); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN7_ID: LCD_vCreateCustomPattern(G_u8Pattern7, 7); LCD_vSetPosition(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		*/
	}
}

void LCD_vTurnOn(){

}
void LCD_vTurnOff(){

}


