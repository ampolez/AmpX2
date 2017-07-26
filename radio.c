/*
 * radio.c
 *
 * Created: 05.04.2017 22:34:36
 *  Author: Андрей
 */ 

/*#include <util/delay.h>*/
/*#include <string.h>*/
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "radio.h"
#include "eeprom.h"
#include "RDA5807M.h"

t_Radio Radio;
static const t_radioBand FMBand		PROGMEM = {880, 1080};		// f/10 МГц

/*char strval[20];*/

void Radio_Init(void)
{	
	Radio.Band = &FMBand;
	Radio.Frequency = (uint16_t)880;
	Radio.TuneMode = eeprom_read_byte((uint8_t*)EEPROM_RADIO_TUNE_MODE);
	
	RDA5807_init();
	RDA5807_SetVolume(15);
	RDA5807_SetFreq(Radio.Frequency);
	
	return;	
}

void Radio_Seek(uint8_t direction)
{
	if(direction < 0)
	{
		//RDA5807_AutoSeek(0);
		RDA5807M_SeekDown(1);
	} else if (direction > 0)
	{
		//RDA5807_AutoSeek(1);		
		RDA5807M_SeekUp(1);
	}
	Radio.Frequency = RDA5807M_GetFrequency();
	
	return;
}

void Radio_StepFrequency(int8_t diff)
{
	if(diff)
	{
		uint16_t _freq = Radio.Frequency;

		_freq += (uint16_t)diff;


		if(_freq > (uint16_t)pgm_read_word(&Radio.Band->max))
		{
			_freq = (uint16_t)pgm_read_word(&Radio.Band->min);
		}

		if(_freq < (uint16_t)pgm_read_word(&Radio.Band->min))
		{
			_freq = (uint16_t)pgm_read_word(&Radio.Band->max);
		}
		
		RDA5807_SetFreq(_freq);
		Radio.Frequency = _freq;
	}

	return;
}

void Radio_ChangeTuneMode(void)
{
	Radio.TuneMode++;
	if(Radio.TuneMode > RADIO_TUNE_MANUAL)
	{
		Radio.TuneMode = RADIO_TUNE_AUTO;
	}	
	eeprom_update_byte((uint8_t*)EEPROM_RADIO_TUNE_MODE, Radio.TuneMode);
	
	return;
}