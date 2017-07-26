/*
 * helpers.c
 *
 * Created: 06.04.2017 1:08:41
 *  Author: Андрей
 */ 

#include "helpers.h"

void bitWrite(unsigned char *var, uint8_t bit, uint8_t value)
{
	if(value == 0)
	{
		CLEARBIT(*var, bit);
	} else if (value == 1)
	{
		SETBIT(*var, bit);
	}
}

uint16_t Make16Bit(uint8_t dataFirst, uint8_t dataSecond)
{
	uint16_t dataBoth = 0x0000;
	dataBoth = dataFirst;
	dataBoth = dataBoth << 8;
	dataBoth |= dataSecond;
	return dataBoth;
}