/*
 * DIO.h
 *
 * Created: 5/25/2020 7:59:16 AM
 *  Author: Arafa
 */ 


#ifndef DIO_H_
#define DIO_H_
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_config_master.h"
#include "STD_Types.h"



void DIO_vSetPinDir(uint8 portname, uint8 pinnumber, uint8 direction);

void DIO_vWrite(uint8 portname, uint8 pinnumber, uint8 outputvalue);

uint8 DIO_u8Read(uint8 portname, uint8 pinnumber);

void DIO_vToggle(uint8 portname, uint8 pinnumber);

void DIO_vWritePort(uint8 portname, uint8 portvalue);

void DIO_vClearHighNibble(uint8 portname);

void DIO_vWriteHighNibble(uint8 portname, uint8 value);

void DIO_vConnectPullUP(uint8 portname, uint8 pinnumber, uint8 connectpullup);




#endif /* DIO_H_ */