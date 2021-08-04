/*
 * ADC_driver.h
 *
 * Created: 6/15/2020 9:40:01 PM
 *  Author: Arafa
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#include "STD_marcos.h"
#include "AVR/io.h" 
#include "STD_types.h"

void ADC_vInit();

uint16 ADC_u16Read(uint8 pinnumber); 




#endif /* ADC_DRIVER_H_ */