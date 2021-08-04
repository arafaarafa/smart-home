/*
 * menu.c
 *
 * Created: 6/13/2020 11:44:46 AM
 *  Author: Arafa
 */ 

#include "menu.h"

extern volatile uint16 session_counter;
extern uint8 timeout_flag;


uint8 MENU_u8ComparePassword(const uint8 *pass1, const uint8 *pass2, const uint8 size){
	
	uint8 pin_counter = 0;
	uint8 return_value = TRUE;
	while(pin_counter<size){
		if(*(pass2+pin_counter) != *(pass1+pin_counter))
			return (return_value = FALSE);
		pin_counter++;
	}
	return return_value;
}

uint8 MENU_u8GetKeyPressed(const uint8 loginmode){
	uint8 key_pressed = NOT_PRESSED;
	while(key_pressed == NOT_PRESSED){
		if((session_counter >= ADMIN_TIMEOUT && loginmode == ADMIN)||(session_counter >= GUEST_TIMEOUT && loginmode == GUEST))
			{
				timeout_flag = TRUE;
				break;
			}
			key_pressed=keypad_u8CheckPress();
	}
	return key_pressed;
}

void MENU_vOptions(const uint8 selectedroom, const uint8 loginmode){
	uint8 statuscode	= 0;
	uint8 turnoncode	= 0;
	uint8 turnoffcode	= 0;
	uint8 response		= DEFAULT_ACK;
	uint8 key_pressed	= NOT_PRESSED;
	do 
	{
		LCD_vClearScreen();
		switch (selectedroom)
		{
		case ROOM1_MENU:
			statuscode  = ROOM1_STATUS;
			turnoncode  = ROOM1_TURN_ON;
			turnoffcode = ROOM1_TURN_OFF;
			LCD_vSendString("ROOM1 S:");
		break;
		case ROOM2_MENU:
		statuscode  = ROOM2_STATUS;
		turnoncode  = ROOM2_TURN_ON;
		turnoffcode = ROOM2_TURN_OFF;
		LCD_vSendString("ROOM2 S:");
		break;
		case ROOM3_MENU:
		statuscode  = ROOM3_STATUS;
		turnoncode  = ROOM3_TURN_ON;
		turnoffcode = ROOM3_TURN_OFF;
		LCD_vSendString("ROOM3 S:");
		break;
		case ROOM4_MENU:
		statuscode  = ROOM4_STATUS;
		turnoncode  = ROOM4_TURN_ON;
		turnoffcode = ROOM4_TURN_OFF;
		LCD_vSendString("ROOM4 S:");
		break;
		case TV_MENU:
		statuscode  = TV_STATUS;
		turnoncode  = TV_TURN_ON;
		turnoffcode = TV_TURN_OFF;
		LCD_vSendString("TV S:");
		break;
		case AIRCOND_CTRL_MENU:
		statuscode  = AIR_COND_STATUS;
		turnoncode  = AIR_COND_TURN_ON;
		turnoffcode = AIR_COND_TURN_OFF;
		LCD_vSendString("AIR COND S:");
		break;
		}
		
		SPI_u8TransmitRecive(statuscode);
		_delay_ms(100);
		response = SPI_u8TransmitRecive(DEMAND_RESPONCE);
		if(response == ON_STATUS)
			LCD_vSendString("ON");
		else
			LCD_vSendString("OFF");
		LCD_vMoveCursor(2,1);
		LCD_vSendString("1-on 2-off 0-ret");
		
		key_pressed = MENU_u8GetKeyPressed(loginmode);
		_delay_ms(100);
		
		if(key_pressed=='1')
			SPI_u8TransmitRecive(turnoncode);
		else if(key_pressed == '2')
			SPI_u8TransmitRecive(turnoffcode);
		else if((key_pressed != NOT_PRESSED)&&(key_pressed != '0'))
		{
			LCD_vClearScreen();
			LCD_vSendString("Wrong input");
			_delay_ms(500);
		}	
		
	} while (((key_pressed<'0')||(key_pressed>'2')) && (timeout_flag == FALSE));
}