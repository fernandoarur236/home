/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: HC-12		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 06/11/2022	 	**************/
/*********************************************************/


#ifndef HC_PRI_H_
#define HC_PRI_H_

/***********		Modes macros		 	**************/
#define FU1	"AT+FU1"
#define FU2	"AT+FU2"
#define FU3	"AT+FU3"
#define FU4	"AT+FU4"

/***********		Baud rate options		 	**************/
#define BAUD_1200     UART_8MHZ_BAUD_RATE_1200
#define BAUD_2400	  UART_8MHZ_BAUD_RATE_2400
#define BAUD_4800	  UART_8MHZ_BAUD_RATE_4800
#define BAUD_9600	  UART_8MHZ_BAUD_RATE_9600
#define BAUD_19200	  UART_8MHZ_BAUD_RATE_19200
#define BAUD_38400    UART_8MHZ_BAUD_RATE_38400
#define BAUD_57600	  UART_8MHZ_BAUD_RATE_57600
#define BAUD_115200	  UART_8MHZ_BAUD_RATE_115200

/***********		Power options		 	**************/
#define	PW_NEG_1DB  "AT+P1"
#define PW_2DB		"AT+P2"
#define PW_5DB		"AT+P3"
#define PW_8DB		"AT+P4"
#define PW_11DB		"AT+P5"
#define PW_14DB		"AT+P6"
#define PW_17DB		"AT+P7"
#define PW_20DB		"AT+P8"


#define AT_COMMAND	"AT+"

static void sendCommand(u8 A_u8Command[]);

#endif /* HC_PRI_H_ */
