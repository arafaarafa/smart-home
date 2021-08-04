/*
 * timer_driver.c
 *
 * Created: 6/10/2020 7:54:46 PM
 *  Author: Arafa
 */ 
#include "timer_driver.h"

void TIMER0_vInitCtc(void){
	OCR0 = 78;
	SET_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, WGM00);
	
	
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	
	sei();
	
	SET_BIT(TIMSK, OCIE0);
}

void TIMER0_vStop(void){
	
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
		
}

void TIMER0_vInitFastPwm(void){
	OCR0=128;
	
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	
	sei();
	
	SET_BIT(TCCR0,COM01);
	
	SET_BIT(TIMSK,TOIE0);
	
	SET_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
}

void TIMER0_vChangeDutyCycle(float64 duty){
	OCR0 = (duty/100)*256;
}
