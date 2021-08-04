/*
 * SPI.c
 *
 * Created: 5/25/2020 8:04:36 PM
 *  Author: Arafa
 */
#include <avr/io.h> 
#include "SPI.h"
#include "DIO.h"
#include "std_messages.h"
#include "std_macros.h"

void SPI_vInitMaster(void){
	/*DIO_vSetPinDir(SPI_PORT,SPI_MOSI,1);
	DIO_vSetPinDir(SPI_PORT,SPI_SCK,1);
	DIO_vSetPinDir(SPI_PORT,SPI_SS,1); 
	
	
	SET_BIT(SPCR,SPE);
	SET_BIT(SPCR,MSTR);
	SET_BIT(SPCR,SPR0);*/
	DDRB |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
	SPCR|= (1<<MSTR)|(1<<SPE)|(1<<SPR0);
	
}

void SPI_vInitSlave(void){
	DIO_vSetPinDir(SPI_PORT,SPI_MISO,1);
	SET_BIT(SPCR,SPE);
}

uint8 SPI_u8TransmitRecive(uint8 data){
	SPDR= data;
	while(((SPSR&(1<<SPIF))>>SPIF)==0)
	;
	return SPDR;
}
