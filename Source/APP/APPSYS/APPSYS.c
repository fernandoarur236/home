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

#include "APPSYS.h"
#include "../../HAL/LCD/LCD_int.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/TIM0/TIM0_int.h"
#include "../../MCAL/EEPROM/EEPROM_int.h"
#include "../../HAL/LDR/LDR_int.h"
#include "../../HAL/TEMPS/TEMPS_int.h"
#include "../../HAL/KeyPad/KeyPad_int.h"
#include "../../HAL/DCM/DCM_int.h"
#include "../../HAL/SERVO/SERVO_int.h"
#include "../../HAL/HC/HC_int.h"
#include <string.h>
#include <avr/delay.h>

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* Home Password */
u8 password[8] = "1234";
u8 trials = 4;


/* Entry Password */
u8 tempPassword[8] = {0};
u8 password_i = 0;


u16 channelsValues[2] = {0};
u8 channels[2] = {TEMPS_PIN, LDR_CHANNEL};

u8 Home_State = _HOME_LOCKED;


u8 G_u8HomeSatus [7];		/*Contains Door, Home, ELEC, Fan status*/
u8 G_u8Buffer[5];			/*Buffer for Receiving Data from GUI */
u8 G_u8IsBufferRdy = 0;		/*Flag for reading buffer when ready*/

/* ADC Chain */
ADC_stChain chain = { channels, channelsValues, 2, &System_SendFrame };

/* Device Automatic Mode Variable */
u8 G_u8FanMode		= MANUAL;
u8 G_u8LightsMode	= MANUAL;


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void DisplayOverLCD(void)        
* \Description     : The API responsible for displaying data over LCD
                     periodically
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None                         
*******************************************************************************/
void DisplayOverLCD()
{
	channelsValues[0] = TEMPS_ConvertValue(channelsValues[0]);	/* Getting Temp Value */
	channelsValues[1] = LDR_ConvertValue(channelsValues[1]);	/* Getting LDR Value */
	LCD_vSetPosition(ROW0_ID, COL0_ID);
	LCD_vDispNum(channelsValues[0]);
	LCD_vSetPosition(ROW1_ID, COL0_ID);
	LCD_vDispNum(channelsValues[1]);
	LCD_vSetPosition(ROW1_ID, COL6_ID);
}

/******************************************************************************
* \Syntax          : void Animation1_LcdPassword(void)
* \Description     : The API responsible for displaying LCD Password
*******************************************************************************/
void Animation1_LcdPassword()
{
	/*		LCD-Password Phase		 */
	_delay_ms(250);
	LCD_vClrDisp();
	_delay_ms(2);
	
	LCD_vDispStr("Enter Password:");
	LCD_vSetPosition(ROW1_ID, COL0_ID);
}


/******************************************************************************
* \Syntax          : void startKeypad(void)        
* \Description     : The API responsible for getting from keypad when triggered
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None  
*******************************************************************************/
void StartKeypad(){
	MCU_WAKEUP();
	if (Home_State == _HOME_LOCKDOWN_STATE);		/* Do Nothing */
	else
	{
		DIO_vSetPinVal(PORTB_ID, PIN7_ID, VAL_HIGH);
		Home_State = _HOME_KEYPAD_STATE;
		
		/*		LCD Welcome Message		 */
		LCD_vSetPosition(ROW0_ID, COL0_ID);
		LCD_vDispStr("Welcome ");
		_delay_ms(50);
		for(u8 i=0 ; i<3; i++)	/* Dots Animation */
		{
			LCD_vDispChar('.');
			_delay_ms(100);
		}
		
		/*		LCD-Password Phase		 */
		Animation1_LcdPassword();
		
		/* Start Inactivity Countdown Timer */
		TIM0_vTurnOn();
		TIM0_vDelayMilli(8000, 0, &Timer0Elapsed_KeyOFF);
	}
}


/******************************************************************************
* \Syntax          : void System_UartHandler(void)
* \Description     :
* \Parameters (in) : Character received
* \Parameters (out): The Global Buffer (G_u8Buffer), G_u8IsBufferRdy = true; 
* \Return value:   : None
*******************************************************************************/
void System_UartHandler(u16 A_u8Data)
{
	static u8 L_u8Counter = 0;
	static u8 L_u8Flag = 0;
	if(A_u8Data == ';'){					/* End Frame */
		L_u8Flag = 0;
		L_u8Counter = 0;
		G_u8IsBufferRdy = 1;
		
		/* Handle the received command */
		System_CommandsHandler();
		/*****	 TODO: Remove these 2 lines		*****/
		System_SendFrame();
		DIO_vTogPin(PORTB_ID, PIN7_ID);
	}
	if(L_u8Flag == 1 && A_u8Data != ' '){   /* Save Frame */
		G_u8Buffer[L_u8Counter++] = A_u8Data;
	}
	if(A_u8Data == '#'){					/* Start frame */
		L_u8Flag = 1;
		G_u8IsBufferRdy = 0;
	}
}


/******************************************************************************
* \Syntax          : void System_CommandsHandler(void)
* \Description     : API responsible for handling the received commands from
					 the web-application and changing status.
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void System_CommandsHandler( void )
{
	u8 L_u8PasswordBuffIndex = 1;
	/*****	 TODO: Implementation		*****/
	switch(G_u8Buffer[COMMAND_OBJECT])
	{
		case 'g':	/* Door */ 
			G_u8Buffer[COMMAND_ACTION] == ON ? SERVO_vSetState(STATE_180) : SERVO_vSetState(STATE_0) ;
			G_u8HomeSatus[DOOR_STATUS_INDEX] = G_u8Buffer[COMMAND_ACTION];		/* Setting the new status */
		break;
		
		case 'c':	/* Device */
			G_u8Buffer[COMMAND_ACTION] == ON ? DIO_vSetPinVal(PORTD_ID, PIN7_ID, VAL_HIGH) : DIO_vSetPinVal(PORTD_ID, PIN7_ID, VAL_LOW);
			G_u8HomeSatus[ELEC_STATUS_INDEX] = G_u8Buffer[COMMAND_ACTION];		/* Setting the new status */
		break;
		
		case 'l':	/* Light */
			if (G_u8Buffer[COMMAND_MODE] == 'e')	/* Automatic */
			{
				G_u8LightsMode = AUTOMATIC;
				LedIntensity_AutoControl();
				G_u8HomeSatus[AUTO_LIGHT_STATUS_INDEX] = 'r';		/* Setting the new mode status */
			}
			else{		/* Not Automatic */
				G_u8LightsMode = MANUAL;
				G_u8Buffer[COMMAND_ACTION] == ON ? DIO_vPortVal_Maked(PORTC_ID, 0x0E, SET_OPERATION) 
													: DIO_vPortVal_Maked(PORTC_ID, 0xF1, CLEAR_OPERATION);
				G_u8HomeSatus[AUTO_LIGHT_STATUS_INDEX] = 's';		/* Setting the new mode status */
			}
		G_u8HomeSatus[LIGHT_STATUS_INDEX] = G_u8Buffer[COMMAND_ACTION];			/* Setting the new status */
		break;
		
		case 'f':	/* Fan */
		if (G_u8Buffer[COMMAND_MODE] == 'e')	/* Automatic */
		{
			G_u8FanMode = AUTOMATIC;
			/* TODO: Automate fan API */
			FanSpeed_AutoControl();
			G_u8HomeSatus[AUTO_FAN_STATUS_INDEX] = 'r';		/* Setting the new mode status */
		}
		else{		/* Not Automatic */
			G_u8FanMode = MANUAL;
			/* TODO: TURN FAN ON/OFF */
			G_u8Buffer[COMMAND_ACTION] == ON ? DCM_vTurnOn() : DCM_vTurnOff();
			G_u8HomeSatus[AUTO_FAN_STATUS_INDEX] = 's';		/* Setting the new mode status */
			G_u8HomeSatus[FAN_STATUS_INDEX] = G_u8Buffer[COMMAND_ACTION];			/* Setting the new status */
		}
	}
	if(G_u8Buffer[COMMAND_ACTION] == 'p'){	/*Password*/
		while(G_u8Buffer[L_u8PasswordBuffIndex] != 'q'){	/* q is the terminating char for pass */
			password[L_u8PasswordBuffIndex - 1] = G_u8Buffer[L_u8PasswordBuffIndex];
			L_u8PasswordBuffIndex++;
		}
		for(u8 i=0; i< L_u8PasswordBuffIndex-1; i++){		/* save password in EEPROM */
			EEPROM_vWrite(i, password[i]);
		}
		EEPROM_vWrite(L_u8PasswordBuffIndex-1, 'q');		/* Terminating character*/
	}
}


/******************************************************************************
* \Syntax          : void System_SendFrame(void)
* \Description     : Sending the frame containing (Temp, LDR, LED) values, home
					 status, door status, electrical device status and fan status
* \NOTES		   : Put values in G_u8HomeStatus array before calling
*******************************************************************************/
void System_SendFrame() {
	/* Making the proper conversions */
	channelsValues[0] = TEMPS_ConvertValue(channelsValues[0]);	/* Getting Temp Value */
	channelsValues[1] = LDR_ConvertValue(channelsValues[1]);	/* Getting LDR Value */
	
	HC_vSendData('S');									/*Frame Start*/
	HC_vSendData('+');									/*Frame Start*/
	HC_vSendData('-');									/*Frame Start*/
	toHex(G_u8HomeSatus[HOME_STATUS_INDEX]);			/*Home Status*/
	HC_vSendData(',');
	toHex(channelsValues[TEMP_INDEX]);						/*Temperature value*/					
	HC_vSendData(',');
	toHex(G_u8HomeSatus[FAN_STATUS_INDEX]);			/*Fan status*/
	HC_vSendData(',');
	toHex(G_u8HomeSatus[AUTO_FAN_STATUS_INDEX]);		/*AutoFan status*/
	HC_vSendData(',');
	toHex( (channelsValues[LDR_INDEX] & 0xFF00) >>0 );		/*Light intensity high two bytes*/
	toHex( (channelsValues[LDR_INDEX] & 0x00FF) );			/*Light intensity Low two bytes*/
	HC_vSendData(',');
	toHex(G_u8HomeSatus[LIGHT_STATUS_INDEX]);
	HC_vSendData(',');
	toHex(G_u8HomeSatus[AUTO_LIGHT_STATUS_INDEX]);			/*AutoLight Status*/
	HC_vSendData(',');
	toHex(G_u8HomeSatus[DOOR_STATUS_INDEX]);				/*Door Status*/
	HC_vSendData(',');
	toHex(G_u8HomeSatus[ELEC_STATUS_INDEX]);				/*Electric Device Status*/
	HC_vSendString("+-");
}


/******************************************************************************
* \Syntax          : void toHex(void)
* \Description     : The API responsible for sending the hex character of a value
*******************************************************************************/
static void toHex(u8 A_u8Data){
	u8 L_u08FirstChar = A_u8Data & 0x0F;
	u8 L_u08SecondChar = (A_u8Data & 0xF0) >> 4;
	switch(L_u08FirstChar){			/* Parsing the higher ASCII values for first char */
		case 10: L_u08FirstChar = 'A'; break;
		case 11: L_u08FirstChar = 'B'; break;
		case 12: L_u08FirstChar = 'C'; break;
		case 13: L_u08FirstChar = 'D'; break;
		case 14: L_u08FirstChar = 'E'; break;
		case 15: L_u08FirstChar = 'F'; break;
		default: L_u08FirstChar += '0'; break;
	}
	switch(L_u08SecondChar){		/* Parsing the higher ASCII values for second char */
		case 10: L_u08SecondChar = 'A'; break;
		case 11: L_u08SecondChar = 'B'; break;
		case 12: L_u08SecondChar = 'C'; break;
		case 13: L_u08SecondChar = 'D'; break;
		case 14: L_u08SecondChar = 'E'; break;
		case 15: L_u08SecondChar = 'F'; break;
		default: L_u08SecondChar += '0'; break;
	}
	HC_vSendData(L_u08SecondChar);
	HC_vSendData(L_u08FirstChar);
}

/******************************************************************************
* \Syntax          : void Timer0Elapsed_KeyOFF(void)        
* \Description     : The API responsible for turning OFF keypad & LCD
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None  
*******************************************************************************/
void Timer0Elapsed_KeyOFF()
{
	if (Home_State == _HOME_LOCKDOWN_STATE);		/* Do Nothing */
	else
	{
		DIO_vSetPinVal(PORTB_ID, PIN7_ID, VAL_LOW);		/* Turn LED OFF */
		Home_State = _HOME_LOCKED;	/* To be Handled */
		TIM0_vTurnOff();
		
		/*		Clearing LCD		*/
		LCD_vClrDisp();
		_delay_ms(2);
		LCD_vDispStr("B Y E ...");
		_delay_ms(250);
		LCD_vClrDisp();
		_delay_ms(2);
		for(u8 i=0 ; i<3; i++)	/* Animation */
		{
			LCD_vSetPosition(ROW0_ID, COL5_ID);
			LCD_vDispStr(" ! ! !");
			_delay_ms(100);
			LCD_vClrDisp();
			_delay_ms(100);
		}
	}
}


/******************************************************************************
* \Syntax          : void System_Start(void)
* \Description     : Initializing and preparing the system for the first time
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void System_Start()
{
	/* Buzzer */
	DIO_vSetPinDir(PORTC_ID, PIN0_ID, DIR_OUTPUT);	
	DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_LOW);
	
	/* Fan */
	DIO_vSetPinDir(PORTA_ID, PIN2_ID, DIR_OUTPUT);
	DIO_vSetPinVal(PORTA_ID, PIN2_ID, VAL_LOW);

	/* Keypad Activiation LED */
	DIO_vSetPinDir(PORTB_ID, PIN7_ID, DIR_OUTPUT);
	DIO_vSetPinVal(PORTB_ID, PIN7_ID, VAL_LOW);
	
	/* Electrical Device Relay Pin */
	DIO_vSetPinDir(PORTD_ID, PIN7_ID, DIR_OUTPUT);	
	DIO_vSetPinVal(PORTD_ID, PIN7_ID, VAL_LOW);
	/* LEDs Intensity Direction and Value */
	DIO_vSetPinDir(PORTC_ID, PIN1_ID, DIR_OUTPUT);	DIO_vSetPinVal(PORTC_ID, PIN1_ID, VAL_LOW);
	DIO_vSetPinDir(PORTC_ID, PIN2_ID, DIR_OUTPUT);	DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_LOW);
	DIO_vSetPinDir(PORTC_ID, PIN3_ID, DIR_OUTPUT);	DIO_vSetPinVal(PORTC_ID, PIN3_ID, VAL_LOW);
	
	/* ADC sending first chain */
	ADC_StartChain(&chain);
	
	/* EEPROM password Init */
	for(u8 i=0; EEPROM_u8Read(i) != 'q'; i++){	/*Password terminated with q*/
		password[i] = EEPROM_u8Read(i);
		//HC_vSendData(password[i]);
	}
	
	/* Servo */
	SERVO_vInit();
	SERVO_vTurnOn();			/* Enable servo */
	SERVO_vSetState(STATE_0);	/* Initially Locked */
	
	/* DC motor*/
	DCM_vInit();
	DCM_vTurnOff();

	EXTI_vReg_Func(&StartKeypad, INT0_ID);
	HC_u8ReceiveDataAsync(&System_UartHandler);
}


/******************************************************************************
* \Syntax          : void System_WakeUp(void)        
* \Description     : Waking the system-up and doing its functions
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None 
*******************************************************************************/
void System_WakeUp()
{
	
	u8 L_u8Char = NO_PRESSED_KEY;
	while (1)
	{
		if (Home_State == _HOME_KEYPAD_STATE)
		{
			L_u8Char = KeyPad_u8GetPressedKey();

			if(L_u8Char == '#')		/* Enter Button */
			{
				trials--;
				if( strcmp(password, tempPassword) == 0)	/* Correct Password */
				{
					DIO_vSetPinVal(PORTB_ID, PIN7_ID, VAL_LOW);		/* Turn LED OFF */
					TIM0_vTurnOff();
					LCD_vClrDisp();
					_delay_ms(100);
					LCD_vDispStr("WELCOME !!!");
					_delay_ms(1000);
					LCD_vClrDisp();
					Home_State = _HOME_UNLOCKED;
					trials = 4;
				}
				else{		/* Incorrect Password */
					TIM0_vDelayMilli(8000, 0, &Timer0Elapsed_KeyOFF);
					/*			Buzzer Beep			 */
					DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_HIGH);
					_delay_ms(50);
					DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_LOW);
					_delay_ms(50);
					DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_HIGH);
					_delay_ms(50);
					DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_LOW);
					
					LCD_vClrDisp();
					_delay_ms(100);
					LCD_vDispStr("Wrong Password !");
					_delay_ms(500);

					if (trials == 1)	/*	System LockDown	 */
					{
						LCD_vClrDisp();
						_delay_ms(100);
						DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_HIGH);		/* Buzzer Warning */
						LCD_vDispStr("System LockDown");
						_delay_ms(2000);
						/*	TODO: Send Warning Message */

						LCD_vClrDisp();
						Home_State = _HOME_LOCKDOWN_STATE;
					}
					else { Animation1_LcdPassword(); }	/* Try Again */
				}
				/* Resetting Password */
				password_i = 0;
				for(u8 i=0 ; i<8 ; i++)	tempPassword[i] = 0;
			}
			else if(L_u8Char != NO_PRESSED_KEY)
			{
				TIM0_vDelayMilli(8000, 0, &Timer0Elapsed_KeyOFF);
				/*			Buzzer Beep			 */
				DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_HIGH);
				_delay_ms(25);
				DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_LOW);
				tempPassword[password_i] = L_u8Char;
				password_i++;
				LCD_vDispChar('*');
			}
		}
		else if(Home_State == _HOME_UNLOCKED)
		{
			ADC_StartChain(&chain);
			_delay_ms(100);
			/* LED INTENSITY CONTROL IF AUTOMATIC */
			if(G_u8LightsMode == AUTOMATIC)
				LedIntensity_AutoControl();
			else;	/* Do Nothing */
			_delay_ms(1000);
			
		}
		else;	/* What State ??? */
	}
}



/******************************************************************************
* \Syntax          : void LedIntensity_AutoControl(void)        
* \Description     : Automatic control of the LEDs based on the intensity value
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None 
*******************************************************************************/
void LedIntensity_AutoControl()
{
	if 		(channelsValues[LDR_CHANNEL] <= 2000)		/* Level 1: Sunny*/
		DIO_vPortVal_Maked(PORTC_ID, 0xF1, CLEAR_OPERATION);
	else if (channelsValues[LDR_CHANNEL] <= 3000){		/* Level 2 */
		DIO_vPortVal_Maked(PORTC_ID, 0xF1, CLEAR_OPERATION);
		DIO_vSetPinVal(PORTC_ID, PIN1_ID, VAL_HIGH);
	}
	else if (channelsValues[LDR_CHANNEL] <= 5000){		/* Level 3 */
		DIO_vPortVal_Maked(PORTC_ID, 0xF1, CLEAR_OPERATION);
		DIO_vSetPinVal(PORTC_ID, PIN2_ID, VAL_HIGH);
		DIO_vSetPinVal(PORTC_ID, PIN3_ID, VAL_HIGH);
	}
	else	/* Level 4: Night */
		DIO_vPortVal_Maked(PORTC_ID, 0x0E, SET_OPERATION);
}


/******************************************************************************
* \Syntax          : void FanSpeed_AutoControl(void)
* \Description     : Automatic control of the Fan based on the temprature
*******************************************************************************/
void FanSpeed_AutoControl(){
	if(channelsValues[TEMP_INDEX] < 10){
		DCM_vSetPWM(0);
		G_u8HomeSatus[FAN_STATUS_INDEX] = 's';		/* Setting the new status */
	}
	else if(channelsValues[TEMP_INDEX] < 15)	DCM_vSetPWM(20);
	else if(channelsValues[TEMP_INDEX] < 20)	DCM_vSetPWM(30);
	else if(channelsValues[TEMP_INDEX] < 25)	DCM_vSetPWM(40);
	else if(channelsValues[TEMP_INDEX] < 30)	DCM_vSetPWM(60);
	else if(channelsValues[TEMP_INDEX] < 35)	DCM_vSetPWM(80);
	else if(channelsValues[TEMP_INDEX] < 100)	DCM_vSetPWM(100);
	else ;	/*UNDEFINED*/
	if(channelsValues[TEMP_INDEX] > 10)		/* Do Nothing */
		G_u8HomeSatus[FAN_STATUS_INDEX] = 'r';
}