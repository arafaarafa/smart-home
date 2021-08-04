/*
 * lcd.c
 *
 * Created: 6/10/2020 3:24:00 PM
 *  Author: Arafa
 */ 

#include "lcd.h"
static void LCD_vSendFallingEdge(void);
void LCD_vInit(void){
	#ifdef eight_bits_mode
		DIO_vSetPinDir(LCD_PORT, LCD_FIRST_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_SECOND_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_THIRD_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_FOURTH_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_FIFTH_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_SIXTH_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_SEVENTH_PIN, 1);
		DIO_vSetPinDir(LCD_PORT, LCD_EIGHTH_PIN, 1);
		
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_EN_PIN, 1);
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_RW_PIN, 1);
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_RS_PIN, 1);
		
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RW_PIN, 0);
		LCD_vSendCmd(EIGHT_BIT_MODE);
		LCD_vSendCmd(CLR_SCREEN);
		LCD_vSendCmd(DISPLAY_ON_SCREEN_ON);
		_delay_ms(10);
	#elif defined(four_bit_mode)
		DIO_vSetPinDir(LCD_PORT, LCD_FIFTH_PIN,1);
		DIO_vSetPinDir(LCD_PORT, LCD_SIXTH_PIN,1);
		DIO_vSetPinDir(LCD_PORT, LCD_SEVENTH_PIN,1);
		DIO_vSetPinDir(LCD_PORT, LCD_EIGHTH_PIN,1);
		
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_EN_PIN, 1);
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_RW_PIN, 1);
		DIO_vSetPinDir(LCD_CONTROL_PORT, LCD_RS_PIN, 1);
		
		
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RW_PIN, 0);
		LCD_vSendCmd(FOUR_BIT_MODE_I);
		LCD_vSendCmd(FOUR_BIT_MODE_II);
		LCD_vSendCmd(CLR_SCREEN);
		LCD_vSendCmd(DISPLAY_ON_SCREEN_ON);
		_delay_ms(10);
		
		
	#endif // _DEBUG
}
static void LCD_vSendFallingEdge(void){
	DIO_vWrite(LCD_CONTROL_PORT, LCD_EN_PIN, 1);
	_delay_ms(2);
	DIO_vWrite(LCD_CONTROL_PORT, LCD_EN_PIN, 0);
	_delay_ms(2);
}
void LCD_vSendCmd(uint8 cmd){
	#ifdef eight_bits_mode
		DIO_vWritePort(LCD_PORT, cmd);
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RS_PIN, 0);
		LCD_vSendFallingEdge();
	#elif defined(four_bit_mode)
		DIO_vClearHighNibble(LCD_PORT);
		DIO_vWriteHighNibble(LCD_PORT, cmd);
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RS_PIN, 0);
		LCD_vSendFallingEdge();
		DIO_vClearHighNibble(LCD_PORT);
		DIO_vWriteHighNibble(LCD_PORT, cmd<<4);
		DIO_vWrite(LCD_CONTROL_PORT,LCD_RS_PIN,0);
		LCD_vSendFallingEdge();
	#endif
}
void LCD_vSendChar(uint8 data){
	#ifdef eight_bits_mode
		DIO_vWritePort(LCD_PORT, data);
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RS_PIN, 1);
		LCD_vSendFallingEdge();
	#elif defined(four_bit_mode)
		DIO_vClearHighNibble(LCD_PORT);
		DIO_vWriteHighNibble(LCD_PORT, data);
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RS_PIN, 1);
		LCD_vSendFallingEdge();
		DIO_vClearHighNibble(LCD_PORT);
		DIO_vWriteHighNibble(LCD_PORT, data<<4);
		DIO_vWrite(LCD_CONTROL_PORT, LCD_RS_PIN, 1);
		LCD_vSendFallingEdge();
	#endif
}
void LCD_vSendString(char *data){
	while(*data != 0){
		LCD_vSendChar(*data);
		data++;
	}
}


void LCD_vClearScreen(void){
	LCD_vSendCmd(CLR_SCREEN);
}

void LCD_vMoveCursor(uint8 row, uint8 col){
	uint8 data;
	if(row>2 || row<1 || col>16 || col<1){
		data=0x80;
	}
	if(row == 1){
		data = 0x80+col-1;
	}
	if(row == 2){
		data = 0xc0+col-1;
	}
	LCD_vSendCmd(data);
}

