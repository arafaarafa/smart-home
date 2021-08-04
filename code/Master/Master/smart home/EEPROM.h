/*
 * EEPROM.h
 *
 * Created: 5/24/2020 8:09:52 PM
 *  Author: Arafa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "STD_Types.h"
uint8 EEPROM_ui8ReadByteFromAddress(const uint16 u16Address);
void EEPROM_vWriteByteToAddress(const uint16 u16Address, const uint8 u8Data );
void EEPROM_vReadBlockFromAddress(const uint16 u16Address, uint8* dist, const uint16 size );
void EEPROM_vWriteBlockToAddress(const uint16 u16Address, const uint8* u8Date, const uint16 size);





#endif /* EEPROM_H_ */