/*
 * EEPROM.c
 *
 * Created: 5/24/2020 8:10:25 PM
 *  Author: Arafa
 */ 
#include "EEPROM.h"
#include <avr/io.h>
uint8 EEPROM_ui8ReadByteFromAddress(const uint16 u16Address){
	while(((EECR&(1<<EEWE))>>EEWE)==1)
	;
	EEAR = u16Address;
	EECR |= (1<<EERE);
	return EEDR;
}
void EEPROM_vWriteByteToAddress(const uint16 u16Address, const uint8 u8Data ){
	while(((EECR & (1 << EEWE))>>EEWE)==1)
	;
	EEAR= u16Address;
	EECR |= (1<<EERE);
	if(EEDR != u8Data){
		EEDR =u8Data;
		EECR |= (1<<EEMWE);
		EECR |= (1<< EEWE);
	}
}
void EEPROM_vReadBlockFromAddress(const uint16 u16Address, uint8* dist, const uint16 size ){
	while(((EECR&(1<<EEWE))>>EEWE)==1)
	;
	uint16 counter = 0;
	while(counter < size){
		EEAR = u16Address + counter;
		EECR |=(1<<EERE);
		*(dist + counter) =EEDR;
		counter++;
	}
}
void EEPROM_vWriteBlockToAddress(const uint16 u16Address, const uint8* u8Date, const uint16 size){
	/*uint16 counter =0;
	
	while(counter < size){
		while(((EECR&(1<<EEWE))>>EEWE)==1);
		EEAR= u16Address+counter;
		EECR|= (1<< EERE);
		if(EEDR != (*(u8Date+counter))){
			EEDR = *( u8Date +counter);
			EECR |=(1<< EEMWE);
			EECR |=(1<< EEWE);
		}
		counter++;
	}*/
	uint8 counter = 0;
	while (counter < size)
	{
		while(((EECR&(1<<EEWE))>>EEWE) == 1);
		EEAR = u16Address+counter;
		EEDR = *(u8Date+counter);
		EECR |= (1<<EEMWE);
		EECR |= (1<<EEWE);
		counter++;
	}
	
}