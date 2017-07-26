#include <avr/pgmspace.h>

// 
// const unsigned char lcd_charset[] PROGMEM = {
// 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	// ' '
// 	0x00, 0x00, 0x00, 0x00, 0x0B, 0xF8, 0x00, 0x00, 0x00, 0x00, 	// '!'
// 	0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 	// '"'
// 	0x02, 0x20, 0x0F, 0xF8, 0x02, 0x20, 0x0F, 0xF8, 0x02, 0x20, 	// '#'
// 	0x04, 0x60, 0x08, 0x90, 0x1F, 0xF8, 0x09, 0x10, 0x06, 0x20, 	// '$'
// 	0x06, 0x10, 0x01, 0x28, 0x04, 0x90, 0x0A, 0x40, 0x04, 0x30, 	// '%'
// 	0x07, 0x30, 0x08, 0xC8, 0x09, 0x30, 0x06, 0x00, 0x09, 0x00, 	// '&'
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 	// '''
// 	0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x10, 0x04, 0x00, 0x00, 	// '('
// 	0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x0F, 0xF8, 0x00, 0x00, 	// ')'
// 	0x01, 0x10, 0x00, 0xA0, 0x03, 0xF8, 0x00, 0xA0, 0x01, 0x10, 	// '*'
// 	0x01, 0x00, 0x01, 0x00, 0x07, 0xC0, 0x01, 0x00, 0x01, 0x00, 	// '+'
// 	0x00, 0x00, 0x2C, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 	// ','
// 	0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 	// '-'
// 	0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	// '.'
// 	0x0C, 0x00, 0x03, 0x00, 0x00, 0xC0, 0x00, 0x38, 0x00, 0x00, 	// '/'
// 	0x07, 0xF0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0xF0, 	// '0'
// 	0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x0F, 0xF8, 0x00, 0x00, 	// '1'
// 	0x0C, 0x10, 0x0A, 0x08, 0x09, 0x08, 0x08, 0x88, 0x08, 0x70, 	// '2'
// 	0x04, 0x10, 0x08, 0x08, 0x08, 0x88, 0x08, 0x88, 0x07, 0x70, 	// '3'
// 	0x03, 0x00, 0x02, 0xC0, 0x02, 0x30, 0x0F, 0xF8, 0x02, 0x00, 	// '4'
// 	0x04, 0xF8, 0x08, 0x48, 0x08, 0x48, 0x08, 0x48, 0x07, 0x88, 	// '5'
// 	0x07, 0xF0, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x07, 0x10, 	// '6'
// 	0x00, 0x08, 0x0E, 0x08, 0x01, 0x88, 0x00, 0x68, 0x00, 0x18, 	// '7'
// 	0x07, 0x70, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x07, 0x70, 	// '8'
// 	0x04, 0x70, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x07, 0xF0, 	// '9'
// 	0x0C, 0xC0, 0x0C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	// ':'
// 	0x00, 0x00, 0x2C, 0xC0, 0x1C, 0xC0, 0x00, 0x00, 0x00, 0x00, 	// ';'
// 	0x01, 0x00, 0x02, 0x80, 0x04, 0x40, 0x08, 0x20, 0x00, 0x00, 	// '<'
// 	0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 	// '='
// 	0x08, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01, 0x00, 0x00, 0x00, 	// '>'
// 	0x00, 0x10, 0x00, 0x08, 0x0B, 0x08, 0x00, 0x88, 0x00, 0x70, 	// '?'
// 	0x01, 0xE0, 0x02, 0x10, 0x04, 0xC8, 0x05, 0x28, 0x02, 0xF0, 	// '@'
// 	0x0F, 0x00, 0x02, 0xE0, 0x02, 0x18, 0x02, 0xE0, 0x0F, 0x00, 	// 'A'
// 	0x0F, 0xF8, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x07, 0x70, 	// 'B'
// 	0x07, 0xF0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x10, 	// 'C'
// 	0x0F, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x04, 0x10, 0x03, 0xE0, 	// 'D'
// 	0x0F, 0xF8, 0x08, 0x88, 0x08, 0x88, 0x08, 0x08, 0x00, 0x00, 	// 'E'
// 	0x0F, 0xF8, 0x00, 0x88, 0x00, 0x88, 0x00, 0x08, 0x00, 0x00, 	// 'F'
// 	0x07, 0xF0, 0x08, 0x08, 0x08, 0x88, 0x04, 0x88, 0x0F, 0x90, 	// 'G'
// 	0x0F, 0xF8, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x0F, 0xF8, 	// 'H'
// 	0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	// 'I'
// 	0x06, 0x00, 0x08, 0x00, 0x08, 0x00, 0x07, 0xF8, 0x00, 0x00, 	// 'J'
// 	0x0F, 0xF8, 0x00, 0xC0, 0x01, 0x20, 0x02, 0x10, 0x0C, 0x08, 	// 'K'
// 	0x0F, 0xF8, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 	// 'L'
// 	0x0F, 0xF8, 0x00, 0x70, 0x01, 0x80, 0x00, 0x70, 0x0F, 0xF8, 	// 'M'
// 	0x0F, 0xF8, 0x00, 0x30, 0x00, 0xC0, 0x03, 0x00, 0x0F, 0xF8, 	// 'N'
// 	0x07, 0xF0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0xF0, 	// 'O'
// 	0x0F, 0xF8, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x00, 0x70, 	// 'P'
// 	0x07, 0xF0, 0x08, 0x08, 0x0A, 0x08, 0x0C, 0x08, 0x17, 0xF0, 	// 'Q'
// 	0x0F, 0xF8, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x0F, 0x70, 	// 'R'
// 	0x04, 0x70, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x07, 0x10, 	// 'S'
// 	0x00, 0x08, 0x00, 0x08, 0x0F, 0xF8, 0x00, 0x08, 0x00, 0x08, 	// 'T'
// 	0x07, 0xF8, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x07, 0xF8, 	// 'U'
// 	0x00, 0x38, 0x03, 0xC0, 0x0C, 0x00, 0x03, 0xC0, 0x00, 0x38, 	// 'V'
// 	0x00, 0xF8, 0x0F, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0xF8, 	// 'W'
// 	0x0E, 0x38, 0x01, 0x40, 0x00, 0x80, 0x01, 0x40, 0x0E, 0x38, 	// 'X'
// 	0x00, 0x38, 0x00, 0x40, 0x0F, 0x80, 0x00, 0x40, 0x00, 0x38, 	// 'Y'
// 	0x0C, 0x08, 0x0B, 0x08, 0x08, 0x88, 0x08, 0x68, 0x08, 0x18, 	// 'Z'
// 	0x00, 0x00, 0x1F, 0xFC, 0x10, 0x04, 0x00, 0x00, 0x00, 0x00, 	// '['
// 	0x00, 0x00, 0x00, 0x38, 0x00, 0xC0, 0x03, 0x00, 0x0C, 0x00, 	// '\'
// 	0x00, 0x00, 0x10, 0x04, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 	// ']'
// 	0x00, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 	// '^'
// 	0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 	// '_'
// 	0x00, 0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 	// '`'
// 	0x06, 0x00, 0x09, 0x40, 0x09, 0x40, 0x09, 0x40, 0x0F, 0x80, 	// 'a'
// 	0x0F, 0xF8, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x07, 0x80, 	// 'b'
// 	0x07, 0x80, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x04, 0x80, 	// 'c'
// 	0x07, 0x80, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x0F, 0xF8, 	// 'd'
// 	0x07, 0x80, 0x09, 0x40, 0x09, 0x40, 0x09, 0x40, 0x05, 0x80, 	// 'e'
// 	0x0F, 0xF0, 0x00, 0x48, 0x00, 0x48, 0x00, 0x48, 0x00, 0x10, 	// 'f'
// 	0x27, 0x80, 0x28, 0x40, 0x28, 0x40, 0x28, 0x40, 0x1F, 0xC0, 	// 'g'
// 	0x0F, 0xF8, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x0F, 0x80, 	// 'h'
// 	0x00, 0x00, 0x00, 0x00, 0x0F, 0xC8, 0x00, 0x00, 0x00, 0x00, 	// 'i'
// 	0x20, 0x00, 0x20, 0x00, 0x1F, 0xC8, 0x00, 0x00, 0x00, 0x00, 	// 'j'
// 	0x0F, 0xF8, 0x01, 0x00, 0x02, 0x80, 0x04, 0x40, 0x08, 0x00, 	// 'k'
// 	0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 	// 'l'
// 	0x0F, 0xC0, 0x00, 0x40, 0x0F, 0x80, 0x00, 0x40, 0x0F, 0x80, 	// 'm'
// 	0x0F, 0xC0, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x0F, 0x80, 	// 'n'
// 	0x07, 0x80, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x07, 0x80, 	// 'o'
// 	0x3F, 0xC0, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x07, 0x80, 	// 'p'
// 	0x07, 0x80, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x3F, 0xC0, 	// 'q'
// 	0x0F, 0xC0, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 	// 'r'
// 	0x04, 0x80, 0x09, 0x40, 0x0A, 0x40, 0x04, 0x80, 0x00, 0x00, 	// 's'
// 	0x07, 0xF0, 0x08, 0x40, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 	// 't'
// 	0x07, 0xC0, 0x08, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0F, 0xC0, 	// 'u'
// 	0x00, 0xC0, 0x03, 0x00, 0x0C, 0x00, 0x03, 0x00, 0x00, 0xC0, 	// 'v'
// 	0x01, 0xC0, 0x0E, 0x00, 0x01, 0xC0, 0x0E, 0x00, 0x01, 0xC0, 	// 'w'
// 	0x0C, 0xC0, 0x03, 0x00, 0x03, 0x00, 0x0C, 0xC0, 0x00, 0x00, 	// 'x'
// 	0x20, 0x00, 0x23, 0xC0, 0x1C, 0x00, 0x04, 0x00, 0x03, 0xC0, 	// 'y'
// 	0x0C, 0x40, 0x0A, 0x40, 0x09, 0x40, 0x08, 0xC0, 0x00, 0x00, 	// 'z'
// 	0x00, 0x00, 0x00, 0x80, 0x0F, 0x78, 0x10, 0x04, 0x00, 0x00, 	// '{'
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 	// '|'
// 	0x00, 0x00, 0x10, 0x04, 0x0F, 0x78, 0x00, 0x80, 0x00, 0x00, 	// '}'
// 	0x00, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 	// '~'
// 	0x00, 0x38, 0x00, 0x44, 0x00, 0x44, 0x00, 0x44, 0x00, 0x38, 	// ''
// };

const char lcd_charset[][5] = 
{
  { //space
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
  },
  { //!
    0b00000000,
    0b00000000,
    0b01001111,
    0b00000000,
    0b00000000
  },
  { //"
    0b00000000,
    0b00000111,
    0b00000000,
    0b00000111,
    0b00000000
  },
  { //#
    0b00010100,
    0b01111111,
    0b00010100,
    0b01111111,
    0b00010100
  },
  { //$
    0b00100100,
    0b00101010,
    0b01111111,
    0b00101010,
    0b00010010
  },
  { //%
    0b00100011,
    0b00010011,
    0b00001000,
    0b01100100,
    0b01100010
  },
  { //&
    0b00110110,
    0b01001001,
    0b01010101,
    0b00100010,
    0b01010000
  },
  { //'
    0b00000000,
    0b00000101,
    0b00000011,
    0b00000000,
    0b00000000
  },
  { //(
    0b00000000,
    0b00011100,
    0b00100010,
    0b01000001,
    0b00000000
  },
  { //)
    0b00000000,
    0b01000001,
    0b00100010,
    0b00011100,
    0b00000000
  },
  { //*
    0b00010100,
    0b00001000,
    0b00111110,
    0b00001000,
    0b00010100
  },
  { //+
    0b00001000,
    0b00001000,
    0b00111110,
    0b00001000,
    0b00001000
  },
  { //,
    0b00000000,
    0b01010000,
    0b00110000,
    0b00000000,
    0b00000000
  },
  { //-
    0b00001000,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00001000
  },
  { //.
    0b00000000,
    0b01100000,
    0b01100000,
    0b00000000,
    0b00000000
  },
  { ///
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010
  },
  { //0
    0b00111110,
    0b01010001,
    0b01001001,
    0b01000101,
    0b00111110
  },
  { //1
    0b00000000,
    0b01000010,
    0b01111111,
    0b01000000,
    0b00000000
  },
  { //2
    0b01000010,
    0b01100001,
    0b01010001,
    0b01001001,
    0b01000110
  },
  { //3
    0b00100001,
    0b01000001,
    0b01000101,
    0b01001011,
    0b00110001
  },
  { //4
    0b00011000,
    0b00010100,
    0b00010010,
    0b01111111,
    0b00010000
  },
  { //5
    0b00100111,
    0b01000101,
    0b01000101,
    0b01000101,
    0b00111001
  },
  { //6
    0b00111100,
    0b01001010,
    0b01001001,
    0b01001001,
    0b00110000
  },
  { //7
    0b00000011,
    0b00000001,
    0b01110001,
    0b00001001,
    0b00000111
  },
  { //8
    0b00110110,
    0b01001001,
    0b01001001,
    0b01001001,
    0b00110110
  },
  { //9
    0b00000110,
    0b01001001,
    0b01001001,
    0b00101001,
    0b00011110
  },
  { //:
    0b00000000,
    0b00110110,
    0b00110110,
    0b00000000,
    0b00000000
  },
  { //;
    0b00000000,
    0b01010110,
    0b00110110,
    0b00000000,
    0b00000000
  },
  { //<
    0b00001000,
    0b00010100,
    0b00100010,
    0b01000001,
    0b00000000
  },
  { //=
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100
  },
  { //>
    0b00000000,
    0b01000001,
    0b00100010,
    0b00010100,
    0b00001000
  },
  { //?
    0b00000010,
    0b00000001,
    0b01010001,
    0b00001001,
    0b00000110
  },
  { //@
    0b00110010,
    0b01001001,
    0b01111001,
    0b01000001,
    0b00111110
  },
  { //A
    0b01111100,
    0b00010010,
    0b00010001,
    0b00010010,
    0b01111100
  },
  { //B
    0b01111111,
    0b01001001,
    0b01001001,
    0b01001001,
    0b00110110
  },
  { //C
    0b00111110,
    0b01000001,
    0b01000001,
    0b01000001,
    0b00100010
  },
  { //D
    0b01111111,
    0b01000001,
    0b01000001,
    0b00100010,
    0b00011100
  },
  { //E
    0b01111111,
    0b01001001,
    0b01001001,
    0b01001001,
    0b01000001
  },
  { //F
    0b01111111,
    0b00001001,
    0b00001001,
    0b00001001,
    0b00000001
  },
  { //G
    0b00111110,
    0b01000001,
    0b01001001,
    0b01001001,
    0b01111010
  },
  { //H
    0b01111111,
    0b00001000,
    0b00001000,
    0b00001000,
    0b01111111
  },
  { //I
    0b00000000,
    0b01000001,
    0b01111111,
    0b01000001,
    0b00000000
  },
  { //J
    0b00100000,
    0b01000000,
    0b01000001,
    0b00111111,
    0b00000001
  },
  { //K
    0b01111111,
    0b00001000,
    0b00010100,
    0b00100010,
    0b01000001
  },
  { //L
    0b01111111,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000
  },
  { //M
    0b01111111,
    0b00000010,
    0b00001100,
    0b00000010,
    0b01111111
  },
  { //N
    0b01111111,
    0b00000100,
    0b00001000,
    0b00010000,
    0b01111111
  },
  { //O
    0b00111110,
    0b01000001,
    0b01000001,
    0b01000001,
    0b00111110
  },
  { //P
    0b01111111,
    0b00001001,
    0b00001001,
    0b00001001,
    0b00000110
  },
  { //Q
    0b00111110,
    0b01000001,
    0b01010001,
    0b00100001,
    0b01011110
  },
  { //R
    0b01111111,
    0b00001001,
    0b00011001,
    0b00101001,
    0b01000110
  },
  { //S
    0b00100110,
    0b01001001,
    0b01001001,
    0b01001001,
    0b00110010
  },
  { //T
    0b00000001,
    0b00000001,
    0b01111111,
    0b00000001,
    0b00000001
  },
  { //U
    0b00111111,
    0b01000000,
    0b01000000,
    0b01000000,
    0b00111111
  },
  { //V
    0b00011111,
    0b00100000,
    0b01000000,
    0b00100000,
    0b00011111
  },
  { //W
    0b00111111,
    0b01000000,
    0b00111000,
    0b01000000,
    0b00111111
  },  
  { //X
    0b01100011,
    0b00010100,
    0b00001000,
    0b00010100,
    0b01100011
  },
  { //Y
    0b00000011,
    0b00000100,
    0b01111000,
    0b00000100,
    0b00000011
  },
  { //Z
    0b01100001,
    0b01010001,
    0b01001001,
    0b01000101,
    0b01000011
  },
  { //[
    0b00000000,
    0b01111111,
    0b01000001,
    0b01000001,
    0b00000000
  },
  { //
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000
  },
  { //]
    0b00000000,
    0b01000001,
    0b01000001,
    0b01111111,
    0b00000000
  },
  { //^
    0b00000100,
    0b00000010,
    0b00000001,
    0b00000010,
    0b00000100
  },
  { //_
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000
  },
  { //`
    0b00000000,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00000000
  },
  { //a
    0b00100000,
    0b01010100,
    0b01010100,
    0b01010100,
    0b01111000
  },
  { //b
    0b01111111,
    0b01001000,
    0b01000100,
    0b01000100,
    0b00111000
  },
  { //c
    0b00111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00100000
  },
  { //d
    0b00111000,
    0b01000100,
    0b01000100,
    0b01001000,
    0b01111111
  },
  { //e
    0b00111000,
    0b01010100,
    0b01010100,
    0b01010100,
    0b00011000
  },
  { //f
    0b00001000,
    0b01111110,
    0b00001001,
    0b00000001,
    0b00000010
  },
  { //g
    0b00001000,
    0b01010100,
    0b01010100,
    0b01010100,
    0b00111100
  },
  { //h
    0b01111111,
    0b00001000,
    0b00000100,
    0b00000100,
    0b01111000
  },
  { //i
    0b00000000,
    0b01001000,
    0b01111101,
    0b01000000,
    0b00000000
  },
  { //j
    0b00100000,
    0b01000000,
    0b01000100,
    0b00111101,
    0b00000000
  },
  { //k
    0b01111111,
    0b00010000,
    0b00101000,
    0b01000100,
    0b00000000
  },
  { //l
    0b00000000,
    0b01000001,
    0b01111111,
    0b01000000,
    0b00000000
  },
  { //m
    0b01111100,
    0b00000100,
    0b01111000,
    0b00000100,
    0b01111000
  },
  { //n
    0b01111100,
    0b00001000,
    0b00000100,
    0b00000100,
    0b01111000
  },
  { //o
    0b00111000,
    0b01000100,
    0b01000100,
    0b01000100,
    0b00111000
  },
  { //p
    0b01111100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00001000
  },
  { //q
    0b00001000,
    0b00010100,
    0b00010100,
    0b00011000,
    0b01111100
  },
  { //r
    0b01111100,
    0b00001000,
    0b00000100,
    0b00000100,
    0b00001000
  },
  { //s
    0b01001000,
    0b01010100,
    0b01010100,
    0b01010100,
    0b00100000
  },
  { //t
    0b00000100,
    0b00111111,
    0b01000100,
    0b01000000,
    0b00100000
  },
  { //u
    0b00111100,
    0b01000000,
    0b01000000,
    0b00100000,
    0b01111100
  },
  { //v
    0b00011100,
    0b00100000,
    0b01000000,
    0b00100000,
    0b00011100
  },
  { //w
    0b00111100,
    0b01000000,
    0b00110000,
    0b01000000,
    0b00111100
  },
  { //x
    0b01000100,
    0b00101000,
    0b00010000,
    0b00101000,
    0b01000100
  },
  { //y
    0b00001100,
    0b01010000,
    0b01010000,
    0b01010000,
    0b00111100
  },
  { //z
    0b01000100,
    0b01100100,
    0b01010100,
    0b01001100,
    0b01000100
  },
  { //{
    0b00000000,
    0b00001000,
    0b00110110,
    0b01000001,
    0b00000000
  },
  { //|
    0b00000000,
    0b00000000,
    0b01111111,
    0b00000000,
    0b00000000
  },
  { //}
    0b00000000,
    0b01000001,
    0b00110110,
    0b00001000,
    0b00000000
  },
  { //~
    0b00010000,
    0b00001000,
    0b00001000,
    0b00010000,
    0b00001000
  },
  { //�
	0b00000110,
	0b00001001,
	0b00001001,
	0b00000110,
	0b00000000
  }  
//   { //�
//     0b01111111,
//     0b00010000,
//     0b00010000,
//     0b00001000,
//     0b00011111
//   }  

};