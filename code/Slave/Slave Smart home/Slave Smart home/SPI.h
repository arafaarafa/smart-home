/*
 * SPI.h
 *
 * Created: 6/15/2020 11:53:30 PM
 *  Author: Arafa
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "STD_types.h"
#include "STD_messages.h"
#include "STD_marcos.h"
#include <avr/io.h>

#define  SPI_SCK  7
#define  SPI_MISO 6
#define  SPI_MOSI 5
#define  SPI_SS	  4
void SPI_vInitMaster(void);

void SPI_vInitSlave(void);

uint8 SPI_u8TransmitRecive(uint8 data);



#endif /* SPI_H_ */