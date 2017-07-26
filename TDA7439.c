#include <avr/pgmspace.h>
#include "tda7439.h"
#include "twi.h"
#include "sound.h"

// Отключение зука выходного канала
void TDA7439_SetMute(void)
{
	I2C_Start(TDA7439_I2C_ADDR);
	//twi_send_byte(TDA7439_SPEAKER_ATT_RIGHT | TDA7439_AUTO_INC);
	I2C_SendByte(TDA7439_VOLUME);
	I2C_SendByte(TDA7439_SPEAKER_MUTE);
	I2C_End();
	return;
}

// Установка значения громкости
void TDA7439_SetVolume(void)
{
	if(-sndParam[PARAM_SND_VOLUME].value <= (int8_t)pgm_read_byte(&sndParam[PARAM_SND_VOLUME].grid->min))
	{
		TDA7439_SetMute();
	}
	else
	{
		I2C_Start(TDA7439_I2C_ADDR);
		I2C_SendByte(TDA7439_VOLUME);
		I2C_SendByte(-sndParam[PARAM_SND_VOLUME].value);
		I2C_End();		
	}

	return;
}

// Установка значения ослабления динамиков. Используется для баланса
void TDA7439_SetSpeakers(void)
{
	int8_t spLeft = sndParam[PARAM_SND_VOLUME].value;
	int8_t spRight = sndParam[PARAM_SND_VOLUME].value;
	int8_t volMin = pgm_read_byte(&sndParam[PARAM_SND_VOLUME].grid->min);
	
	if (sndParam[PARAM_SND_BALANCE].value > 0)
	{
		spLeft -= sndParam[PARAM_SND_BALANCE].value;
		if (spLeft < volMin)
		{
			spLeft = volMin;
		}
	} 
	else 
	{
		spRight += sndParam[PARAM_SND_BALANCE].value;
		if (spRight < volMin)
		{
			spRight = volMin;	
		}
	}

	I2C_Start(TDA7439_I2C_ADDR);
	I2C_SendByte(TDA7439_SPEAKER_ATT_RIGHT | TDA7439_AUTO_INC);
	I2C_SendByte(-spRight);
	I2C_SendByte(-spLeft);
	I2C_End();		


	return;
}

// Установка значений эквалайзера
void TDA7439_SetEqualizer(void)
{
	int8_t val;
	uint8_t mode;

	I2C_Start(TDA7439_I2C_ADDR);
	I2C_SendByte(TDA7439_BASS | TDA7439_AUTO_INC);
	for (mode = PARAM_SND_BASS; mode <= PARAM_SND_TREBLE; mode++) 
	{
		val = sndParam[mode].value;
		I2C_SendByte(val > 0 ? 15 - val : 7 + val);
	}
	I2C_End();

	return;
}

// Установка значения усиления выходного канала
void TDA7439_SetGain(void)
{
	I2C_Start(TDA7439_I2C_ADDR);
	I2C_SendByte(TDA7439_INPUT_GAIN);
	I2C_SendByte(sndParam[PARAM_SND_GAIN].value);
	I2C_End();

	return;
}

// Установка текущего входного канала
void TDA7439_SetInput(uint8_t channel)
{
	I2C_Start(TDA7439_I2C_ADDR);
	I2C_SendByte(TDA7439_INPUT_SELECT | TDA7439_AUTO_INC);
	I2C_SendByte(TDA7439_IN_CNT - 1 - channel);
	I2C_End();
	return;
}