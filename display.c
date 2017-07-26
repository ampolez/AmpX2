/*
 * display.c
 *
 * Created: 18.03.2017 12:21:19
 *  Author: Андрей
 */ 

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "sound.h"
#include "radio.h"
#include "rtc.h"

const char STR_INPUT_AUX1[]				PROGMEM = "AUX1";
const char STR_INPUT_AUX2[]				PROGMEM = "AUX2";
const char STR_INPUT_AUX_BLUETOOTH[]	PROGMEM = "BLUETOOTH";
const char STR_INPUT_AUX_RADIO[]		PROGMEM = "RADIO";
PGM_P const InputLabels[] PROGMEM = {
	STR_INPUT_AUX1,
	STR_INPUT_AUX2,
	STR_INPUT_AUX_BLUETOOTH,
	STR_INPUT_AUX_RADIO
};

const char STR_SOUDPAR_VOL[]			PROGMEM = "VOLUME";
const char STR_SOUDPAR_BAL[]			PROGMEM = "BALANCE";
const char STR_SOUDPAR_BAS[]			PROGMEM = "BASS";
const char STR_SOUDPAR_MID[]			PROGMEM = "MIDDLE";
const char STR_SOUDPAR_TREB[]			PROGMEM = "TREBLE";
const char STR_SOUDPAR_GAIN[]			PROGMEM = "GAIN";
PGM_P const SoundParamLabels[] PROGMEM = {
	STR_SOUDPAR_VOL,
	STR_SOUDPAR_BAL,
	STR_SOUDPAR_BAS,
	STR_SOUDPAR_MID,
	STR_SOUDPAR_TREB,
	STR_SOUDPAR_GAIN
};

const char STR_RADIO_MONO[]				PROGMEM = " MONO";
const char STR_RADIO_STEREO[]			PROGMEM = "STEREO";
const char STR_RADIO_MUTE[]				PROGMEM = " MUTE";
const char STR_RADIO_UNMUTE[]			PROGMEM = "UNMUTE";
PGM_P const RadioModes[] PROGMEM = {	
	STR_RADIO_MONO,
	STR_RADIO_STEREO,
	STR_RADIO_MUTE,
	STR_RADIO_UNMUTE,
};

char strbuf[STR_BUFSIZE + 1];		

// Вывод на экран числа с единицами измерения
static void writeNum(int16_t number, uint8_t width, uint8_t lead, uint8_t radix, uint8_t x, uint8_t y, uint8_t inverse, char unit[STR_UNITSIZE])
{
	char buf[STR_BUFSIZE + 1];
	uint8_t numdiv;
	uint8_t sign = lead;
	int8_t i;

	if (number < 0) 
	{
		sign = '-';
		number = -number;
	}

	for (i = 0; i < width; i++)
	{
		buf[i] = lead;		
	}
	buf[width] = '\0';
	i = width - 1;

	while (number > 0 || i == width - 1)
	{
		numdiv = number % radix;
		buf[i] = numdiv + 0x30;
		if (numdiv >= 10)
		{
			buf[i] += 7;
		}

		i--;
		number /= radix;
	}

	if (i >= 0)
	{
		buf[i] = sign;
	}
	
	for(i = 0; i < STR_UNITSIZE; i++)
	{
		buf[width + i] = unit[i];
	}
	
	
	lcd_puts(buf, x, y, inverse);

	return;
}

// Включение экрана, настройка яркости и контраста по умолчанию
void Display_Init(void)
{
	//ST7565_normal_reverse(0);
	ST7565_init();
	ST7565_contrast(DISPLAY_CONTRAST);
	ST7565_volume(DISPLAY_BRIGHTNESS);
	ST7565_on_off(1);
	Display_Clear();
	
	return;
}

// Очистка экрана + прорисовка шапки для отображения входного канала
void Display_Clear(void)
{
	ST7565_FillRect(0,0,LCD_COLUMNS,LCD_ROWS, 0x00);	// Заполнение всего экрана (белым)
	ST7565_Rect(0,0,LCD_COLUMNS-1,LCD_ROWS-1);			// Рамка на весь экран (черная)
	ST7565_FillRect(0,0,LCD_COLUMNS-1,15, 0xff);		// Рамка в шапке (черная)
		
	return;
}

// Прорисовка текущего входного канала (в шапке)
void Display_DrawInputMode(uint8_t clear)
{
	const char *label = (const char *)pgm_read_word(&InputLabels[inputSelector.channel]);
	
	if(clear)
	{
		ST7565_Rect(0,0,LCD_COLUMNS,LCD_ROWS-1);
		ST7565_FillRect(0,0,LCD_COLUMNS-1,15, 0xff);		
	}
	strcpy_P(inputSelector.label, label);
	lcd_puts((char*)inputSelector.label, 6, 4, 1);
	
	return;
}

// Прорисовка настроек звука
void Display_DrawSoundParam(e_SoundEffect mode, uint8_t clear)
{
	int8_t val = sndParam[mode].value;
	int8_t min = (int8_t)pgm_read_byte(&sndParam[mode].grid->min);
	int8_t max = (int8_t)pgm_read_byte(&sndParam[mode].grid->max);

	strcpy_P(strbuf, (const char *)pgm_read_word(&SoundParamLabels[mode]));
	if(clear)
	{
		ST7565_FillRect(1,16,LCD_COLUMNS-2,LCD_ROWS-2, 0x00);		
	}	
	lcd_puts(strbuf, 25, 23, 0);
	writeNum(val, 3, ' ', 10, 70, 23, 0, "dB");
	//itoa ((int8_t)val,strbuf,2);
	//lcd_puts(strbuf, 10, 23, 0);

	Display_DrawSoundBar(min, max, val);
}

// Отображение горизонтальной шкалы регулировки
static void Display_DrawBar(int16_t min, int16_t max, int16_t value, uint8_t verticalCenter)
{
	uint8_t i, j;
	uint16_t mid = ((DISPLAY_PROGRESS_X2-DISPLAY_PROGRESS_X1)/2);

	if (min + max)
	{
		value = ((uint16_t)(DISPLAY_PROGRESS_X2) * (value - min) / (max - min)) + DISPLAY_PROGRESS_X1;
	}
	else
	{
		value = (int16_t)mid * value / max;
	}

	for (i = DISPLAY_PROGRESS_X1; i < DISPLAY_PROGRESS_X2; i++)
	{
		if (!(i & 0x01))
		{
			for (j = verticalCenter - 4; j < verticalCenter + 4; j++)
			{
				if (j == verticalCenter)
				{
					ST7565_SetPixel(i, j);
				}
				else
				{
					if ( ((min + max) && (value <= i)) || (!(min + max) &&
					(((value > DISPLAY_PROGRESS_X1) && ((i < mid) || (value + mid < i))) ||
					((value <= DISPLAY_PROGRESS_X1) && ((i > mid) || (value + mid > i))))))
					{
						ST7565_ClearPixel(i,j);
					}
					else
					{
						ST7565_SetPixel(i,j);
					}
				}
			}
		}
	}
	
	return;
}

// Прорисовка экрана регулировки звуковых параметров
void Display_DrawSoundBar(int16_t min, int16_t max, int16_t value)
{
	Display_DrawBar(min, max, value, 38);

	writeNum(min, 3, ' ', 10, 5, 47, 0, "dB");
	writeNum(max, 3, ' ', 10, 95, 47, 0, "dB");

	return;
}

// Прорисовка текущего времени
void Display_DrawClock(void)
{
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;

	int8_t ti;
	uint8_t tf;
		
	rtc_get_time_s(&hour, &minute, &second);
	sprintf(strbuf, "%2.2d:%2.2d", hour, minute);
	lcd_puts(strbuf,74,4,1);
	
	ds3231_get_temp_int(&ti, &tf);
	
	lcd_puts("°",116,4,1);	
	sprintf(strbuf, "%d", ti);
	lcd_puts(strbuf,109,4,1);
		
	return;
}

// Прорисовка экрана радиоприемника
void Display_DrawRadio(void)
{	
	char *_tuneMode;

/*	char *_stereo;*/
// 	if(Radio_IsStereo())
// 	{
// 		_stereo = "STEREO";
// 	}
// 	else
// 	{
// 		_stereo = " MONO";
// 	}

	if(Radio.TuneMode == RADIO_TUNE_AUTO)
	{
		_tuneMode = "[A]";	
	}
	else
	{
		_tuneMode = "[M]";
	}
	
		
	lcd_puts(_tuneMode, 110, 24, 1);
	lcd_puts("[1]", 86, 24, 1);
	
	lcd_puts("FM", 6, 24, 1);	
	dtostrf((float)(Radio.Frequency * 0.1), 5, 1, strbuf);
	sprintf(strbuf, "%sMHz",strbuf);
	lcd_puts(strbuf, 23, 24, 1);
	
	Display_DrawBar((int16_t)pgm_read_word(&Radio.Band->min), 
					(int16_t)pgm_read_word(&Radio.Band->max), 
					Radio.Frequency,
					41
					);	
	writeNum((int16_t)pgm_read_word(&Radio.Band->min)*0.1, 2, ' ', 10, 4, 52, 0, "MHz");
 	writeNum((int16_t)pgm_read_word(&Radio.Band->max)*0.1, 4, ' ', 10, 86, 52, 0, "MHz");	
}
