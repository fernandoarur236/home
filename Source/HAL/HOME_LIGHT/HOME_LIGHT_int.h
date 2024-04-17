/*
 * HOME_LIGHT_int.h
 *
 *  Created on: 12 Jan 2023
 *      Author: 20109
 */

#ifndef HAL_HOME_LIGHT_HOME_LIGHT_INT_H_
#define HAL_HOME_LIGHT_HOME_LIGHT_INT_H_


#define HOME_LIGHTS_LVL1	0
#define HOME_LIGHTS_LVL2	1
#define HOME_LIGHTS_LVL3	2
#define HOME_LIGHTS_LVL4	3


/**********************************************************************************************************
 * Description : Interface Function to initialize the Home lights
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void HOME_LIGHT_vInit();
/**********************************************************************************************************
 * Description : Interface Function to set the status of the lights
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Use the interface MACROS
 ***********************************************************************************************************/
void HOME_LIGHT_vSetStatus(u8 A_u8Status);

#endif /* HAL_HOME_LIGHT_HOME_LIGHT_INT_H_ */
