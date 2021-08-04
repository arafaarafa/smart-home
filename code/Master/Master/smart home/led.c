/*
 * led.c
 *
 * Created: 6/10/2020 6:54:30 PM
 *  Author: Arafa
 */ 
#include "led.h"
void LED_vInit(uint8 portname, uint8 pinnumber){
	DIO_vSetPinDir(portname,pinnumber,1);
}
void LED_vTurnOn(uint8 portname , uint8 pinnumber){
	DIO_vWrite(portname,pinnumber,1);
}
void LED_vTurnOff(uint8 portname , uint8 pinnumber){
	DIO_vWrite(portname, pinnumber, 0);
}
void LED_vToggle(uint8 portname , uint8 pinnumber){
	DIO_vToggle(portname,pinnumber);
}
uint8 LED_u8ReadStatus(uint8 portname ,uint8 pinnumber){
	return DIO_u8Read(portname,pinnumber);
}