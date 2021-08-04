/*
 * smart home.c
 *
 * Created: 5/24/2020 8:01:49 PM
 * Author : Arafa
 */ 

#include <avr/io.h>
#include "DIO.h"
#include "main_config.h"
#include "lcd.h"
#include "led.h"
#include "keypad.h"
#include "SPI.h"
#include "timer_driver.h"
#include "menu.h"
#include "EEPROM.h"

volatile uint16 session_counter = 0;
uint8 timeout_flag = FALSE;

int main(void)
{
	uint8 temperature = 0;
	uint8 temp_ones = NOT_SELECTED;
	uint8 temp_tens = NOT_SELECTED;
	
	uint8 login_mode = NO_MODE;
	uint8 block_mode_flag = FALSE;
	uint8 key_pressed = NOT_PRESSED;
	
	LED_vInit(ADMIN_LED_PORT,ADMIN_LED_PIN);
	LED_vInit(GUEST_LED_PORT,GUEST_LED_PIN);
	LED_vInit(BLOCK_LED_PORT, BLOCK_LED_PIN);
	LCD_vInit();
	keypad_vInit();
	SPI_vInitMaster();
	
	
	LCD_vSendString("WELCOME TO SMART");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("HOME SYSTEM");
	_delay_ms(1000);
	LCD_vClearScreen();
	if((EEPROM_ui8ReadByteFromAddress(ADMIN_PASS_STATUS_ADDRESS)!= PASS_SET)||(EEPROM_ui8ReadByteFromAddress(GUEST_PASS_STATUS_ADDRESS)!= PASS_SET))
    {
		LCD_vSendString("login for");
		LCD_vMoveCursor(2,1);
		LCD_vSendString("first time");
		_delay_ms(1000);
		LCD_vClearScreen();
		LCD_vMoveCursor(2,1);
		LCD_vSendString("ADMIN PASS:");
		
		uint8 pass_counter = 0;
		uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			while(pass_counter<PASS_SIZE){
				key_pressed = NOT_PRESSED;
				while(key_pressed==NOT_PRESSED){
					key_pressed =keypad_u8CheckPress();
				}
				pass[pass_counter]=key_pressed;
				LCD_vSendChar(key_pressed);
				_delay_ms(CHARACTER_PREVIEW_TIME);
				LCD_vMoveCursor(2,12+pass_counter);
				LCD_vSendChar(PASSWORD_SYMBOL);
				_delay_ms(100);
				pass_counter++;
			}
			EEPROM_vWriteBlockToAddress(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);
			EEPROM_vWriteByteToAddress(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);
			LCD_vClearScreen();
			LCD_vSendString("pass saved");
			_delay_ms(500);
			LCD_vClearScreen();
				
				
		pass_counter=0;
		LCD_vSendString("set guest pass");
		LCD_vMoveCursor(2,1);
		LCD_vSendString("guest pass:");
			while(pass_counter<PASS_SIZE){
				key_pressed =NOT_PRESSED;
				while(key_pressed == NOT_PRESSED){
					key_pressed = keypad_u8CheckPress();
				}
				pass[pass_counter] = key_pressed;
				LCD_vSendChar(key_pressed);
				_delay_ms(CHARACTER_PREVIEW_TIME);
				LCD_vMoveCursor(2,12+pass_counter);
				LCD_vSendChar(PASSWORD_SYMBOL);
				_delay_ms(100);
				pass_counter++;
					
			}
			EEPROM_vWriteBlockToAddress(EEPROM_GUEST_ADDRESS,pass,PASS_SIZE);
			EEPROM_vWriteByteToAddress(GUEST_PASS_STATUS_ADDRESS,PASS_SET);
			LCD_vClearScreen();
			LCD_vSendString("pass saved");
			_delay_ms(500);
			LCD_vClearScreen();
			EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);
				
	}
	else{
		block_mode_flag = EEPROM_ui8ReadByteFromAddress(LOGIN_BLOCKED_ADDRESS);
	}
	
	/* Replace with your application code */
    while (1) 
    {
		key_pressed = NOT_PRESSED ;
		uint8 pass_tries_count = 0;
		 if(timeout_flag ==TRUE){
			 TIMER0_vStop();
			 session_counter = 0;
			 timeout_flag = FALSE;
			 login_mode = NO_MODE;
			 key_pressed = NOT_PRESSED;
			 LED_vTurnOff(GUEST_LED_PORT, GUEST_LED_PIN);
			 LED_vTurnOff(ADMIN_LED_PORT, ADMIN_LED_PIN);
			 LCD_vClearScreen();
			 LCD_vSendString("SESSION TIMEOUT");
			 _delay_ms(1000);
		 }
		 while(login_mode == NO_MODE){
			 if(block_mode_flag == TRUE){
				 LCD_vClearScreen();
				 LCD_vSendString("login blocked");
				 LCD_vMoveCursor(2,1);
				 LCD_vSendString("wait 20seconds");
				 LED_vTurnOn(BLOCK_LED_PORT, BLOCK_LED_PIN);
				 _delay_ms(BLOCK_MODE_TIME);
				 pass_tries_count=0;
				 block_mode_flag = FALSE;
				 LED_vTurnOff(BLOCK_LED_PORT, BLOCK_LED_PIN);
				 EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);
			 }
			 LCD_vClearScreen();
			 LCD_vSendString("Select mode");
			 LCD_vMoveCursor(2,1);
			 LCD_vSendString("0:ADMIN 1:GUEST");
			 while(key_pressed == NOT_PRESSED){
				 key_pressed = keypad_u8CheckPress();
			 }
			 if(key_pressed != CHECK_ADMIN_MODE && key_pressed != CHECK_GUEST_MODE){
				 LCD_vClearScreen();
				 LCD_vSendString("Wrong Input");
				 key_pressed = NOT_PRESSED;
				 _delay_ms(1000);
				 continue;
			 }
			 uint8 pass_counter=0;
			 uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			 uint8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			 switch(key_pressed){
				 case CHECK_ADMIN_MODE:
					while(login_mode != ADMIN){
						key_pressed = NOT_PRESSED;
						LCD_vClearScreen();
						LCD_vSendString("ADMIN Mode");
						LCD_vMoveCursor(2,1);
						LCD_vSendString("Enter pass:");
						_delay_ms(200);
						pass_counter=0;
						while(pass_counter<PASS_SIZE){
							while(key_pressed == NOT_PRESSED){
								key_pressed = keypad_u8CheckPress();
							}
							pass[pass_counter]= key_pressed;
							LCD_vSendChar(key_pressed);
							_delay_ms(CHARACTER_PREVIEW_TIME);
							LCD_vMoveCursor(2,12+pass_counter);
							LCD_vSendChar(PASSWORD_SYMBOL);
							_delay_ms(100);
							pass_counter++;
							key_pressed = NOT_PRESSED;
						}
						EEPROM_vReadBlockFromAddress(EEPROM_ADMIN_ADDRESS,stored_pass,PASS_SIZE);
						if(MENU_u8ComparePassword(pass,stored_pass,PASS_SIZE)==TRUE){
							login_mode = ADMIN;
							pass_tries_count = 0;
							LCD_vClearScreen();
							LCD_vSendString("Right pass");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("ADMIN Mode");
							_delay_ms(500);
							LED_vTurnOn(ADMIN_LED_PORT, ADMIN_LED_PIN);
							TIMER0_vInitCtc();
							LCD_vClearScreen();
						}
						else{
							pass_tries_count++;
							login_mode = NO_MODE;
							LCD_vClearScreen();
							LCD_vSendString("Wrong pass");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("TRIES LEFT:");
							LCD_vSendChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
							_delay_ms(1000);
							LCD_vClearScreen();
							if(pass_tries_count>= TRIES_ALLOWED){
								EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);
								block_mode_flag= TRUE;
								break;
							}
							
						}
					}
				 
				 break;
				 case CHECK_GUEST_MODE:
					while(login_mode != GUEST){
						key_pressed =NOT_PRESSED;
						LCD_vClearScreen();
						LCD_vSendString("GEUST MODE");
						LCD_vMoveCursor(2,1);
						LCD_vSendString("ENTER PASS:");
						_delay_ms(200);
						pass_counter=0;
						while(pass_counter<PASS_SIZE){
							while(key_pressed == NOT_PRESSED){
								key_pressed = keypad_u8CheckPress(); 
							}
							pass[pass_counter]=key_pressed;
							LCD_vSendChar(key_pressed);
							_delay_ms(CHARACTER_PREVIEW_TIME);
							LCD_vMoveCursor(2,12+pass_counter);
							LCD_vSendChar(PASSWORD_SYMBOL);
							_delay_ms(100);
							pass_counter++;
							key_pressed = NOT_PRESSED;
						}
						EEPROM_vReadBlockFromAddress(EEPROM_GUEST_ADDRESS,stored_pass,PASS_SIZE);
						
						if (MENU_u8ComparePassword(stored_pass,pass,PASS_SIZE) == TRUE)
						{
							login_mode =GUEST;
							pass_tries_count = 0;
							LCD_vClearScreen();
							LCD_vSendString("Right pass");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("GUEST MODE");
							_delay_ms(500);
							LED_vTurnOn(GUEST_LED_PORT,GUEST_LED_PIN);
							TIMER0_vInitCtc();
							LCD_vClearScreen();
						} 
						else
						{
							pass_tries_count++;
							login_mode = NO_MODE;
							LCD_vClearScreen();
							LCD_vSendString("Wrong pass");
							LCD_vMoveCursor(2,1);
							LCD_vSendString("Tries left");
							LCD_vSendChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
							_delay_ms(1000);
							LCD_vClearScreen();
							if(pass_tries_count>= TRIES_ALLOWED){
								EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);
								block_mode_flag = TRUE;
								break;
								
							}
						}
						
					}
				 
				 break;
			 }
		 }
		 uint8 show_menu = MAIN_MENU;
		 while (timeout_flag != TRUE)
		 {
			 key_pressed = NOT_PRESSED;
			 switch (show_menu)
			 {
			 case MAIN_MENU:
				do 
				{
					LCD_vClearScreen();
					LCD_vSendString("1:Room1 2:Room2");
					LCD_vMoveCursor(2,1);
					if (login_mode == ADMIN)
					{
						LCD_vSendString("3:Room3 4:More");
					}else if(login_mode == GUEST){
						LCD_vSendString("3:Room3 4:Room4");
					}
					key_pressed =MENU_u8GetKeyPressed(login_mode);
					_delay_ms(100);
					if (key_pressed == SELECT_ROOM1){
						show_menu = ROOM1_MENU;
					}else if(key_pressed == SELECT_ROOM2){
						show_menu = ROOM2_MENU;
					}else if(key_pressed == SELECT_ROOM3){
						show_menu = ROOM3_MENU;
					}else if(key_pressed == SELECT_ROOM4 && login_mode == GUEST){
						show_menu = ROOM4_MENU;
					}else if(key_pressed == ADMIN_MORE_OPTION && login_mode == ADMIN){
						show_menu = MORE_MENU;
					}else if(key_pressed != NOT_PRESSED){
						LCD_vClearScreen();
						LCD_vSendString("WRONG INPUT");
						_delay_ms(500);
					}
				} while ((key_pressed<'1' || key_pressed>'4')&& timeout_flag != TRUE );
			 break;
			 case MORE_MENU:
				do 
				{
					LCD_vClearScreen();
					LCD_vSendString("1:Room4 2:TV");
					LCD_vMoveCursor(2,1);
					LCD_vSendString("3:AIRCond 4:RET");
					key_pressed =MENU_u8GetKeyPressed(login_mode);
					_delay_ms(100);
					if(key_pressed == SELECT_ROOM4_ADMIN){
						show_menu = ROOM4_MENU;
					}else if(key_pressed == SELECT_TV){
						show_menu = TV_MENU;
					}else if(key_pressed == SELECT_AIR_CONDITIONING){
						show_menu = AIRCONDITIONING_MENU;
					}else if(key_pressed == ADMIN_RET_OPTION){
						show_menu = MAIN_MENU;
					}else if (key_pressed != NOT_PRESSED){
						LCD_vClearScreen();
						LCD_vSendString("Wrong Input");
						_delay_ms(500);
					}
				} while ((key_pressed<'1' || key_pressed>'4')&& timeout_flag == FALSE);
			 break;	 
			 case AIRCONDITIONING_MENU:
				do 
				{
					LCD_vClearScreen();
					LCD_vSendString("1:Set temperature");
					LCD_vMoveCursor(2,1);
					LCD_vSendString("2:Control 0:Ret");
					
					key_pressed = MENU_u8GetKeyPressed(login_mode);
					_delay_ms(100);
					
					if (key_pressed == SELECT_SET_TEMPERATURE){
						show_menu =TEMPERATURE_MENU;
					}else if(key_pressed == SELECT_AIR_COND_CTRL){
						show_menu =AIRCOND_CTRL_MENU;
					}else if(key_pressed == SELECT_AIR_COND_RET){
						show_menu = MORE_MENU;
					}else if (key_pressed != NOT_PRESSED){
						LCD_vClearScreen();
						LCD_vSendString("Wrong Input");
						_delay_ms(500);
					}
				} while ((key_pressed<'1' || key_pressed > '4') && timeout_flag == FALSE );
			 break;
			 case ROOM1_MENU:
				MENU_vOptions(ROOM1_MENU, login_mode);
				show_menu = MAIN_MENU;
			 break;
			 case ROOM2_MENU:
				MENU_vOptions(ROOM2_MENU, login_mode);
				show_menu = MAIN_MENU;
			 break;
			 case ROOM3_MENU:
				MENU_vOptions(ROOM3_MENU, login_mode);
				show_menu = MAIN_MENU;
			 break;
			 case ROOM4_MENU:
				MENU_vOptions(ROOM4_MENU, login_mode);
				if (login_mode == GUEST){
					show_menu = MAIN_MENU;
				}else{
					show_menu = MORE_MENU;
				}
			 break;
			 case TV_MENU:
				MENU_vOptions(TV_MENU, login_mode);
				show_menu=MORE_MENU;
			 break;
			 case AIRCOND_CTRL_MENU:
				MENU_vOptions(AIRCOND_CTRL_MENU, login_mode);
				show_menu =AIRCONDITIONING_MENU;
			 break;
			 case TEMPERATURE_MENU:
				temperature = 0;
				while(temperature == 0 && timeout_flag == FALSE){
					key_pressed = NOT_PRESSED;
					LCD_vClearScreen();
					LCD_vSendString("Set Temp:__");
					LCD_vSendChar(DEGREES_SYMBOL);
					LCD_vSendChar('C');
					LCD_vMoveCursor(1,10);
					_delay_ms(200);
					key_pressed = MENU_u8GetKeyPressed(login_mode);
					_delay_ms(250);
					if (timeout_flag == TRUE)
					{
						break;
					}
					if(key_pressed<'0' || key_pressed>'9'){
						LCD_vClearScreen();
						LCD_vSendString("Wrong input");
						_delay_ms(500);
						continue;
					}else{
						LCD_vSendChar(key_pressed);
						temp_tens = key_pressed- ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					key_pressed =MENU_u8GetKeyPressed(login_mode);
					_delay_ms(250);
					if(timeout_flag == TRUE){
						break;
					}
					if(key_pressed<'0'||key_pressed > '9'){
						LCD_vClearScreen();
						LCD_vSendString("Wrong Input");
						_delay_ms(500);
						continue;
					}else{
						LCD_vSendChar(key_pressed);
						temp_ones = key_pressed-ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					temperature = temp_tens*10 + temp_ones;
					SPI_u8TransmitRecive(SET_TEMPERATURE);
					_delay_ms(200);
					SPI_u8TransmitRecive(temperature);
					LCD_vClearScreen();
					LCD_vSendString("temp Sent");
					_delay_ms(500);
				}
				show_menu = AIRCONDITIONING_MENU;
				
			 break;
			 }
		 }
		 
    }
}
ISR(TIMER0_COMP_vect){
	session_counter++;
}

