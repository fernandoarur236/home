/*
 * DCmotor_int.h
 *
 *  Created on: 25 Aug 2022
 *      Author: 20109
 */

#ifndef HAL_DCM_DCM_INT_H_
#define HAL_DCM_DCM_INT_H_
/*Must be connected to H-bridge*/


#define DCM_ANTI_CLK_WISE 1
#define DCM_CLK_WISE      0

void DCM_vInit();
void DCM_vTurnOn();
void DCM_vTurnOff();
void DCM_vSetDirection(u8 A_u8Dir);
void DCM_vSetPWM(s8 A_u8PWM);

#endif /* HAL_DCM_DCM_INT_H_ */
