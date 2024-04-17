/*********************************************************/
/***********		Author: Smart Home	 	**************/
/***********		Layer: APP			 	**************/
/***********		Component: APPSYS  		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 28 Dec 2022	 	**************/
/***********		Updated: 28 Sep 2022	**************/
/*********************************************************/



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/MCU/MCU.h"
#include "../../LIB/STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define		_HOME_LOCKED			100
#define		_HOME_UNLOCKED			101
#define		_HOME_KEYPAD_STATE		102

#define		_HOME_LOCKDOWN_STATE	111

#define		LDR_INDEX					1	 /*For Channels Array*/
#define		TEMP_INDEX					0	 /*For Channels Array*/

#define		DOOR_STATUS_INDEX			0	 /*For HomeStatus Array*/
#define		HOME_STATUS_INDEX			1	 /*For HomeStatus Array*/
#define		ELEC_STATUS_INDEX			2	 /*For HomeStatus Array*/
#define		FAN_STATUS_INDEX			3	 /*For HomeStatus Array*/
#define		AUTO_LIGHT_STATUS_INDEX		4	 /*For HomeStatus Array*/
#define		AUTO_FAN_STATUS_INDEX		5	 /*For HomeStatus Array*/
#define 	LIGHT_STATUS_INDEX			6	 /*For HomeStatus Array*/


/* Received Frame From Web-Application */
#define		COMMAND_ACTION				0	/* ON/OFF */
#define		COMMAND_OBJECT				1	/* Object or Device to control */
#define		COMMAND_MODE				2	/* Auto-mode ON/OFF (if the device has automatic mode) */

/* Automatic/Manual Modes */
#define		AUTOMATIC					50
#define		MANUAL						51

/* Device ON/OFF */
#define		ON					    0x72
#define		OFF						0x73

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void DisplayOverLCD(void)        
* \Description     : The API responsible for displaying data over LCD
                     periodically
*******************************************************************************/
void DisplayOverLCD();

/******************************************************************************
* \Syntax          : void Animation1_LcdPassword(void)
* \Description     : The API responsible for displaying LCD Password
*******************************************************************************/
void Animation1_LcdPassword();


/******************************************************************************
* \Syntax          : void startKeypad(void)        
* \Description     : The API responsible for getting from keypad when triggered
*******************************************************************************/
void StartKeypad();


/******************************************************************************
* \Syntax          : void System_SendFrame(void)
* \Description     : Sending the frame containing (Temp, LDR, LEDs) values, home
					 status, door status, electrical device status and fan status
*******************************************************************************/
void System_SendFrame();

/******************************************************************************
* \Syntax          : void toHex(void)
* \Description     : The API responsible for sending the hex character of a value
*******************************************************************************/
static void toHex(u8 A_u8Data);

/******************************************************************************
* \Syntax          : void System_UartHandler(void)
* \Description     :
*******************************************************************************/
void System_UartHandler(u16 A_u8Data);


/******************************************************************************
* \Syntax          : void System_CommandsHandler(void)
* \Description     : API responsible for handling the received commands from
					 the web-application and changing status.
*******************************************************************************/
void System_CommandsHandler( void );

/******************************************************************************
* \Syntax          : void Timer0Elapsed_KeyOFF(void)        
* \Description     : The API responsible for turning OFF keypad & LCD
*******************************************************************************/
void Timer0Elapsed_KeyOFF();


/******************************************************************************
* \Syntax          : void System_Start(void)
* \Description     : Initializing and preparing the system for the first time
*******************************************************************************/
void System_Start();


/******************************************************************************
* \Syntax          : void System_WakeUp(void)        
* \Description     : Waking the system-up and doing its functions
*******************************************************************************/
void System_WakeUp();


/******************************************************************************
* \Syntax          : void LedIntensity_AutoControl(void)        
* \Description     : Automatic control of the LEDs based on the intensity value
*******************************************************************************/
void LedIntensity_AutoControl();


/******************************************************************************
* \Syntax          : void FanSpeed_AutoControl(void)
* \Description     : Automatic control of the Fan based on the temprature
*******************************************************************************/
void FanSpeed_AutoControl();
