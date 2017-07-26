/*
 * menu.h
 *
 * Created: 16.03.2017 20:44:28
 *  Author: Андрей
 */ 

#ifndef MENU_H_
#define MENU_H_

#include "input.h"
#include "sound.h"

// Возможные функции и события
enum {
	ACTION_NEXT_SOUND_PARAM,
	ACTION_NEXT_INPUT,
	ACTION_SWITCH_TUNE_MODE,
	
	ACTION_NOACTION
};

// Возможные режимы работы
enum {
	MODE_STANDBY,
	MODE_INPUT_CHANGE,
	MODE_FM_RADIO,
	MODE_BLUETOOTH,
	MODE_TIME_EDIT,
	MODE_SOUND_PARAMS,

	MODE_END
};


uint8_t Action_ProcessButtons(void);
void Action_ProcessEncoders(cmdID _encIndex, int8_t encVal);

void Action_Perform(uint8_t action);
void Menu_Change(void);
void Menu_ShowCurrent(void);
void Menu_CheckTimers(void);
uint8_t Menu_GetDispayMode(void);

#endif /* MENU_H_ */