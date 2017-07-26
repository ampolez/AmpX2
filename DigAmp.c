/*****************************************************

*****************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "DigAmp.h"
#include "input.h"
#include "menu.h"
#include "display.h"
#include "twi.h"
#include "rtc.h"
#include "radio.h"

/*#include "tda7439.h"*/
/*#include "ST7565_LCD.h"*/

char strval[20];

int main(void)
{
	Display_Init();
	Input_Init();

	sei();

	I2C_Master_Init();
	_delay_ms(200);
	
	RTC_Init();
	Sound_Init();	
	Radio_Init();
	
	//rtc_set_time_s(12, 57, 0);

	uint8_t action;
	int8_t enc1, enc2;
			
	while (1)
	{	
		action = Action_ProcessButtons();		
		
		enc1 = Encoder_GetValue(ENC1);
		enc2 = Encoder_GetValue(ENC2);
		
		Action_ProcessEncoders(ENC1, enc1);
		Action_ProcessEncoders(ENC2, enc2);

		
		Action_Perform(action);
		

// 			sprintf(strval, "BR: %d B1: %d B2: %d", btn, ((btn>>BTN_ENC1_PIN) & 0x01), ((btn>>BTN_ENC2_PIN) & 0x01));
//  			lcd_puts("ABCde[A]{d}!naq",2,30,1);
//  			lcd_putchar('A',2,40,1);
/* 			lcd_putchar('A',20,41,1);*/

		
		Menu_CheckTimers();
		
		Menu_Change();
		
		Menu_ShowCurrent();	
	}
}
