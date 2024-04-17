/*
 * KeyPad_prg.c
 *
 *  Created on: 24 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "KeyPad_pri.h"
#include "KeyPad_cfg.h"
#include "KeyPad_int.h"

#define F_CPU 8000000UL
#include <avr/delay.h>

void KeyPad_vInit(){
	for(u8 col = COL_START; col <= COL_END; col++){
		DIO_vSetPinDir(KEYPAD_PORT, col, DIR_OUTPUT);
		DIO_vSetPinVal(KEYPAD_PORT, col, VAL_LOW); /*Initally the KEYPAD is off*/
	}
	for(u8 row = ROW_START; row <= ROW_END; row++){
		DIO_vSetPinDir(KEYPAD_PORT, row, DIR_INPUT);
		DIO_vSetPinVal(KEYPAD_PORT, row, VAL_HIGH);/*PULL-UP*/
	}
}
u8 KeyPad_u8GetPressedKey(){
	u8 L_u8PressedVal = NO_PRESSED_KEY, L_u8Flag = 0;
	/*Loop on every columns*/
	for(u8 col = COL_START; col <= COL_END; col++){
		/*Set the value low (to read)*/
		DIO_vSetPinVal(KEYPAD_PORT, col , VAL_LOW);
		/*Loop on every row*/
		for(u8 row = ROW_START; row <= ROW_END; row++){
			/*Check if the value is low (pressed key)*/
			if(DIO_u8GetPinVal(KEYPAD_PORT, row) == 0){
				/*Wait till the user remove his hands*/
				while(DIO_u8GetPinVal(KEYPAD_PORT, row) == 0);
				/*Get the corresponding value*/
				L_u8PressedVal = L_KeyPadMatrix[row - ROW_START][col - COL_START];
				/*Flag is set to represent a key is pressed*/
				L_u8Flag = 1;
				/*Delay for bouncing of the key*/
				_delay_ms(20);
				break;
			}
		}
		/*set the value high again (to prevent unwanting)*/
		DIO_vSetPinVal(KEYPAD_PORT, col, VAL_HIGH);
		if(L_u8Flag == 1) break;
	}

	return L_u8PressedVal;
}
