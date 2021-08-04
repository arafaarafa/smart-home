/*
 * menu.h
 *
 * Created: 6/13/2020 11:45:06 AM
 *  Author: Arafa
 */ 


#ifndef MENU_H_
#define MENU_H_
#include "main_config.h"
#include "std_messages.h"
#include "STD_Types.h"
#include "keypad.h"
#include "SPI.h"
#include "lcd.h"



uint8 MENU_u8ComparePassword(const uint8 *pass1, const uint8 *pass2, const uint8 size);

void MENU_vOptions(const uint8 selectedroom, const uint8 loginmode);

uint8 MENU_u8GetKeyPressed(const uint8 loginmode); 




#endif /* MENU_H_ */