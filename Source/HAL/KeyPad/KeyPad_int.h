/*
 * KeyPad_int.h
 *
 *  Created on: 24 Aug 2022
 *      Author: 20109
 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_

#define NO_PRESSED_KEY 255

void KeyPad_vInit();
u8 KeyPad_u8GetPressedKey();

#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
