/*
 * ADC_prg.c
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "ADC_reg.h"
#include "ADC_pri.h"
#include "ADC_cfg.h"
#include "ADC_int.h"


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static u16* gAdcValuePtr = ADDRESS_NULL;

static u8* gAdcChainChannelsArr = ADDRESS_NULL;
static u16* gAdcChainResultsArr = ADDRESS_NULL;
static u8* gAdcChainSize = ADDRESS_NULL;
static u8 gAdcChainIndex;
static ptr_func_t ISR_ADCCHAINPTR;

static u8 gISR_conversionMode;


/*
 * Init the ADC: enable the ADEN bit, select the pre-scale value, select the reference voltage
 * select the ADLAR bit value.
 *
 * if need lower execution time you can use the default values of register
 * */
void ADC_vInit(){
	/*ADCSRA |= ( (1<<ADEN) | (ADC_PRE_SCALE << ADPS0) ); /*Enable ADC & setting PreScaler*/
	DIO_vSetPinDir(PORTA_ID, PIN0_ID, DIR_INPUT);
	DIO_vSetPinDir(PORTA_ID, PIN1_ID, DIR_INPUT);
    /*Set the pre-scaler*/
	ADCSRA &= ADC_PRESCALE_BIT_MASK;
	ADCSRA |= (ADC_PRE_SCALE<<ADPS0);

	/*Set the AutoTriggering mode*/
	CLR_BIT(ADCSRA, ADATE); /*No auto-triggering*/

	/*Selecting the Vref*/
	ADMUX = ( (ADMUX & (0b00111111)) | (ADC_VREF_SELECT << REFS0) );/*Selecting VREF*/

	/*setup the bits adjust*/
	WRT_BIT(ADMUX, ADLAR, ADC_ADJUST); /*Disable left adjust, although it is by default 0*/

	/*enable the ADC*/
	SET_BIT(ADCSRA, ADEN);
}

/*used only if needed during runtime*/
void ADC_vSetPreScale(u8 A_u8PreScaleVal){
	ADCSRA &= ADC_PRESCALE_BIT_MASK;
	ADCSRA |= (ADC_PRE_SCALE << ADPS0) ;
}

/*Read using interrupt*/
void ADC_vReadDigitalAsync(ptr_func_Iu16_Ov ptr, u8 A_u8ADCId){
	gISR_conversionMode = _ADC_ISR_SINGLECONVERSION;
	G_ISR_ADC = ptr; /*better to be the first instruction as conversion could be fast*/
	ADMUX = ( (ADMUX & (0b11100000)) | (A_u8ADCId << MUX0));/*Selecting the channel*/
	ADCSRA |= ((1<<ADIE) | (1<<ADSC));/*Starting conversion and enable interrupt*/
}

/*Read using polling*/
u16 ADC_u16ReadDigitalSync(u8 A_u8ADCId){
	ADMUX = ((ADMUX & (0b11100000)) | (A_u8ADCId << MUX0));/*Selecting the channel*/
	SET_BIT(ADCSRA, ADSC);/*Starting conversion*/
	while(GET_BIT(ADCSRA, ADSC) == 1);/*Wait till conversion is completed, this will lead to blockage therfore we can use
	time-out concept using timers or increamental variable*/

	return ADCW; /*get the resulted digital value*/
}

void ADC_vTurnOff(){
	CLR_BIT(ADCSRA, ADEN); /*turn off the ADC*/
}


/******************************************************************************
* \Syntax          : void ADC_StartChain(struct[chain])        
* \Description     : Setting a channels chain and setting their ISR conversion
* \Sync\Async      : ASynchronous                                               
* \Parameters (in) : [chain: struct containing the (channelsArray), (resultsArray),
                     (chainSize), (chain conversion complete notification)].
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void ADC_StartChain  ( ADC_stChain* chain )
{
    /* Choosing the ISR Multiconversion Mode */
    gISR_conversionMode = _ADC_ISR_MULTICONVERSION;

    /* Pointing to the channels array */
    gAdcChainChannelsArr = chain->channels;

    /* Pointing to the channels results array */
    gAdcChainResultsArr = chain->channelValues;

    /* Pointing to the chain size */
    gAdcChainSize = chain->chainSize;

    /* Pointing to the Chain Complete Notification */
    ISR_ADCCHAINPTR = chain->chainNotification;

    /* Resetting the chain index to start conversion */
    gAdcChainIndex = 0;
    
    /* Choosing first channel */
    ADMUX &= _ADC_CHANNEL_MASK;
    ADMUX |= (gAdcChainChannelsArr[gAdcChainIndex] << 0);

    ADCSRA |= ((1<<3) | (1<<6));       /* Enabling ADC Interrupt just in case and starting conversion */
}

void ADC_vDisable(){
	ADCSRA &= ~ (1<<7);
}
void ADC_vEnable(){
	ADCSRA |= (1<<7);
}

/*ISR for the ADC*/
void __vector_16 (void){
	if( gISR_conversionMode == _ADC_ISR_SINGLECONVERSION )
	{
		if( G_ISR_ADC != ADDRESS_NULL){
			*gAdcValuePtr = ADCW;
			G_ISR_ADC();
			CLR_BIT(ADCSRA, 3);       /* Disabling ADC Peripheral Interrupt */
		}
		else;   /* Do Nothing */
	}
	else if ( gISR_conversionMode == _ADC_ISR_MULTICONVERSION )
	{
		if( gAdcChainIndex == gAdcChainSize )   /* Chain channel is still under-going conversion */
		{
			ISR_ADCCHAINPTR();
			CLR_BIT(ADCSRA, 3);       /* Disabling ADC Peripheral Interrupt */
		}
		else    /* Whole chain didn't finish conversion yet */
		{
			gAdcChainResultsArr[gAdcChainIndex] = ADCW;
			/* Choosing next channel */
			gAdcChainIndex++;
			DIO_vTogPin(PORTD_ID, PIN7_ID);
			ADMUX &= _ADC_CHANNEL_MASK;
			ADMUX |= (gAdcChainChannelsArr[gAdcChainIndex] << 0);
			SET_BIT(ADCSRA, 6);
		}
	}
}



