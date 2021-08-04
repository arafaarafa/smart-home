/*
 * lcd.h
 *
 * Created: 6/10/2020 3:24:25 PM
 *  Author: Arafa
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"
#include "lcd_config.h"

#define CLR_SCREEN				0x01
#define DISPLAY_ON_SCREEN_ON	0x0e
#define EIGHT_BIT_MODE			0x38
#define FOUR_BIT_MODE_I			0x02
#define FOUR_BIT_MODE_II		0x28

void LCD_vInit(void);
void LCD_vSendCmd(uint8 cmd);
void LCD_vSendChar(uint8 data);
void LCD_vSendString(char *data);
void LCD_vClearScreen(void);
void LCD_vMoveCursor(uint8 row, uint8 col );


#endif /* LCD_H_ */