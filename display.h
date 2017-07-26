/*
 * display.h
 *
 * Created: 18.03.2017 12:21:31
 *  Author: Андрей
 */ 

#include "ST7565.h"
#include "input.h"
#include "sound.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define DISPLAY_CONTRAST	5
#define DISPLAY_BRIGHTNESS	35

#define DISPLAY_PROGRESS_X1	3
#define DISPLAY_PROGRESS_X2	LCD_COLUMNS-DISPLAY_PROGRESS_X1
#define STR_BUFSIZE			25		// Длина буфера для отображения строк на экране
#define STR_UNITSIZE		4		// Длина буфера для отображения единиц измерения

#define DISPLAY_TIME_SOUND_PARAMS 3000

void Display_Init(void);
void Display_Clear(void);
void Display_DrawInputMode(uint8_t clear);
void Display_DrawClock(void);
void Display_DrawSoundParam(e_SoundEffect mode, uint8_t clear);
void Display_DrawSoundBar(int16_t min, int16_t max, int16_t value);

void Display_DrawRadio(void);

#endif /* DISPLAY_H_ */