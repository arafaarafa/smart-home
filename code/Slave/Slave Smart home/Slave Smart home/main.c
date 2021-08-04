/*
 * Slave Smart home.c
 *
 * Created: 6/15/2020 9:29:28 PM
 * Author : Arafa
 */ 

#include <avr/io.h>
#include "SPI.h"
#include "LED.h"
#include "STD_types.h"
#include "STD_marcos.h"
#include "STD_messages.h"
#include "TIMER_driver.h"
#include "ADC_driver.h"
#include "APP_Slave.h"



volatile uint16 required_temperature = 24;
volatile uint16 temp_sensor_reading = 0;
volatile uint16 counter = 0;
volatile uint8 last_air_conditioning = AIR_CONDTIONING_OFF;
int main(void)
{
	ADC_vInit();
	TIMER0_vInitCTC();
	SPI_vInitSlave();
	
	
	
	
	LED_vInit(ROOM1_PORT, ROOM1_PIN);
	LED_vInit(ROOM2_PORT, ROOM2_PIN);
	LED_vInit(ROOM3_PORT, ROOM3_PIN);
	LED_vInit(ROOM4_PORT, ROOM4_PIN);
	LED_vInit(AIR_COND_PORT, AIR_COND_PIN);
	LED_vInit(TV_PORT, TV_PIN);
	
	uint8 request = DEFAULT_ACK;
	uint8 response = DEFAULT_ACK;
	
    /* Replace with your application code */
    while (1) 
    {
		request = SPI_u8TransmitRecive(DEFAULT_ACK);
		switch(request){
			case ROOM1_STATUS:
				if (LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==0)
				{
					response = OFF_STATUS;
				}else if(LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==1){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case ROOM2_STATUS:
				if (LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==0)
				{
					response = OFF_STATUS;
					}else if(LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==1){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case ROOM3_STATUS:
				if (LED_u8ReadStatus(ROOM3_PORT,ROOM3_PIN)==0)
				{
					response = OFF_STATUS;
					}else if(LED_u8ReadStatus(ROOM3_PORT,ROOM3_PIN)==0){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case ROOM4_STATUS:
				if (LED_u8ReadStatus(ROOM4_PORT,ROOM4_PIN)==0)
				{
					response = OFF_STATUS;
					}else if(LED_u8ReadStatus(ROOM4_PORT,ROOM4_PIN)==1){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case AIR_COND_STATUS:
				if (LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==0)
				{
					response = OFF_STATUS;
					}else if(LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==1){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case TV_STATUS:
				if (LED_u8ReadStatus(TV_PORT,TV_PIN)==0)
				{
					response = OFF_STATUS;
					}else if(LED_u8ReadStatus(TV_PORT,TV_PIN)==1){
					response = ON_STATUS;
				}
				SPI_u8TransmitRecive(response);
				break;
			case ROOM1_TURN_ON:
				LED_vTurnOn(ROOM1_PORT,ROOM1_PIN);
				break; 
			case ROOM2_TURN_ON:
				LED_vTurnOn(ROOM2_PORT,ROOM2_PIN);
				break;
			case ROOM3_TURN_ON:
				LED_vTurnOn(ROOM3_PORT,ROOM3_PIN);
				break;
			case ROOM4_TURN_ON:
				LED_vTurnOn(ROOM4_PORT,ROOM4_PIN);
				break;
			case AIR_COND_TURN_ON:
				TIMER0_vInitCTC();
				LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);
				break;
			case TV_TURN_ON:
				LED_vTurnOn(TV_PORT,TV_PIN);
				break;
			
			case ROOM1_TURN_OFF:
			LED_vTurnOff(ROOM1_PORT,ROOM1_PIN);
			break;
			case ROOM2_TURN_OFF:
			LED_vTurnOff(ROOM2_PORT,ROOM2_PIN);
			break;
			case ROOM3_TURN_OFF:
			LED_vTurnOff(ROOM3_PORT,ROOM3_PIN);
			break;
			case ROOM4_TURN_OFF:
			LED_vTurnOff(ROOM4_PORT,ROOM4_PIN);
			break;
			case AIR_COND_TURN_OFF:
			TIMER0_vStop();
			LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);
			break;
			case TV_TURN_OFF:
			LED_vTurnOff(TV_PORT,TV_PIN);
			break;
			
		}
    }
}

ISR(TIMER0_COMP_vect){
	counter++;
	if(counter>=10){
		counter = 0;
		temp_sensor_reading = (0.25*ADC_u16Read(0));
		if(temp_sensor_reading >= (required_temperature+1)){
			LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning = AIR_COND_TURN_ON;
		}else if(temp_sensor_reading <= (required_temperature-1)){
			LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning = AIR_COND_TURN_ON;
		}else if(temp_sensor_reading == required_temperature){
			if (last_air_conditioning == AIR_COND_TURN_ON)
			{
				LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);
			}else if(last_air_conditioning == AIR_COND_TURN_OFF){
				LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);
			}
		}
	}
}
