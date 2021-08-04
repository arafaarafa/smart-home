/*
 * SPI.c
 *
 * Created: 6/15/2020 11:53:16 PM
 *  Author: Arafa
 */ 
#include "SPI.h"

void SPI_vInitMaster(){
	SET_BIT(DDRB, SPI_MOSI);
	SET_BIT(DDRB,SPI_SCK);
	SET_BIT(DDRB,SPI_SS);
	
	SET_BIT(SPCR,SPE);
	SET_BIT(SPCR,MSTR);
	SET_BIT(SPCR,SPR0);
	
}
void SPI_vInitSlave(){
	SET_BIT(DDRB, SPI_MISO);
	SET_BIT(SPCR,SPE);
	SET_BIT(SPCR,SPR0);
}
uint8 SPI_u8TransmitRecive(uint8 data){
	SPDR =data;
	while (((SPSR&(1<<SPIF))>>SPIF) == 0)
	;
	
	return SPDR;
}