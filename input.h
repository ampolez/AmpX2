/*
 * input.h
 *
 * Created: 17.03.2017 12:41:57
 *  Author: Андрей
 */ 
#include <inttypes.h>

#ifndef INPUT_H_
#define INPUT_H_

#define TR(x, y, z) (((x) << 4) | ((y) << 2) | (z) )

#define ENC_DDR_REG DDRD
#define ENC_PORT_REG PORTD
#define ENC_PIN_REG PIND

#define ENC_STEP_ACTION 0		// Число тиков энкодера для фиксации значения (0 - мгновенно)
#define ENC1_PIN1 7
#define ENC1_PIN2 6
#define ENC2_PIN1 5
#define ENC2_PIN2 4

// Биты (0-7), соответствующие кнопкам, подключенным к регистру HC165
#define BTN_ENC1_PIN 1		// Вход A (нога 11)
#define BTN_ENC2_PIN 0		// Вход B (Нога 12)

#define SHORT_PRESS	50			// in ms
#define LONG_PRESS	600			// in ms

#define STATE_BTN_NULL		1
#define STATE_BTN_ENC1		2
#define STATE_BTN_ENC2		3

// Все возможные варианты команд управления
typedef enum {
	ENC1,			// Вращение энкодера 1
	ENC2,			// Вращение энкодера 2

	ENC1_BTN_SHORT,		// Короткое нажатие кнопки энкодера 1
	ENC2_BTN_SHORT,		// Короткое нажатие кнопки энкодера 2
	ENC1_BTN_LONG,		// Длинное нажатие кнопки энкодера 1
	ENC2_BTN_LONG,		// Длинное нажатие кнопки энкодера 2

	CMD_END			// Пустышка
} cmdID;

void Input_Init(void);

cmdID Buttons_GetState(void);
int8_t Encoder_GetValue(cmdID _encIndex);

void Timer_SetDisplayTime(uint16_t value);
uint16_t Timer_GetDisplayTime(void);

#endif /* INPUT_H_ */
