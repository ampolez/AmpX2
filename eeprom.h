/*
 * eeprom.h
 *
 * Created: 05.04.2017 21:52:35
 *  Author: Андрей
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define EEPROM_SND_VOLUME			0x00
#define EEPROM_SND_BALANCE			0x01
#define EEPROM_SND_BASS				0x02
#define EEPROM_SND_MIDDLE			0x03
#define EEPROM_SND_TREBLE			0x04
#define EEPROM_SND_GAIN				0x05

#define EEPROM_AUDIO_CHANNEL		0x10

#define EEPROM_RADIO_BAND			0x20
#define EEPROM_RADIO_FM_FREQ		0x21
#define EEPROM_RADIO_AM_FREQ		0x22
#define EEPROM_RADIO_TUNE_MODE		0x23

#define EEPROM_RADIO_FM1			0x24
#define EEPROM_RADIO_FM2			0x25
#define EEPROM_RADIO_FM3			0x26
#define EEPROM_RADIO_FM4			0x27
#define EEPROM_RADIO_FM5			0x28
#define EEPROM_RADIO_FM6			0x29

#define EEPROM_RADIO_AM1			0x30
#define EEPROM_RADIO_AM2			0x31
#define EEPROM_RADIO_AM3			0x32
#define EEPROM_RADIO_AM4			0x33
#define EEPROM_RADIO_AM5			0x34
#define EEPROM_RADIO_AM6			0x35


#endif /* EEPROM_H_ */