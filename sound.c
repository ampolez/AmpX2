/*
 * sound.c
 *
 * Created: 17.03.2017 16:21:14
 *  Author: Андрей
 */ 

#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "sound.h"
#include "eeprom.h"
#include "tda7439.h"

static const t_SoundGrid grid_BMT		PROGMEM = { -7, 7, 2.00 * 8};
static const t_SoundGrid grid_Gain		PROGMEM = {0, 15, 2.00 * 8};
static const t_SoundGrid grid_Vol		PROGMEM = {-40, 0, 1.00 * 8};
static const t_SoundGrid grid_Bal		PROGMEM = {-15, 15, 1.00 * 8};

t_SoundParam sndParam[PARAM_SND_END];
t_SoundSelector inputSelector;
e_SoundEffect curSoundParam = PARAM_SND_VOLUME;
e_SoundEffect prevSoundParam = PARAM_SND_VOLUME;

// static const uint8_t tVol[]				PROGMEM = {0,1,2,3,4,5,6,7,8,16,24,32,40};
// static const uint8_t tGain[]			PROGMEM = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
// static const uint8_t tBMT[]				PROGMEM = {0,1,2,3,4,5,6,15,14,13,13,11,10,9,8};
// static const uint8_t tBal[]				PROGMEM = {0,1,2,3,4,5,6,7,8,16,24,32,48,56,64,72,120};
	
/*char strbuf[20];*/

void Sound_Init(void)
{
	uint8_t i = 0;
	
	sndParam[PARAM_SND_VOLUME].grid =	&grid_Vol;
	sndParam[PARAM_SND_BASS].grid =		&grid_BMT;
	sndParam[PARAM_SND_MIDDLE].grid =	&grid_BMT;
	sndParam[PARAM_SND_TREBLE].grid =	&grid_BMT;
	sndParam[PARAM_SND_GAIN].grid =		&grid_Gain;
	sndParam[PARAM_SND_BALANCE].grid =	&grid_Bal;

	// Восстанавливаем из памяти текущий входной канал
	inputSelector.channel = eeprom_read_byte((uint8_t*)EEPROM_AUDIO_CHANNEL);
	TDA7439_SetInput(inputSelector.channel);
	
	// Восстанавливаем из памяти настройки звука
	for(i = 0; i < PARAM_SND_END; i++)
	{
		sndParam[PARAM_SND_VOLUME + i].value = eeprom_read_byte((uint8_t*)EEPROM_SND_VOLUME + i);
	}	

	TDA7439_SetGain();
	TDA7439_SetVolume();
	TDA7439_SetSpeakers();
	TDA7439_SetEqualizer();
}

void Sound_SetInput(uint8_t *inputChannel)
{	
	(*inputChannel)++;		
	if((*inputChannel) >= INPUT_END)	
	{
		(*inputChannel) = INPUT_AUX1;
	}
	
	eeprom_update_byte((uint8_t*)EEPROM_AUDIO_CHANNEL, *inputChannel);
	inputSelector.channel = (*inputChannel);
	TDA7439_SetInput(inputSelector.channel);
}

void Sound_NextParameter(e_SoundEffect *_sndParamNumber)
{	
	(*_sndParamNumber)++;

	if ((*_sndParamNumber) >= PARAM_SND_END)
	{
		(*_sndParamNumber) = PARAM_SND_VOLUME;			
	}		
	eeprom_update_byte((uint8_t*)EEPROM_SND_VOLUME + (*_sndParamNumber), sndParam[(*_sndParamNumber)].value);

	return;
}

void Sound_ChangeParam(e_SoundEffect *_sndParam, int8_t diff)
{
	t_SoundParam param = sndParam[(*_sndParam)];
		
	if(diff != 0)
	{				
		param.value += diff;
		if (param.value > (int8_t)pgm_read_byte(&param.grid->max))
			param.value = (int8_t)pgm_read_byte(&param.grid->max);
		if (param.value < (int8_t)pgm_read_byte(&param.grid->min))
			param.value = (int8_t)pgm_read_byte(&param.grid->min);
		sndParam[(*_sndParam)] = param;

		TDA7439_SetGain();
		TDA7439_SetVolume();
		TDA7439_SetSpeakers();
		TDA7439_SetEqualizer();		
	}
	
	return;
}
