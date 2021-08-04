/*
 * ADC_driver.c
 *
 * Created: 6/15/2020 9:39:34 PM
 *  Author: Arafa
 */ 
#include "ADC_driver.h"
void ADC_vInit(){
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	
	SET_BIT(ADCSRA,ADEN);
	
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}
uint16 ADC_u16Read(uint8 pinnumber){
	ADMUX&=0XF0;
	ADMUX|=pinnumber;
	SET_BIT(ADCSRA,ADSC);
	while((ADCSRA&(1<<ADSC)));
	return ADC;
}
