/*
 * DIO.c
 *
 * Created: 6/16/2020 12:47:44 AM
 *  Author: Arafa
 */ 
#include "DIO.h"

void DIO_vSetPinDir(uint8 portname,uint8 pinnumber,uint8 direction){
	
	
	switch(portname){
		case 'A':
			if(direction==1)
				SET_BIT(DDRA,pinnumber);
			else
				CLR_BIT(DDRA,pinnumber);
		break;
		case 'B':
			if(direction==1)
			SET_BIT(DDRB,pinnumber);
			else
			CLR_BIT(DDRB,pinnumber);
		break;	
		case 'C':
			if(direction==1)
			SET_BIT(DDRC,pinnumber);
			else
			CLR_BIT(DDRC,pinnumber);
		break;
		case 'D':
			if(direction==1)
			SET_BIT(DDRD,pinnumber);
			else
			CLR_BIT(DDRD,pinnumber);
		break;	
	}
}

void DIO_vWrite(uint8 portname, uint8 pinnumber, uint8 outputvalue){
	
		switch(portname){
			case 'A':
			if(outputvalue==1)
				SET_BIT(PORTA,pinnumber);
			else
				CLR_BIT(PORTA,pinnumber);
			break;
			case 'B':
			if(outputvalue==1)
				SET_BIT(PORTB,pinnumber);
			else
				CLR_BIT(PORTB,pinnumber);
			break;
			case 'C':
			if(outputvalue==1)
				SET_BIT(PORTC,pinnumber);
			else
				CLR_BIT(PORTC,pinnumber);
			break;
			case 'D':
			if(outputvalue==1)
				SET_BIT(PORTD,pinnumber);
			else
				CLR_BIT(PORTD,pinnumber);
			break;
		}
}

uint8 DIO_u8Read(uint8 portname, uint8 pinnumber){
	uint8 return_value =0;
	switch(portname){
		case 'A':
			return_value = READ_BIT(PINA,pinnumber);
		break;
		case 'B':
			return_value = READ_BIT(PINB,pinnumber);
		break;
		case 'C':
			return_value = READ_BIT(PINC,pinnumber);
		break;
		case 'D':
			return_value = READ_BIT(PIND,pinnumber);
		break;
	}
	return return_value;
}
void DIO_vToggle(uint8 portname, uint8 pinnumber){
	switch (portname)
	{
		case 'A':
			TOG_BIT(PORTA,pinnumber);
		break;
		case 'B':
			TOG_BIT(PORTB,pinnumber);
		break;
		case 'C':
			TOG_BIT(PORTC,pinnumber);
		break;
		case 'D':
			TOG_BIT(PORTD,pinnumber);
		break;
		
	}
}

void DIO_vWritePort(uint8 portname, uint8 pinnumber,uint8 portvalue){
	switch (portname)
	{
		case 'A':
			PORTA=portvalue;
		break;
		case 'B':
			PORTB=portvalue;
		break;
		case 'C':
			PORTC=portvalue;
		break;
		case 'D':
			PORTD=portvalue;
		break;
		
	}
}

void DIO_vConnectPullUp(uint8 portname, uint8 pinnumber,uint8 connect_pullup){
	switch (portname)
	{
		case 'A':
			if(connect_pullup==1)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRA,pinnumber);
				SET_BIT(PORTA,pinnumber);
			}
			else
			{
				SET_BIT(SFIOR,PUD);
				CLR_BIT(DDRA,pinnumber);
				CLR_BIT(PORTA,pinnumber);
			}
		break;
		case 'B':
			if(connect_pullup==1)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRB,pinnumber);
				SET_BIT(PORTB,pinnumber);
			}
			else
			{
				SET_BIT(SFIOR,PUD);
				CLR_BIT(DDRB,pinnumber);
				CLR_BIT(PORTB,pinnumber);
			}
		break;
		case 'C':
			if(connect_pullup==1)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRC,pinnumber);
				SET_BIT(PORTC,pinnumber);
			}
			else
			{
				SET_BIT(SFIOR,PUD);
				CLR_BIT(DDRC,pinnumber);
				CLR_BIT(PORTC,pinnumber);
			}
		break;
		case 'D':
			if(connect_pullup==1)
			{
				CLR_BIT(SFIOR,PUD);
				CLR_BIT(DDRD,pinnumber);
				SET_BIT(PORTD,pinnumber);
			}
			else
			{
				SET_BIT(SFIOR,PUD);
				CLR_BIT(DDRD,pinnumber);
				CLR_BIT(PORTD,pinnumber);
			}
		break;
		
	}
}