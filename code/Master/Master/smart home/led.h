/*
 * led.h
 *
 * Created: 6/10/2020 6:54:13 PM
 *  Author: Arafa
 */ 


#ifndef LED_H_
#define LED_H_

#include "DIO.h"
#include "STD_Types.h"

void LED_vInit(uint8 portname, uint8 pinnumber);
void LED_vTurnOn(uint8 portname , uint8 pinnumber);
void LED_vTurnOff(uint8 portname , uint8 pinnumber);
void LED_vToggle(uint8 portname , uint8 pinnumber);
uint8 LED_u8ReadStatus(uint8 portname , uint8 pinnumber);





#endif /* LED_H_ */