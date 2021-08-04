/*
 * keypad.h
 *
 * Created: 5/25/2020 1:13:16 PM
 *  Author: Arafa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"
#define NOT_PRESSED 0xff

void keypad_vInit(void);
uint8 keypad_u8CheckPress(void);






#endif /* KEYPAD_H_ */