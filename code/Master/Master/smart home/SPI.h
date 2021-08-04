/*
 * SPI.h
 *
 * Created: 5/25/2020 8:04:19 PM
 *  Author: Arafa
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "STD_Types.h"
#include "std_messages.h"
#include "std_macros.h"

#define SPI_PORT (uint8)'B'
#define SPI_SCK  7
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SS   4


void SPI_vInitMaster(void);

void SPI_vInitSlave(void);

uint8 SPI_u8TransmitRecive(uint8 data);




#endif /* SPI_H_ */