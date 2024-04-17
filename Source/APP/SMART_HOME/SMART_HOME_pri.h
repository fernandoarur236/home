/*
 * SMART_HOME_pri.h
 *
 *  Created on: 12 Jan 2023
 *      Author: 20109
 */

#ifndef APP_SMART_HOME_SMART_HOME_PRI_H_
#define APP_SMART_HOME_SMART_HOME_PRI_H_

		/****************************************************************************
		 * 						SMART HOME CONSTANT MACROS							*
		 ***************************************************************************/
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



		/****************************************************************************
		 * 							SMART HOME VARIABLES							*
		 ***************************************************************************/

/* Home Password */
static u8 password[4] = "1234";
static u8 trials = 4;


/* Entry Password */
static u8 tempPassword[4] = {0};
static u8 password_i = 0;


static u16 channelsValues[2] = {0};

static u8 G_u8HomeState = _HOME_LOCKED;

static u8 G_u8HomeSatus [7];		/*Contains Door, Home, ELEC, Fan status*/
static u8 G_u8Buffer[8];			/*Buffer for Receiving Data from GUI */
static u8 G_u8IsBufferRdy = 0;		/*Flag for reading buffer when ready*/

/* Device Automatic Mode Variable */
static u8 G_u8FanMode		= MANUAL;
static u8 G_u8LightsMode	= MANUAL;



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void DisplayOverLCD(void)
* \Description     : The API responsible for displaying data over LCD
                     periodically
*******************************************************************************/
static void DisplayOverLCD();

/******************************************************************************
* \Syntax          : void Animation1_LcdPassword(void)
* \Description     : The API responsible for displaying LCD Password
*******************************************************************************/
static void Animation1_LcdPassword();


/******************************************************************************
* \Syntax          : void startKeypad(void)
* \Description     : The API responsible for getting from keypad when triggered
*******************************************************************************/
static void StartKeypad();


/******************************************************************************
* \Syntax          : void System_SendFrame(void)
* \Description     : Sending the frame containing (Temp, LDR, LEDs) values, home
					 status, door status, electrical device status and fan status
*******************************************************************************/
static void System_SendFrame();

/******************************************************************************
* \Syntax          : void toHex(void)
* \Description     : The API responsible for sending the hex character of a value
*******************************************************************************/
static void toHex(u8 A_u8Data);

/******************************************************************************
* \Syntax          : void System_UartHandler(void)
* \Description     :
*******************************************************************************/
static void System_UartHandler(u16 A_u8Data);


/******************************************************************************
* \Syntax          : void System_CommandsHandler(void)
* \Description     : API responsible for handling the received commands from
					 the web-application and changing status.
*******************************************************************************/
static void System_CommandsHandler( void );

/******************************************************************************
* \Syntax          : void Timer0Elapsed_KeyOFF(void)
* \Description     : The API responsible for turning OFF keypad & LCD
*******************************************************************************/
static void Timer0Elapsed_KeyOFF();

/******************************************************************************
* \Syntax          : void LedIntensity_AutoControl(void)
* \Description     : Automatic control of the LEDs based on the intensity value
*******************************************************************************/
static void LedIntensity_AutoControl();

/******************************************************************************
* \Syntax          : void FanSpeed_AutoControl(void)
* \Description     : Automatic control of the Fan based on the temprature
*******************************************************************************/
static void FanSpeed_AutoControl();

static void HomeUnlocked();
static void HomeLockDown();
static void KeyPadState ();

#endif /* APP_SMART_HOME_SMART_HOME_PRI_H_ */
