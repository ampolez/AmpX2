/*
 * helpers.h
 *
 * Created: 05.04.2017 23:59:49
 *  Author: Андрей
 */ 


#ifndef HELPERS_H_
#define HELPERS_H_

#include <inttypes.h>

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#define BITSET(x,y) ((x) & (BIT(y)))
#define BITCLEAR(x,y) !BITSET((x), (y))
#define BITSSET(x,y) (((x) & (y)) == (y))
#define BITSCLEAR(x,y) (((x) & (y)) == 0)
#define BITVAL(x,y) (((x)>>(y)) & 1)

void bitWrite(unsigned char *var, uint8_t bit, uint8_t value);
uint16_t Make16Bit(uint8_t dataFirst, uint8_t dataSecond);


#endif /* HELPERS_H_ */