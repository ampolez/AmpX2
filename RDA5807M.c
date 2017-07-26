/*
 * RDA5807M.c
 *
 * Created: 20.04.2017 16:58:44
 *  Author: Андрей
 */ 

#include "twi.h"
#include "RDA5807M.h"
#include "helpers.h"
#include <avr/pgmspace.h>

static uint8_t writeBuf[9];
const uint16_t RDA5807M_BandLowerLimits[5]	PROGMEM = { 8700, 7600, 7600, 6500, 5000 };
const uint16_t RDA5807M_BandHigherLimits[5] PROGMEM = { 10800, 9100, 10800, 7600, 6500 };
const uint8_t RDA5807M_ChannelSpacings[4]	PROGMEM = { 100, 200, 50, 25 };

// Запись всех регистров модуля по I2C
void RDA5807_write(void)
{
	I2C_Start(RDA5807_ADDRESS);
	for(uint8_t i = 0; i < 9; i++)
	{
		I2C_SendByte(writeBuf[i]);
	}
	I2C_End();
}

// инициализация, конфигурация
void RDA5807_init(void) 
{
 	writeBuf[0] = 0b11010010;		// 0x02 high
 	writeBuf[1] = 0b10001101;		// 0x02 low
 	writeBuf[2] = 0x00;				// 0x03 high
 	writeBuf[3] = 0x00;				// 0x03 low
	writeBuf[4] = 0b00000010;		// 0x04 high
	writeBuf[5] = 0x00;				// 0x04 low
	writeBuf[6] = 0b00001000;		// 0x05 high
	writeBuf[7] = 0b10001111;		// 0x05 low
	writeBuf[8] = 0x00;				// 0x06 high
	
	RDA5807_write();
	return;
}

// задать частоту радиостанции
// частота в формате 101.2 FM пишем как 1012 (например)
// шаг 0.1 МГц
void RDA5807_SetFreq(uint16_t freq) 
{
	uint16_t chan = (freq - 870);
	//uint16_t chan = (freq - RDA5807_FREQ_MIN) / RDA5807_CHAN_SPACING;

	writeBuf[2]  = chan >> 2;					// смаргшие 8 бит
	writeBuf[3] |= (chan << 6) | RDA5807_TUNE;

	RDA5807_write();
	return;
}

// Задать уровень громкости (значение от 0 до 15)
void RDA5807_SetVolume(uint8_t vol)
{
	writeBuf[7] |= vol;
	RDA5807_write();
}

void RDA5807M_SeekUp(uint8_t wrap) 
{
	RDA5807M_UpdateRegister(RDA5807M_REG_CONFIG,
							(RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK |	RDA5807M_FLG_SKMODE),
							(RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK | (wrap ? 0x00 : RDA5807M_FLG_SKMODE))
						   );
};

void RDA5807M_SeekDown(uint8_t wrap) 
{
	RDA5807M_UpdateRegister(RDA5807M_REG_CONFIG,
							(RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK | RDA5807M_FLG_SKMODE),
							(0x00 | RDA5807M_FLG_SEEK |	(wrap ? 0x00 : RDA5807M_FLG_SKMODE))
						    );
};

uint16_t RDA5807M_GetRegister(uint8_t reg) 
{
	uint16_t result;

	I2C_Start(RDA5807_ADDRESS);
	I2C_SendByte(reg);
	I2C_End();
	I2C_RequestFrom(RDA5807_ADDRESS, 2);
	
	//Don't let gcc play games on us, enforce order of execution.
	result = (uint16_t)I2C_Receive() << 8;
	result |= I2C_Receive();

	return result;
};

void RDA5807M_SetRegister(uint8_t reg, const uint16_t value) 
{
	I2C_Start(RDA5807_ADDRESS);
	I2C_SendByte(reg);
	I2C_SendByte(highByte(value));
	I2C_SendByte(lowByte(value));
	I2C_End();
};

void RDA5807M_UpdateRegister(uint8_t reg, uint16_t mask, uint16_t value) 
{
	RDA5807M_SetRegister(reg, RDA5807M_GetRegister(reg) & (~mask | value));
};


uint16_t RDA5807M_GetBandAndSpacing(void) 
{
	uint8_t band = RDA5807M_GetRegister(RDA5807M_REG_TUNING) & (RDA5807M_BAND_MASK | RDA5807M_SPACE_MASK);	
	const uint8_t space = band & RDA5807M_SPACE_MASK;		//Separate channel spacing

	if (band && RDA5807M_BAND_MASK == RDA5807M_BAND_EAST && !(RDA5807M_GetRegister(RDA5807M_REG_BLEND) & RDA5807M_FLG_EASTBAND65M))
	{
		//Lower band limit is 50MHz
		band = (band >> RDA5807M_BAND_SHIFT) + 1;		
	}
	else
	{
		band >>= RDA5807M_BAND_SHIFT;				
	}

	return Make16Bit(space, band);
};

uint16_t RDA5807M_GetFrequency(void) 
{
	const uint16_t spaceandband = RDA5807M_GetBandAndSpacing();

	return pgm_read_word(&RDA5807M_BandLowerLimits[lowByte(spaceandband)]) + 
						(RDA5807M_GetRegister(RDA5807M_REG_STATUS) & RDA5807M_READCHAN_MASK) *	
						pgm_read_byte(&RDA5807M_ChannelSpacings[highByte(spaceandband)]) / 10;
};

// запустить автопоиск (вверх = 1, вниз = 0)
void RDA5807_AutoSeek(uint8_t d)
{
	writeBuf[0] |= (d<<1)|(1<<0);
	RDA5807_write();
}