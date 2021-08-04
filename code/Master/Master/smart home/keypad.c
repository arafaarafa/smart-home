/*
 * keypad.c
 *
 * Created: 5/25/2020 1:13:31 PM
 *  Author: Arafa
 */ 
#include "keypad.h"
void keypad_vInit(void){
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_FIRST_PIN,1);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_SECOND_PIN,1);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_THIRD_PIN,1);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_FOURTH_PIN,1);
	
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_FIFTH_PIN,0);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_SIXTH_PIN,0);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_SEVENTH_PIN,0);
	DIO_vSetPinDir(KEYPAD_PORT,KEYPAD_EIGHTH_PIN,0);
	
	DIO_vConnectPullUP(KEYPAD_PORT,KEYPAD_FIFTH_PIN,1);
	DIO_vConnectPullUP(KEYPAD_PORT,KEYPAD_SIXTH_PIN,1);
	DIO_vConnectPullUP(KEYPAD_PORT,KEYPAD_SEVENTH_PIN,1);
	DIO_vConnectPullUP(KEYPAD_PORT,KEYPAD_EIGHTH_PIN,1);
	
}
uint8 keypad_u8CheckPress(void){
	uint8 arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	uint8 key_pressed_indicator;
	uint8 returnvalue= NOT_PRESSED;

	
	
	for(uint8 row=0;row<4;row++){
			DIO_vWrite(KEYPAD_PORT,KEYPAD_FIRST_PIN,1);
			DIO_vWrite(KEYPAD_PORT,KEYPAD_SECOND_PIN,1);
			DIO_vWrite(KEYPAD_PORT,KEYPAD_THIRD_PIN,1);
			DIO_vWrite(KEYPAD_PORT,KEYPAD_FOURTH_PIN,1);
	_delay_ms(20);
	DIO_vWrite(KEYPAD_PORT,row,0);	
		for(uint8 column=0;column<4;column++){
			key_pressed_indicator= DIO_u8Read(KEYPAD_PORT,column+4);
			if(key_pressed_indicator==0){
				returnvalue = arr[row][column];
				break;
			}
		}
	}
	return returnvalue;
}
