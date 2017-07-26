#ifndef TDA7439_H
#define TDA7439_H

/*#include <inttypes.h>*/

#define TDA7439_I2C_ADDR			0x44		// I2C address
#define TDA7439_AUTO_INC			0x10		// I2C autoincrement flag
#define TDA7439_IN_CNT				4			// Number of inputs

/* I2C function selection */
#define TDA7439_INPUT_SELECT		0x00
#define TDA7439_INPUT_GAIN			0x01
#define TDA7439_VOLUME				0x02
#define TDA7439_BASS				0x03
#define TDA7439_MIDDLE				0x04
#define TDA7439_TREBLE				0x05
#define TDA7439_SPEAKER_ATT_RIGHT	0x06
#define TDA7439_SPEAKER_ATT_LEFT	0x07

#define TDA7439_SPEAKER_MUTE		0b01111111

void TDA7439_SetVolume(void);					// Установка значения громкости
void TDA7439_SetSpeakers(void);					// Установка значения ослабления динамиков. Используется для баланса
void TDA7439_SetEqualizer(void);				// Установка значений эквалайзера
void TDA7439_SetGain(void);						// Установка значения усиления выходного канала
void TDA7439_SetInput(uint8_t channel);			// Установка текущего входного канала
void TDA7439_SetMute(void);						// Отключение зука выходного канала

#endif /* TDA7439_H */
