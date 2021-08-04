/*
 * timer_driver.h
 *
 * Created: 6/10/2020 7:53:58 PM
 *  Author: Arafa
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_macros.h"
#include "STD_Types.h"

void TIMER0_vInitCtc(void);

void TIMER0_vStop(void);

void TIMER0_vInitFastPwm(void);

void TIMER0_vChangeDutyCycle(float64 duty);

#endif /* TIMER_DRIVER_H_ */