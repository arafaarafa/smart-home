/*
 * DIO.h
 *
 * Created: 6/16/2020 12:47:25 AM
 *  Author: Arafa
 */ 


#ifndef DIO_H_
#define DIO_H_
#define F_CPU 8000000ul
#include <util/delay.h>
#include "DIO_slave.h"
#include "STD_types.h"
#include "STD_marcos.h"
#include <avr/io.h>


void DIO_vSetPinDir(uint8 portname,uint8 pinnumber,uint8 direction);

void DIO_vWrite(uint8 portname, uint8 pinnumber, uint8 outputvalue);

uint8 DIO_u8Read(uint8 portname, uint8 pinnumber);

void DIO_vToggle(uint8 portname, uint8 pinnumber);

void DIO_vWritePort(uint8 portname, uint8 pinnumber,uint8 portvalue);

void DIO_vConnectPullUp(uint8 portname, uint8 pinnumber,uint8 connect_pullup);



#endif /* DIO_H_ */