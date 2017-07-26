/*
 * sound.h
 *
 * Created: 17.03.2017 16:21:04
 *  Author: Андрей
 */ 

#include <inttypes.h>

#ifndef SOUND_H_
#define SOUND_H_

/* Режимы настройки звука */
typedef enum 
{
	PARAM_SND_VOLUME = 0,
	PARAM_SND_BALANCE,
	PARAM_SND_BASS,
	PARAM_SND_MIDDLE,
	PARAM_SND_TREBLE,
	PARAM_SND_GAIN,

	PARAM_SND_END
} e_SoundEffect;

// Источники входного сигнала
typedef enum
{
	INPUT_AUX1 = 0,
	INPUT_AUX2,
	INPUT_BLUETOOTH,
	INPUT_RADIO,
	INPUT_END
} e_SoundInput;

typedef struct
{
	const int8_t min;
	const int8_t max;
	const int8_t step;
} t_SoundGrid;

typedef struct
{
	uint8_t channel;
	char label[20];
} t_SoundSelector;

typedef struct 
{
	int8_t value;
	const t_SoundGrid *grid;
} t_SoundParam;

extern t_SoundSelector inputSelector;
extern t_SoundParam sndParam[PARAM_SND_END];
extern e_SoundEffect curSoundParam;
extern e_SoundEffect prevSoundParam;

void Sound_Init(void);
void Sound_SetInput(uint8_t *inputChannel);
void Sound_NextParameter(e_SoundEffect *_sndParam);
void Sound_ChangeParam(e_SoundEffect *_sndParam, int8_t diff);

#endif /* SOUND_H_ */