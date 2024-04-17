/*
 * KeyPad_cfg.h
 *
 *  Created on: 24 Aug 2022
 *      Author: 20109
 */

#ifndef HAL_KEYPAD_KEYPAD_CFG_H_
#define HAL_KEYPAD_KEYPAD_CFG_H_

#define KEYPAD_PORT PORTB_ID

#define ROW_START PIN3_ID
#define ROW_END   PIN6_ID

#define COL_START PIN0_ID
#define COL_END   PIN2_ID


/*
 * you have ROWS_NUMBER , COLS_NUMBER
 * Not used
 * */
#define AVAILABLE_ROWS ROWS_NUMBER
#define AVAILABLE_COLS COLS_NUMBER

#endif /* HAL_KEYPAD_KEYPAD_CFG_H_ */
