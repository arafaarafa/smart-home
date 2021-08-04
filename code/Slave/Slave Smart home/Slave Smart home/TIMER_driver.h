/*
 * TIMER_driver.h
 *
 * Created: 6/15/2020 10:52:32 PM
 *  Author: Arafa
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD_marcos.h"
#include "STD_types.h"


void TIMER0_vInitCTC();
void TIMER0_vStop();
void TIMER0_vInitFastPWM();
void TIMER0_vChangeDutyCycle(float64 duty);



#endif /* TIMER_DRIVER_H_ */