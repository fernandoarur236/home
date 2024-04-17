/*
 * ADC_reg.h
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_ADC_ADC_REG_H_
#define MCAL_ADC_ADC_REG_H_

/*ADMUX register*/
#define ADMUX  *( (u8*) 0x27)
/*pins*/
#define MUX0 0  /*Channel select*/
#define MUX1 1  /*Channel select*/
#define MUX2 2  /*Channel select*/
#define MUX3 3  /*Channel select*/
#define MUX4 4  /*Channel select*/
#define ADLAR 5 /*ADC left adjust result*/
#define REFS0 6 /*select ref*/
#define REFS1 7 /*select ref*/

/*ADCSRA*/
#define ADCSRA  *( (volatile u8*) 0x26)
/*Pins*/
#define ADPS0 0  /*pre-scale select*/
#define ADPS1 1  /*pre-scale select*/
#define ADPS2 2  /*pre-scale select*/
#define ADIE  3  /*Enable ADC*/
#define ADIF  4 /*ADC flag*/
#define ADATE 5 /*ADC auto trigger enable*/
#define ADSC  6 /*ADC start conversion*/
#define ADEN  7 /*ADC enable*/

/*ADCH*/
#define ADCH  *( (volatile u8*) 0x25)
/*ADCL*/
#define ADCL  *( (volatile u8*) 0x24)
/*ADCW*/
#define ADCW  *( (volatile u16*) 0x24) /*used to read the 10 bits of the result*/

/*SFIOR*/
#define SFIOR *( (u8*) 0x50)
/*pins*/
/*PIN 4 is reserved, pins 0,1,2,3 are for another peripheral*/
#define ADTS0 5  /*Trigger source*/
#define ADTS1 6  /*Trigger source*/
#define ADTS2 7  /*Trigger source*/

#endif /* MCAL_ADC_ADC_REG_H_ */
