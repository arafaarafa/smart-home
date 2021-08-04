/*
 * TIMER_deriver.c
 *
 * Created: 6/15/2020 10:53:05 PM
 *  Author: Arafa
 */ 

#include "TIMER_driver.h"

void TIMER0_vInitCTC(){
	OCR0 = 78;
	
	
	
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);
	
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	CLR_BIT(TCCR0,CS01);
	
	sei();
	SET_BIT(TIMSK, OCIE0);
	
}

void TIMER0_vStop(){
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
}
void TIMER0_vInitFastPWM(){
	
	OCR0 = 128;
	
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	
	sei();
	SET_BIT(TCCR0, COM01);
	
	SET_BIT(TIMSK,TOIE0);
	
	
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	
}
TIMER0_vChangeDutyCycle(float64 duty){
	OCR0 = (duty / 100) * 256;
}