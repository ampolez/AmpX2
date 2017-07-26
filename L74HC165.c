#include <avr/io.h>
#include <util/delay.h>

#include "l74hc165.h"

void L74HC165_Init(void) 
{
	L74HC165_DDR |= (1 << L74HC165_CLOCKPIN);
	L74HC165_DDR |= (1 << L74HC165_LOADPIN);
	L74HC165_DDR &= ~(1 << L74HC165_DATAPIN);
	L74HC165_PORT &= ~(1 << L74HC165_CLOCKPIN);
	L74HC165_PORT &= ~(1 << L74HC165_LOADPIN);

	return;
}

uint8_t L74HC165_ShiftIn(void) 
{
	uint8_t currentbyte = 0;
	
	L74HC165_PORT &= ~(1 << L74HC165_LOADPIN);
	//_delay_us(5);
	L74HC165_PORT |= (1 << L74HC165_LOADPIN);
	
	for(uint8_t j = 0; j < 8; j++)
	{
		currentbyte |= ((L74HC165_PIN & (1 << L74HC165_DATAPIN))>>L74HC165_DATAPIN)<<(7-j);
		L74HC165_PORT |= (1 << L74HC165_CLOCKPIN);
		//_delay_us(5);
		L74HC165_PORT &= ~(1 << L74HC165_CLOCKPIN);
	}

	return currentbyte;
}
