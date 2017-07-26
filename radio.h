/*
 * radio.h
 *
 * Created: 05.04.2017 22:34:45
 *  Author: Андрей
 */ 


#ifndef RADIO_H_
#define RADIO_H_

#define RADIO_TUNE_AUTO		0
#define RADIO_TUNE_MANUAL	1

typedef struct
{
	const uint16_t min;
	const uint16_t max;
} t_radioBand;

typedef struct
{
	const t_radioBand *Band;
	uint8_t TuneMode;
	uint16_t Frequency;
} t_Radio;

extern t_Radio Radio;

void Radio_Init(void);
void Radio_ChangeTuneMode(void);
void Radio_StepFrequency(int8_t diff);
void Radio_Seek(uint8_t direction);

#endif /* RADIO_H_ */