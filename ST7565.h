// ST7565 LCD driver

#ifndef _ST7565_LCD_INCLUDED_
#define _ST7565_LCD_INCLUDED_

/**********LCD connection to the MCU**********/
#define ST7565_PORT PORTB
#define ST7565_DDR DDRB
#define ST7565_SI 3
#define ST7565_SCL 1
#define ST7565_A0 2
#define ST7565_RES 4
#define ST7565_CS2 0
/*********************************************/

/*******************LCD size******************/
#define LCD_ROWS 65
#define LCD_COLUMNS 132
#define LCD_PAGES 9
#define LCD_FONT_WIDTH 5
/*********************************************/ 

/*************Default LCD settings************/
#define ST7565_DEFAULT_BIAS 0 //0 - 1/9 bias, 1 - 1/7 bias
#define ST7565_DEFAULT_ADC 0 //0 - normal column scanning order, 1 - reverse column scanning order
#define ST7565_DEFAULT_COM_DIRECTION 1 //0 - normal row scanning order, 1 - reverse row scanning order
#define ST7565_DEFAULT_CONTRAST 6 //0 - minimal contrast,...,7 - maximal contrast
#define ST7565_DEFAULT_ELECTRONIC_VOLUME 32 //0 - minimal brightness,...,63 - maximal brightness
#define ST7565_DEFAULT_BOOSTER_RATIO 0 //Booster ratio: 0 - 2x/3x/4x, 1 - 5x, 3 - 6x.
#define ST7565_DEFAULT_POWER_CONTROL 0b111 //0b111 - Booster ON, Voltage regulator ON, Voltage Follower ON
                                           //0b011 - Booster OFF, Voltage regulator ON, Voltage Follower ON 
                                           //0b001 - Booster OFF, Voltage regulator OFF, Voltage Follower ON
                                           //0b000 - Booster OFF, Voltage regulator OFF, Voltage Follower OFF                                           
#define ST7565_DEFAULT_FILL_PATTERN 0b00000000 //After initialization, the LCD will be filled with this pattern. Set to 0b00000000 to clear the display.
#define ST7565_DEFAULT_DISPLAY_ON_OFF 0 //0 - display OFF, 1 - display ON
#define ST7565_DEFAULT_START_ADDRESS 0 //First row which will be displayed. Must be between 0 and 63.
/*********************************************/
                              
/*****************LCD commands****************/
#define ST7565_DUMMY_COMM                         0b00000000
#define ST7565_DISPLAY_ON_OFF_COMM                0b10101110
#define ST7565_DISPLAY_START_LINE_SET_COMM        0b01000000
#define ST7565_PAGE_ADDRESS_SET_COMM              0b10110000
#define ST7565_COLUMN_ADDRESS_SET_COMM            0b00010000
#define ST7565_ADC_SELECT_COMM                    0b10100000
#define ST7565_DISPLAY_NORMAL_REVERSE_COMM        0b10100110
#define ST7565_DISPLAY_ALL_POINTS_ON_OFF_COMM     0b10100100
#define ST7565_LCD_BIAS_SET_COMM                  0b10100010
#define ST7565_CRESET_COMM                        0b11100010
#define ST7565_COMM_OUTPUT_MODE_SELECT_COMM       0b11000000
#define ST7565_POWER_CONTROL_SET_COMM             0b00101000
#define ST7565_RESISTOR_RATIO_SET_COMM            0b00100000
#define ST7565_ELECTRONIC_VOLUME_SET_COMM         0b10000001
#define ST7565_STATIC_INDICATOR_ON_OFF_COMM       0b10101100
#define ST7565_BOOSTER_RATIO_SET_COMM             0b11111000
#define ST7565_NOP_COMM                           0b11100011
/*********************************************/



void ST7565_send(unsigned char byte); //Sends any byte to the LCD. Before use this command, set the A0 line.
void ST7565_comm(unsigned char command); //Sends command to the LCD. A0=0.
void ST7565_data(unsigned char data); //Sends data to the LCD. A0=1.
void ST7565_reset(void); //Generates the LCD RESET pulse.
void ST7565_init(void); //Loads default values to the LCD.
void ST7565_on_off(unsigned char on_off); //on_off=1 - turns the LCD ON, on_off=0 - turns the LCD OFF.
void ST7565_volume(unsigned char volume); //Sets LCD brightness (0..63).
void ST7565_contrast(unsigned char contrast); //Sets LCD contrast (0..7).
void ST7565_normal_reverse(char normal_reverse); //Sets LCD mode: 0 - normal, 1 - reverse.
void ST7565_Fill(unsigned char pattern); //Fills all the LCD with the pattern.
void ST7565_Cursor(unsigned char page,unsigned char col); //Sets LCD page and column addresses.
void ST7565_SetPixel(unsigned char x,unsigned char y); //Sets pixel at (x,y).
void ST7565_ClearPixel(unsigned char x,unsigned char y); //Clears pixel at (x,y).
void ST7565_HorLine(unsigned char x1,unsigned char x2,unsigned char y); //Draws horizontal line from (x1,y) to (x2,y).
void ST7565_VertLine(unsigned char x,unsigned char y1,unsigned char y2); //Draws vertical line from (x,y1) to (x,y2).
void ST7565_Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2); //Draws line from (x1,y1) to (x2,y2).
void ST7565_Rect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2); //Draws rectangle frame with opposite vertexes (x1,y1) and (x2,y2).
void ST7565_FillRect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char pattern); //Draws rectangle with opposite vertexes (x1,y1) and (x2,y2) filled by the pattern. Owerwrites all pixels in the frame.
void reverse_rect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2); //Reverses all pixels in the frame with opposite vertexes (x1,y1) and (x2,y2).
void lcd_putbitmap(char *bitmap); //Draws bitmap.
void lcd_putchar(unsigned char c,unsigned char x,unsigned char y,unsigned char normal_reverse); //Draws one character.
void lcd_putchar6(char c,unsigned char x,unsigned char y,char normal_reverse); //Draws one character with width=6.

//In next functions (x,y) is:
//left-alligned string  - left-up angle, 
//right-alligned string - right-up angle.
//All of them returns distance from the left edge to the right edge of the string displayed (number of pixels the string takes in horizontal direction).

unsigned char lcd_puts(char *str,unsigned char x,unsigned char y,char normal_reverse); //Draws string from RAM. 
unsigned char lcd_puts_right_alligned(char *str,unsigned char x,unsigned char y,char normal_reverse); //Draws string from RAM alligned to the right edge.
unsigned char ST7565_PutNum(unsigned long int n,unsigned char x,unsigned char y,char normal_reverse); //Draws number n.
unsigned char lcd_putnum_right_alligned(unsigned long int n,unsigned char x,unsigned char y,char normal_reverse); //Draws number n alligned to the right edge.


#endif
