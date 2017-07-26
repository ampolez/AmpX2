#include <avr/io.h>

#ifndef L74HC165_H_
#define L74HC165_H_

#define L74HC165_DDR DDRD
#define L74HC165_PORT PORTD
#define L74HC165_PIN PIND

#define L74HC165_DATAPIN 1	// ����� OUT (Q7 pin #9)
#define L74HC165_CLOCKPIN 3	// ���������� CLOCK INPUT (CP pin #2)
#define L74HC165_LOADPIN 2	// ��������� LOAD (PL pin #1)

extern void L74HC165_Init(void);
extern uint8_t L74HC165_ShiftIn(void);

#endif
