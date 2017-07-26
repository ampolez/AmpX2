/*
 * menu.c
 *
 * Created: 17.03.2017 16:48:04
 *  Author: Андрей
 */ 

#include <inttypes.h>
#include <util/delay.h>
#include "menu.h"
#include "display.h"
#include "radio.h"
/*#include "tda7439.h"*/
/*#include "ST7565_LCD.h"*/
/*#include <stdio.h>*/

static uint8_t displayMode = MODE_STANDBY;
static uint8_t displayModePrev = MODE_STANDBY;

static uint8_t clearGlobal = 0;



/*char strbuf[20];*/ 

// Получение текущего режима отображения
uint8_t Menu_GetDispayMode(void)
{
	uint8_t mode = MODE_STANDBY;
	
	if(inputSelector.channel == INPUT_RADIO)
	{
		mode = MODE_FM_RADIO;
	}
	else if (inputSelector.channel == INPUT_BLUETOOTH)
	{
		mode = MODE_BLUETOOTH;
	}
	
	return mode;
}

// Обработка нажатий на кнопки (включая кнопки энкодеров)
uint8_t Action_ProcessButtons(void)
{
	uint8_t action = ACTION_NOACTION;
	cmdID cmd;
 
	/* Определение текущей комманды */
	cmd = Buttons_GetState();
	switch(cmd)
	{
		case ENC1_BTN_SHORT:
			action = ACTION_NEXT_SOUND_PARAM;			
			break;

		case ENC1_BTN_LONG:
			action = ACTION_NEXT_INPUT;
			break;
		
		case ENC2_BTN_SHORT:
			break;
				
		case ENC2_BTN_LONG:
			if(displayMode == MODE_FM_RADIO)
			{
				action = ACTION_SWITCH_TUNE_MODE;
			}
			break;

		default:
			break;

	}	
	return action;
}

// Выполнение функций и обработка событий
void Action_Perform(uint8_t action)
{
	switch (action) 
	{
		case ACTION_NEXT_SOUND_PARAM:
			Sound_NextParameter(&curSoundParam);			
			Timer_SetDisplayTime(DISPLAY_TIME_SOUND_PARAMS);
			displayMode = MODE_SOUND_PARAMS;
			break;
		
		case ACTION_NEXT_INPUT:			
			Sound_SetInput(&inputSelector.channel);	
			clearGlobal = 1;
			displayMode = MODE_STANDBY;
			break;
			
		case ACTION_SWITCH_TUNE_MODE:
			Radio_ChangeTuneMode();
			break;

		case ACTION_NOACTION:
		default:
			break;
	}		
}

// Обработка действий при вращении энкодеров
void Action_ProcessEncoders(cmdID _encIndex, int8_t encVal)
{	
	if(encVal != 0)
	{
		//ST7565_FillRect(2, 35, LCD_COLUMNS-2, 43, 0x00);					// Очистка
		
		// Энкодер №1 - Левый. Во всех режимах 
		// Вращение регулирует значение параметры звука. 
		if(_encIndex == ENC1)
		{
			switch(displayMode)	
			{
				case MODE_STANDBY:
				case MODE_FM_RADIO:
				case MODE_BLUETOOTH:
					curSoundParam = PARAM_SND_VOLUME;
					displayMode = MODE_SOUND_PARAMS;
					break;
				case MODE_SOUND_PARAMS:
				default:
					break;
			}
			//displayMode = MODE_SOUND_PARAMS;
			Sound_ChangeParam(&curSoundParam, encVal);			
			Timer_SetDisplayTime(DISPLAY_TIME_SOUND_PARAMS);
		}
		
		// Энкодер №2 - правый. Функция зависит от выбранного режима
		else if (_encIndex == ENC2)
		{
			switch(displayMode)
			{
				// В режиме радиоприемника этот энкодер служит для настройки частоты
				case MODE_FM_RADIO:

					// Ручная настройка частоты
					if(Radio.TuneMode == RADIO_TUNE_MANUAL)
					{
						Radio_StepFrequency(encVal);						
					}
					// Автоматический поиск станции
					else if (Radio.TuneMode == RADIO_TUNE_AUTO)
					{
						Radio_Seek(encVal);
					}
					break;
			}
		
		}
	}
	
	return;
}

// Перерисовка очистка меню, если режим изменился
void Menu_Change(void)
{
	if (displayMode != displayModePrev || clearGlobal == 1)
	{
		Display_Clear();
		clearGlobal = 0;	
	}

	return;
}

// Проверка таймеров отображения
void Menu_CheckTimers(void)
{
	if(Timer_GetDisplayTime() == 0)
	{
		//displayMode = MODE_STANDBY;
		displayMode = Menu_GetDispayMode();
		curSoundParam = PARAM_SND_VOLUME;
	}	
}

// Прорисовка экрана меню в соответствии с текущим режимом
void Menu_ShowCurrent(void)
{
	uint8_t clear = 0;

	if(displayMode == MODE_SOUND_PARAMS)
	{
		if(curSoundParam != prevSoundParam)
		{
			clear = 1;
		}
		Display_DrawSoundParam(curSoundParam, clear);
		prevSoundParam = curSoundParam;
	}
	
	if(displayMode == MODE_FM_RADIO)
	{
		Display_DrawRadio();
	}	
	//clear = 1;

	// Режим входа и часы отображаются всегда
	Display_DrawInputMode(clearGlobal);
	//Display_DrawClock();
	
	displayModePrev = displayMode;
	
	return;
}
