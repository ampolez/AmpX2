﻿/*
 * RDA5807M.h
 *
 * Created: 20.04.2017 16:58:58
 *  Author: Андрей
 */ 


#ifndef RDA5807M_H_
#define RDA5807M_H_

// Адрес чипа RDA5807M
#define RDA5807_ADDRESS				0x10		// RDASequential
//#define RDA5807_ADDRESS				0x11		// RDARandom
//#define RDA5807_ADDRESS				0x60		// TEA5767Mode

// Регистры для записи данных (настроек)

/* 0 register (02H) */
#define RDA5807_DHIZ				(1<<7) /* Audio out enable (1) / High impedance (0)*/
#define RDA5807_DMUTE				(1<<6) /* Audio unmuted (1) / muted (0) */
#define RDA5807_MONO				(1<<5) /* Mono mode (1) / stereo mode (0) */
#define RDA5807_BASS				(1<<4) /* Bass boost (1) */
#define RDA5807_RCLK_NON_CAL_MODE	(1<<3) /* RCLK always on (0) */
#define RDA5807_RCLK_DIR_IN_MODE	(1<<2) /* RCLK direct input mode (1) */
#define RDA5807_SEEKUP				(1<<1) /* Seek up (0) / down (1) */
#define RDA5807_SEEK				(1<<0) /* Stop seek (0) / start seek in SEEKUP direction (1) */

/* 1 register (02L) */
#define RDA5807_SKMODE				(1<<7) /* Stop seeking on band limit (1) */
#define RDA5807_CLK_MODE_32768		(0<<4) /* Select quartz frequency */
#define RDA5807_CLK_MODE_12M		(1<<4)
#define RDA5807_CLK_MODE_24M		(5<<4)
#define RDA5807_CLK_MODE_13M		(2<<4)
#define RDA5807_CLK_MODE_26M		(6<<4)
#define RDA5807_CLK_MODE_19M2		(3<<4)
#define RDA5807_CLK_MODE_38M4		(7<<4)
#define RDA5807_RDS_EN				(1<<3) /* RDS/RBDS enable (1) */
#define RDA5807_NEW_METHOD			(1<<2) /* New demodulation method (1) */
#define RDA5807_SOFT_RESET			(1<<1) /* Reset settings (1) */
#define RDA5807_ENABLE				(1<<0) /* Power on radio (1) */

/* 2 register (03H) */
/* CHAN 9..2 bits */
/*
 * BAND = 0    => Freq = Channel spacing (kHz) * CHAN + 87.0MHz
 * BAND = 1,2  => Freq = Channel spacing (kHz) * CHAN + 76.0MHz
 * BAND = 3    => Freq = Channel spacing (kHz) * CHAN + 65.0MHz
*/

/* 3 register (03L) */
/* CHAN 1.. 0 bits */
#define RDA5807_DIRECT_MODE			(1<<5) /* Direct mode (1), only used when test */
#define RDA5807_TUNE				(1<<4) /* Tune enable (1) */
#define RDA5807_BAND_US_EUROPE		(0<<2) /* 87..108 MHz */
#define RDA5807_BAND_JAPAN			(1<<2) /* 76..97 MHz */
#define RDA5807_BAND_WORLDWIDE		(2<<2) /* 76..108 MHz */
#define RDA5807_BAND_EASTEUROPE		(3<<2) /* 65..76 MHz */
#define RDA5807_SPACE_100			(0<<0) /* 100kHz step */
#define RDA5807_SPACE_200			(1<<0) /* 200kHz step */
#define RDA5807_SPACE_50			(2<<0) /* 50kHz step */
#define RDA5807_SPACE_25			(3<<0) /* 25kHz step */

/* 4 register (04H) */
#define RDA5807_DE					(1<<3) /* De-emphasis 75us (0) / 50us (1) */
#define RDA5807_SOFTMUTE_EN			(1<<1) /* Softmute enable (1) 0 - disable*/
#define RDA5807_AFCD				(1<<0) /* AFC disable (1) */

/* 5 register (04L) */
/* Unused on RDA5807M, used on RDA5807FP for GPIO/I2S control */

/* 6 register (05H) */
#define RDA5807_INT_MODE			(1<<7) /* 5ms interrupt for RDSIEN on RDS ready (0) */
#define RDA5807_SEEKTH				0x0F   /* Seek SNR threshold, 4bits, default 1000=32dB */

/* 7 register (05L) */
#define RDA5807_LNA_PORT_SEL		(2<<6) /* Only for RDA5807FP 2 bit (10) to select FMIN input */
#define RDA5807_VOLUME				0x0F   /* 4 bits volume (0000 - muted, 1111 - max) */

/* 8 register (06H) */
#define RDA5807_OPEN_MODE			0x60   /* 2 bits (11) to open read-only regs for writing */
/* Other bits for RDA5807FP, for I2S control */

/* 9 register (06L) */
/* It's for RDA5807FP, for I2S control */

/* 10 register (07H) */
#define RDA5807_TH_SOFRBLEND		0x7C   /* 5 bits for noise soft blend, default 10000 */
#define RDA5807_65M_50M_MODE		(1<<1) /* For BAND=11, 50..76MHz (0) */

/* 11 register (07L) */
#define RDA5807_TH_OLD				0xFC   /* 6 bits seek treshold, valid for SKMODE=1 */
#define RDA5807_SOFTBLEND_EN		(1<<1) /* Softblend enable (1) */
#define RDA5807_FREQ_MODE			(1<<0) /* Manual freq setup (1) for 12,13 regs */

/* 12,13 registers (08H,L) */
/* Manual frequency value. Freq = 76000(87000)kHz + value of 08 word */

// Регистры для чтения

/* 0 register (0AH) */
#define RDA5807_RDSR				(1<<7) /* RDS ready (1) */
#define RDA5807_STC					(1<<6) /* Seek/tune complete (1) */
#define RDA5807_SF					(1<<5) /* Seek failure (1) */
#define RDA5807_RDSS				(1<<4) /* RDS decoder synchronized (1) */
#define RDA5807_BLK_E				(1<<3) /* (When RDS enabled) block E has been found (1)*/
#define RDA5807_ST					(1<<2) /* Stereo indicator (1) */
/* READCHAN 9,8 bits */

/* 1 register (0AL) */
/* READCHAN 7-0 bits */

/* 2 register (0BH) */
#define RDA5807_RSSI				0xFE   /* 7 bits of RSSI signal level*/
#define RDA5807_FM_TRUE				(1<<0) /* Current channel is a station (1) */

/* 3 register (0BL) */
#define RDA5807_FM_READY			(1<<7) /* Ready */
#define RDA5807_ABCD_E				(1<<4) /* Data block E (1) or blocks A-D (0) */
#define RDA5807_BLERA				0x0C   /* 2 bits error level in block A(RDS) or E(RBDS) */
#define RDA5807_BLERB				0x03   /* 2 bits error level in block B(RDS) or E(RBDS) */

/* 4-11 registers */
/* RDS data registers:
 * 4-5   => A,
 * 6-7   => B,
 * 8-9   => C,
 * 10-11 => D,
 * or 4-11 => E when ABCD_E = 1
 */


//Register file origins for sequential mode
#define RDA5807M_FIRST_REGISTER_WRITE 0x02
#define RDA5807M_FIRST_REGISTER_READ 0x0A
#define RDA5807M_LAST_REGISTER 0x3A

//Register addresses
#define RDA5807M_REG_CHIPID 0x00
#define RDA5807M_REG_CONFIG 0x02
#define RDA5807M_REG_TUNING 0x03
#define RDA5807M_REG_GPIO 0x04
#define RDA5807M_REG_VOLUME 0x05
#define RDA5807M_REG_I2S 0x06
#define RDA5807M_REG_BLEND 0x07
#define RDA5807M_REG_FREQ 0x08
#define RDA5807M_REG_STATUS 0x0A
#define RDA5807M_REG_RSSI 0x0B
#define RDA5807M_REG_RDSA 0x0C
#define RDA5807M_REG_RDSB 0x0D
#define RDA5807M_REG_RDSC 0x0E
#define RDA5807M_REG_RDSD 0x0F
#define RDA5800_REG_LNA 0x10
#define RDA5807M_REG_SEEK 0x20

//Status bits (from the chip)
#define RDA5807M_STATUS_RDSR 0x8000
#define RDA5807M_STATUS_STC 0x4000
#define RDA5807M_STATUS_SF 0x2000
#define RDA5807M_STATUS_RDSS 0x1000
#define RDA5807M_STATUS_BLKE 0x0800
#define RDA5807M_STATUS_ST 0x0400
#define RDA5800_STATUS_ST 0x0100

//Flag bits (to the chip)
#define RDA5807M_FLG_DHIZ 0x8000
#define RDA5807M_FLG_DMUTE 0x4000
#define RDA5807M_FLG_MONO 0x2000
#define RDA5807M_FLG_BASS 0x1000
#define RDA5807M_FLG_RCLKNOCAL 0x0800
#define RDA5807M_FLG_RCLKDIRECT 0x0400
#define RDA5807M_FLG_SEEKUP 0x0200
#define RDA5807M_FLG_SEEK 0x0100
#define RDA5807M_FLG_SKMODE		(uint16_t)0x0080
#define RDA5807M_FLG_RDS		(uint16_t)0x0008
#define RDA5807M_FLG_NEW		(uint16_t)0x0004
#define RDA5807M_FLG_RESET		(uint16_t)0x0002
#define RDA5807M_FLG_ENABLE		(uint16_t)0x0001
#define RDA5807M_FLG_DIRECT		(uint16_t)0x0020
#define RDA5807M_FLG_TUNE		(uint16_t)0x0010
#define RDA5807M_FLG_DE						0x0800
#define RDA5807M_FLG_SOFTMUTE				0x0200
#define RDA5807M_FLG_AFCD					0x0100
#define RDA5807P_FLG_INTMODE				0x8000
#define RDA5807M_FLG_EASTBAND65M			0x0200
#define RDA5807M_FLG_SOFTBLEND	(uint16_t)0x0002
#define RDA5807M_FLG_FREQMODE	(uint16_t)0x0001
#define RDA5807M_FLG_FMTRUE					0x0100
#define RDA5807M_FLG_FMREADY	(uint16_t)0x0080
#define RDA5807M_FLG_BLOCKE		(uint16_t)0x0010
#define RDA5807P_FLG_STCIEN				  0x4000
#define RDA5807P_FLG_I2S		(uint16_t)0x0040
#define RDA5807P_FLG_I2SSLAVE				0x1000
#define RDA5807P_FLG_SWLR					0x0800
#define RDA5807P_FLG_SCLKINVERT_I			0x0400
#define RDA5807P_FLG_SIGNED					0x0200
#define RDA5807P_FLG_WSINVERT_I				0x0100
#define RDA5807P_FLG_WSINVERT_O		(uint16_t)0x0008
#define RDA5807P_FLG_SCLKINVERT_O	(uint16_t)0x0004
#define RDA5807P_FLG_DELAY_L		(uint16_t)0x0002
#define RDA5807P_FLG_DELAY_R		(uint16_t)0x0001
#define RDA5800_FLG_SPACE_200K		(uint16_t)0x0001
#define RDA5800_FLG_SPACE_50K		(uint16_t)0x0004
#define RDA5800_FLG_BAND_JAPAN		(uint16_t)0x0002

// Masks and constants for configuration parameters
// NOTE: the entire family, including the RDA5800, all report the same ChipID.
#define RDA5807M_CHIPID 0x58
#define RDA5807M_CLKMODE_MASK (uint16_t)(0x0070)
#define RDA5807M_CLKMODE_32K (0x0 << 4)
#define RDA5807M_CLKMODE_12M (0x1 << 4)
#define RDA5807M_CLKMODE_13M (0x2 << 4)
#define RDA5807M_CLKMODE_19M (0x3 << 4)
#define RDA5807M_CLKMODE_24M (0x5 << 4)
#define RDA5807M_CLKMODE_26M (0x6 << 4)
#define RDA5807M_CLKMODE_38M (0x7 << 4)
#define RDA5807M_CHAN_MASK 0xFFC0
#define RDA5807M_CHAN_SHIFT 6
#define RDA5807M_BAND_MASK (uint16_t)(0x000C)
#define RDA5807M_BAND_SHIFT 2
#define RDA5807M_BAND_WEST (0x0 << 2)
#define RDA5807M_BAND_JAPAN (0x1 << 2)
#define RDA5807M_BAND_WORLD (0x2 << 2)
#define RDA5807M_BAND_EAST (0x3 << 2)
#define RDA5807M_SPACE_MASK (uint16_t)(0x0003)
#define RDA5807M_SPACE_100K 0x0
#define RDA5807M_SPACE_200K 0x1
#define RDA5807M_SPACE_50K 0x2
#define RDA5807M_SPACE_25K 0x3
#define RDA5807M_SEEKTH_MASK 0x7F00
#define RDA5807M_SEEKTH_SHIFT 8
#define RDA5807M_VOLUME_MASK (uint16_t)(0x000F)
#define RDA5807M_VOLUME_SHIFT 0
#define RDA5807M_OPENMODE_MASK (uint16_t)(0x6000)
#define RDA5807M_OPENMODE_WRITE (0x3 << 13)
#define RDA5807M_SOFTBLENDTH_MASK 0x7C00
#define RDA5807M_SOFTBLENDTH_SHIFT 10
#define RDA5807M_SEEKTHOLD_MASK (uint16_t)(0x00FC)
#define RDA5807M_SEEKTHOLD_SHIFT 2
#define RDA5807M_SEEKMODE_MASK 0x7000
#define RDA5807M_SEEKMODE_OLD (0x1 << 12)
#define RDA5807M_READCHAN_MASK 0x03FF
#define RDA5807M_RSSI_MASK 0xFE00
#define RDA5807M_RSSI_SHIFT 9
#define RDA5807M_BLERA_MASK (uint16_t)(0x000C)
#define RDA5807M_BLERA_0 (0x0 << 2)
#define RDA5807M_BLERA_12 (0x1 << 2)
#define RDA5807M_BLERA_35 (0x2 << 2)
#define RDA5807M_BLERA_U (RDA5807M_BLERA_12 | RDA5807M_BLERA_35)
#define RDA5807M_BLERB_MASK (uint16_t)(0x0003)
#define RDA5807M_BLERB_0 0x0
#define RDA5807M_BLERB_12 0x1
#define RDA5807M_BLERB_35 0x2
#define RDA5807M_BLERB_U (RDA5807M_BLERB_12 | RDA5807M_BLERB_35)
#define RDA5807P_GPIO3_MASK (uint16_t)(0x0030)
#define RDA5807P_GPIO3_HIZ (0x0 << 4)
#define RDA5807P_GPIO3_ST (0x1 << 4)
#define RDA5807P_GPIO3_L (0x2 << 4)
#define RDA5807P_GPIO3_H (0x3 << 4)
#define RDA5807P_GPIO2_MASK (uint16_t)(0x000C)
#define RDA5807P_GPIO2_HIZ (0x0 << 2)
#define RDA5807P_GPIO2_INT (0x1 << 2)
#define RDA5807P_GPIO2_L (0x2 << 2)
#define RDA5807P_GPIO2_H (0x3 << 2)
#define RDA5807P_GPIO1_MASK (uint16_t)(0x0003)
#define RDA5807P_GPIO1_HIZ 0x0
#define RDA5807P_GPIO1_L 0x2
#define RDA5807P_GPIO1_H 0x3
#define RDA5807P_LNAP_MASK (uint16_t)(0x00C0)
#define RDA5807P_LNAP_NONE (0x0 << 6)
#define RDA5807P_LNAP_N (0x1 << 6)
#define RDA5807P_LNAP_P (0x2 << 6)
#define RDA5807P_LNAP_BOTH (0x3 << 6)
#define RDA5807P_LNAI_MASK (uint16_t)(0x0030)
#define RDA5807P_LNAI_1_8M (0x0 << 4)
#define RDA5807P_LNAI_2_1M (0x1 << 4)
#define RDA5807P_LNAI_2_5M (0x2 << 4)
#define RDA5807P_LNAI_3_0M (0x3 << 4)
#define RDA5807P_I2SRATE_MASK (uint16_t)(0x00F0)
#define RDA5807P_I2SRATE_8K (0x0 << 4)
#define RDA5807P_I2SRATE_11_025K (0x1 << 4)
#define RDA5807P_I2SRATE_12K (0x2 << 4)
#define RDA5807P_I2SRATE_16K (0x3 << 4)
#define RDA5807P_I2SRATE_22_05K (0x4 << 4)
#define RDA5807P_I2SRATE_24K (0x5 << 4)
#define RDA5807P_I2SRATE_32K (0x6 << 4)
#define RDA5807P_I2SRATE_44_1K (0x7 << 4)
#define RDA5807P_I2SRATE_48K (0x8 << 4)
#define RDA5800_VOLUMEDSP_MASK (uint16_t)(0x00F0)
#define RDA5800_VOLUMEDSP_SHIFT 4
#define RDA5800_LNAP_MASK 0x6000
#define RDA5800_LNAP_N (0x1 << 13)
#define RDA5800_LNAP_P (0x2 << 13)
#define RDA5800_LNAP_BOTH (0x3 << 13)

void RDA5807_write(void);
void RDA5807_init(void);
void RDA5807_SetFreq(uint16_t freq);
void RDA5807_SetVolume(uint8_t vol);

void RDA5807_AutoSeek(uint8_t d);
void RDA5807M_SeekUp(uint8_t wrap);
void RDA5807M_SeekDown(uint8_t wrap);

uint16_t RDA5807M_GetFrequency(void);
uint16_t RDA5807M_GetRegister(uint8_t reg);
uint16_t RDA5807M_GetBandAndSpacing(void);

uint16_t RDA5807M_GetRegister(uint8_t reg);
void RDA5807M_UpdateRegister(uint8_t reg, uint16_t mask, uint16_t value);
void RDA5807M_SetRegister(uint8_t reg, const uint16_t value);


#endif /* RDA5807M_H_ */