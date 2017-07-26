/*
 * input.c
 *
 * Created: 17.03.2017 12:46:06
 *  Author: Андрей
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "input.h"
#include "l74hc165.h"

volatile int8_t enc_value[2];	
volatile uint8_t encoder_state[2];

static volatile int8_t encRes = ENC_STEP_ACTION;				// Число щелчков энкодера перед срабатыванием
static volatile uint8_t btnPrev = STATE_BTN_NULL;	// Предыдущая нажатая кнопка
static volatile uint16_t displayTime;				// Время отображения текущей страницы на дисплее
static volatile uint16_t secTimer;					// Таймер на одну секунду
static volatile cmdID cmdBuf = CMD_END;				// Буфер текущей команды

//char str[20];

// Настройка портов и таймеров
void Input_Init(void)
{
	// Настройка энкодеров
	ENC_DDR_REG	&= ~(1<<ENC1_PIN1 | 1<<ENC1_PIN2 | 1<<ENC2_PIN1 | 1<<ENC2_PIN2);			// Пины на вход
	ENC_PORT_REG |= (1<<ENC1_PIN1 | 1<<ENC1_PIN2 | 1<<ENC2_PIN1 | 1<<ENC2_PIN2);			// Подтягивающие резисторы
	
	// Предделитель 128 (125 кГц), сброс по совпадению
	TCCR2B = (1<<CS22) | (0<<CS21) | (1<<CS20);
	TCCR2A = (1<<WGM21);
	OCR2A = 125;						// 125000/125 => 1000 тиков/сек
	TIMSK2 |= (1<<OCIE2A);				// Прерывание по совпадению 

	cmdBuf = CMD_END;
}

// Опрос энкодера с индексом _encIndex
void Input_EncoderRead(cmdID _encIndex)
{
	// считываем состояние энкодера
	uint8_t pins = 0;
	//enc_value[_encIndex] = 0;
	
	if(_encIndex == ENC1)
	{
		pins = ((ENC_PIN_REG) >> ENC1_PIN2) & 0x03;
	} else if(_encIndex == ENC2)
	{
		pins = ((ENC_PIN_REG) >> ENC2_PIN2) & 0x03;
	}

	// если не изменилось с предыдущего вызова, ничего не делаем
	if ((encoder_state[_encIndex] & 3) == pins )
	{
		return;
	}
	
	// задвигаем новое состояние в переменную, забывая самое старое из 3 сохраненных состояний
	encoder_state[_encIndex] = ((encoder_state[_encIndex] << 2) | pins) & 0x3F;


	// проверяем условия, и изменяем количество щелчков, если нужно
	if (encoder_state[_encIndex] == TR(3, 1, 0) || encoder_state[_encIndex] == TR(0,2,3))
	{
		enc_value[_encIndex]--;
	}
	if (encoder_state[_encIndex] == TR(0, 1, 3) || encoder_state[_encIndex] == TR(3,2,0))
	{
		enc_value[_encIndex]++;
	}
}
// Возвращает значение энкодера с индексом _encIndex
// Возможные значения: -1 0 +1 - соответственно CCW 0 CW
int8_t Encoder_GetValue(cmdID _encIndex)
{
	int8_t ret = 0;

	if (encRes) {
		if (encRes > 0) 
		{
			while (enc_value[_encIndex] >= encRes) {
				ret++;
				enc_value[_encIndex] -= encRes;
			}
			while (enc_value[_encIndex] <= -encRes) {
				ret--;
				enc_value[_encIndex] += encRes;
			}
		} else {
			while (enc_value[_encIndex] <= encRes) {
				ret++;
				enc_value[_encIndex] -= encRes;
			}
			while (enc_value[_encIndex] >= -encRes) {
				ret--;
				enc_value[_encIndex] += encRes;
			}
		}
	} else {
		ret = enc_value[_encIndex];
		enc_value[_encIndex] = 0;
	}

	return ret;
}

// Прерывание пой таймеру 10мс - опрос кнопок, энкодеров, обновление счетчиков секунд
ISR (TIMER2_COMPA_vect)
{
	static int16_t btnCnt = 0;				// Длительность нажатия на кнопку
	uint8_t btnNow = STATE_BTN_NULL;		// Текущая нажатая кнопка
	uint8_t buttons = 0;					// Байт значений кнопок, получаемый от HC165
		
	L74HC165_Init();
	buttons = L74HC165_ShiftIn();
	
	if ((buttons>>BTN_ENC1_PIN) & 0x01)
	{
		btnNow = STATE_BTN_ENC1;
	}
	
	if ((buttons>>BTN_ENC2_PIN) & 0x01)
	{
		btnNow = STATE_BTN_ENC2;
	}

	buttons = 0;

	Input_EncoderRead(ENC1);
	Input_EncoderRead(ENC2);

	if (btnNow) 
	{
		if (btnNow == btnPrev) 
		{
			btnCnt++;
			if (btnCnt == LONG_PRESS) 
			{
				switch (btnPrev) 
				{
					case STATE_BTN_ENC1:
						cmdBuf = ENC1_BTN_LONG;
						break;
					
					case STATE_BTN_ENC2:
						cmdBuf = ENC2_BTN_LONG;
						break;
				}
			} 
			else 
			{
				btnPrev = btnNow;
			}
		} 
		else 
		{
			if ((btnCnt > SHORT_PRESS) && (btnCnt < LONG_PRESS))
			{
				switch (btnPrev)
				{
					case STATE_BTN_ENC1:
						cmdBuf = ENC1_BTN_SHORT;
						break;
					
					case STATE_BTN_ENC2:
						cmdBuf = ENC2_BTN_SHORT;
						break;
				}
			}
			btnCnt = 0;
		}
		btnPrev = btnNow;
	}

	// Таймер отображения текущей страницы на дисплее
	if (displayTime)
	{
		displayTime--;		
	}
	
	// Секундный таймер
	if (secTimer) 
	{
		secTimer--;
	} else 
	{
		secTimer = 1000;
	}

	return;
}

// Установка таймера отображения текущего состояния экрана
void Timer_SetDisplayTime(uint16_t value)
{
	displayTime = value;

	return;
}

// Получение значения таймера отображения текущего экрана
uint16_t Timer_GetDisplayTime(void)
{
	return displayTime;
}

// Получение состояния кнопок
cmdID Buttons_GetState(void)
{
	cmdID ret = cmdBuf;
	cmdBuf = CMD_END;
	return ret;
}
