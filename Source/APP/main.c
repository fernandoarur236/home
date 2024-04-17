/*
 * Smart Home.c
 *
 * Created: 26/12/2022 05:58:27 PM
 * Author : 20109
 */ 


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MCU/MCU.h"
#include "../HAL/DCM/DCM_int.h"
#include "../MCAL/EEPROM/EEPROM_int.h"
#include "SMART_HOME/SMART_HOME_int.h"
#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{

	SMART_HOME_vInit();
	Mcu_Init();

    while (1)
    {
    	SMART_HOME_vUpdate();
	}

//	DCM_vInit();
//	DCM_vTurnOn();
//	DCM_vSetPWM(80);
//
	//DCM_vTurnOff();
	//while(1);
	/*
	u8 pass[] = "101010";
	u8 i=0;
	while(1) {
		EEPROM_vWrite(i, pass[i]);
		i++;
		if( i == ( sizeof(pass) / sizeof(pass[0]) ) - 1 ){
			EEPROM_vWrite(i, 'q');
			break;
		}
	}
	*/
}




