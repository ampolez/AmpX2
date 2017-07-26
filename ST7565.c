#include <util/delay.h>
#include <avr/io.h>
#include "ST7565.h"
#include "helpers.h"
#include "LCD_font.h"

unsigned char screen_buffer[LCD_PAGES][LCD_COLUMNS];

void ST7565_send(unsigned char byte){
  char i;
  
  SETBIT(ST7565_PORT, ST7565_CS2);
  for(i=0;i<8;i++){
	if(byte>>7 == 1)
	{
		SETBIT(ST7565_PORT, ST7565_SI);
	} else
	{
		CLEARBIT(ST7565_PORT, ST7565_SI);
	}
    byte<<=1;
	CLEARBIT(ST7565_PORT, ST7565_SCL);
	SETBIT(ST7565_PORT, ST7565_SCL);
  }
  CLEARBIT(ST7565_PORT,ST7565_CS2);
}

void ST7565_comm(unsigned char command)
{
  char i;
  CLEARBIT(ST7565_PORT, ST7565_A0);
  SETBIT(ST7565_PORT, ST7565_CS2);
  for(i=0;i<8;i++)
  {
	if(command>>7 == 1)
	{
		SETBIT(ST7565_PORT, ST7565_SI);
	} else
	{
		CLEARBIT(ST7565_PORT, ST7565_SI);
	}
    command<<=1;
	CLEARBIT(ST7565_PORT, ST7565_SCL);
	SETBIT(ST7565_PORT, ST7565_SCL);
  }
  CLEARBIT(ST7565_PORT, ST7565_CS2);
}

void ST7565_data(unsigned char data){
  char i;
  SETBIT(ST7565_PORT, ST7565_A0);
  SETBIT(ST7565_PORT, ST7565_CS2);
  for(i=0;i<8;i++)
  {
	if(data>>7 == 1)
	{
		SETBIT(ST7565_PORT, ST7565_SI);
	} else
	{
		CLEARBIT(ST7565_PORT, ST7565_SI);
	}
    data<<=1;
	CLEARBIT(ST7565_PORT, ST7565_SCL);
	SETBIT(ST7565_PORT, ST7565_SCL);
  }
  CLEARBIT(ST7565_PORT, ST7565_CS2);
}

void ST7565_reset(void){
  CLEARBIT(ST7565_PORT, ST7565_RES);
  _delay_ms(500);
  SETBIT(ST7565_PORT, ST7565_RES);
  _delay_ms(500);
}

void ST7565_Fill(unsigned char pattern)
{
  unsigned char page,col;

  for(page=0;page<LCD_PAGES;page++)
  {
    ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
    ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM);
    ST7565_comm(0b00000000);
	SETBIT(ST7565_PORT, ST7565_A0);
    for(col=0;col<LCD_COLUMNS;col++)
	{
      ST7565_send(pattern);
      //screen_buffer[page][col] = pattern;
    }
  }
}

void ST7565_init(void)
{
  // Настройка дисплея
  ST7565_DDR |= (1<<ST7565_CS2 | 1<<ST7565_SCL | 1<<ST7565_A0 | 1<<ST7565_SI | 1<<ST7565_RES);		// Пины на выход

	
  ST7565_reset(); 
  
  ST7565_comm(ST7565_DUMMY_COMM);
  ST7565_comm(ST7565_DUMMY_COMM);
  
  ST7565_comm(ST7565_LCD_BIAS_SET_COMM | (ST7565_DEFAULT_BIAS&1)); // 1/9 bias 
  
  ST7565_comm(ST7565_ADC_SELECT_COMM | (ST7565_DEFAULT_ADC&1)); // ADC set 
   
  ST7565_comm(ST7565_COMM_OUTPUT_MODE_SELECT_COMM | ((ST7565_DEFAULT_COM_DIRECTION&1)<<3)); // COM direction set
  
  ST7565_comm(ST7565_RESISTOR_RATIO_SET_COMM | (ST7565_DEFAULT_CONTRAST&7)); // V0 resistor ratio set
  
  ST7565_comm(ST7565_ELECTRONIC_VOLUME_SET_COMM); // Electronic volume
  ST7565_comm(ST7565_DEFAULT_ELECTRONIC_VOLUME&63);
  
  ST7565_comm(ST7565_BOOSTER_RATIO_SET_COMM); // Booster ratio
  ST7565_comm(ST7565_DEFAULT_BOOSTER_RATIO&3);
  
  ST7565_comm(ST7565_POWER_CONTROL_SET_COMM | (ST7565_DEFAULT_POWER_CONTROL&7)); // Booster ON, Voltage regulator ON, Voltage Follower ON
  
  ST7565_Fill(ST7565_DEFAULT_FILL_PATTERN);
  
  ST7565_comm(ST7565_DISPLAY_ON_OFF_COMM | (ST7565_DEFAULT_DISPLAY_ON_OFF&1)); // Display ON
  
  ST7565_comm(ST7565_DISPLAY_START_LINE_SET_COMM | (ST7565_DEFAULT_START_ADDRESS&63)); // Start line address
}

void ST7565_on_off(unsigned char on_off){
  on_off&=0x01;
  ST7565_comm(ST7565_DISPLAY_ON_OFF_COMM | on_off); 
}

void ST7565_volume(unsigned char volume){
  volume&=0x3F;
  ST7565_comm(ST7565_ELECTRONIC_VOLUME_SET_COMM);
  ST7565_comm(volume);
}

void ST7565_normal_reverse(char normal_reverse)
{
  normal_reverse &= 0x01;
  ST7565_comm(ST7565_DISPLAY_NORMAL_REVERSE_COMM | normal_reverse);
}

void ST7565_contrast(unsigned char contrast)
{
  contrast&=0x07;
  ST7565_comm(ST7565_RESISTOR_RATIO_SET_COMM | contrast);
}

void ST7565_Cursor(unsigned char page,unsigned char col){
  if((page>=LCD_PAGES)||(col>=LCD_COLUMNS)) return;
  ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
  ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM|(col>>4));
  ST7565_comm(col&0x0F);  
}

void ST7565_SetPixel(unsigned char x,unsigned char y)
{
  unsigned char page;
  if((x>=LCD_COLUMNS)||(y>=LCD_ROWS)) return;
  page=y>>3;
  ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
  ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM|(x>>4));
  ST7565_comm(x&0x0F);
  screen_buffer[page][x]|=1<<(y&0x07);
  ST7565_data(screen_buffer[page][x]);
}

void ST7565_ClearPixel(unsigned char x,unsigned char y){
  unsigned char page;
  if((x>=LCD_COLUMNS)||(y>=LCD_ROWS)) return;
  page=y>>3;
  ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
  ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM|(x>>4));
  ST7565_comm(x&0x0F);
  screen_buffer[page][x]&=~(1<<(y&0x07));
  ST7565_data(screen_buffer[page][x]);
}

void ST7565_HorLine(unsigned char x1,unsigned char x2,unsigned char y){
  int b,page,row,col;
  if(x2<x1) {b=x1; x1=x2; x2=b;} 
  if(y>=LCD_ROWS) return;
  if(x1>=LCD_COLUMNS) return;
  if(x2>=LCD_COLUMNS) x2=LCD_COLUMNS-1;
  page=y>>3;
  row=1<<(y&0x07);
  ST7565_Cursor(page,x1); 
  SETBIT(ST7565_PORT, ST7565_A0);
  for(col=x1;col<=x2;col++){
    screen_buffer[page][col]|=row;
    ST7565_send(screen_buffer[page][col]);
  } 
}

void ST7565_VertLine(unsigned char x,unsigned char y1,unsigned char y2){
  int b,page1,row1,page2,row2,page;
  if(y2<y1) {b=y1; y1=y2; y2=b;} 
  if(x>=LCD_COLUMNS) return;
  if(y1>=LCD_ROWS) return;
  if(y2>=LCD_ROWS) y2=LCD_ROWS-1;
  page1=y1>>3;
  row1=y1&0x07; 
  page2=y2>>3;                                                             
  row2=y2&0x07; 
  if(page1==page2){
    ST7565_Cursor(page1,x);
    screen_buffer[page1][x]|=(0xFF>>(7-row2))&(0xFF<<row1);
    ST7565_data(screen_buffer[page1][x]);
    return;
  }
  for(page=page1;page<=page2;page++){
    ST7565_Cursor(page,x);
    if(page==page1){
      screen_buffer[page][x]|=0xFF<<row1;
      ST7565_data(screen_buffer[page][x]);
    }
    else if(page==page2){
      screen_buffer[page][x]|=0xFF>>(7-row2);
      ST7565_data(screen_buffer[page][x]);
    }
    else{
      screen_buffer[page][x]=0xFF;
      ST7565_data(screen_buffer[page][x]);    
    }
  } 
}

void ST7565_Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2){
  unsigned char dx,dy,b,x,y,page;
  unsigned int C; 
  if(x1==x2){
    ST7565_VertLine(x1,y1,y2);
    return;
  }
  if(y1==y2){
    ST7565_HorLine(x1,x2,y1);
    return;
  }
   
  if(x1<x2) dx=x2-x1;
  else dx=x1-x2;
  
  if(y1<y2) dy=y2-y1;
  else dy=y1-y2; 
  
  if(dx>=dy){
    C=2*x2*y1-2*x1*y2+dx;
    if(x2<x1) {b=x1; x1=x2; x2=b;}
    for(x=x1;x<=x2;x++){
      y=(C+2*(int)x*(y2-y1))/(2*dx);
      page=y>>3;
      if((page<LCD_PAGES)&&(x<LCD_COLUMNS)){
        ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
        ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM|(x>>4));
        ST7565_comm(x&0x0F);
        screen_buffer[page][x]|=1<<(y&0x07);
        ST7565_data(screen_buffer[page][x]);
      }      
    } 
  }
  else{
    C=2*y2*x1-2*y1*x2+dy;
    if(y2<y1) {b=y1; y1=y2; y2=b;}
    for(y=y1;y<=y2;y++){
      x=(C+2*(int)y*(x2-x1))/(2*dy);
      page=y>>3;
      if((page<LCD_PAGES)&&(x<LCD_COLUMNS)){
        ST7565_comm(ST7565_PAGE_ADDRESS_SET_COMM|page);
        ST7565_comm(ST7565_COLUMN_ADDRESS_SET_COMM|(x>>4));
        ST7565_comm(x&0x0F);
        screen_buffer[page][x]|=1<<(y&0x07);
        ST7565_data(screen_buffer[page][x]);
      }     
    } 
  } 
}

void ST7565_Rect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2){
  ST7565_HorLine(x1,x2,y1);
  ST7565_HorLine(x1,x2,y2);
  ST7565_VertLine(x1,y1,y2);
  ST7565_VertLine(x2,y1,y2);
}

void ST7565_FillRect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char pattern){
  int b,page1,row1,page2,row2,page,col;   
  
  if(x2<x1) {b=x1; x1=x2; x2=b;}
  if(y2<y1) {b=y1; y1=y2; y2=b;} 
  
  if(x1>=LCD_COLUMNS) return; 
  if(x2>=LCD_COLUMNS) x2=LCD_COLUMNS-1;
  if(y1>=LCD_ROWS) return;
  if(y2>=LCD_ROWS) y2=LCD_ROWS-1;  
  
  page1=y1>>3;
  row1=y1&0x07; 
  page2=y2>>3;                                                             
  row2=y2&0x07; 
  
  if(page1==page2){
    ST7565_Cursor(page1,x1);
    for(col=x1;col<=x2;col++){
      screen_buffer[page1][col] = screen_buffer[page1][col] & (~((0xFF>>(7-row2))&(0xFF<<row1))) | (pattern&(0xFF>>(7-row2))&(0xFF<<row1));
      ST7565_data(screen_buffer[page1][col]);  
    }
    return;
  }
  for(page=page1;page<=page2;page++){
    ST7565_Cursor(page,x1);
    for(col=x1;col<=x2;col++){
      if(page==page1){  
        screen_buffer[page][col] = screen_buffer[page][col] & (~(0xFF<<row1)) | (pattern & (0xFF<<row1));
        ST7565_data(screen_buffer[page][col]);  
      }
      else if(page==page2){
        screen_buffer[page][col] = screen_buffer[page][col] & (~(0xFF>>(7-row2))) | (pattern & (0xFF>>(7-row2)));
        ST7565_data(screen_buffer[page][col]);
      }
      else{
        screen_buffer[page][col]=pattern;
        ST7565_data(screen_buffer[page][col]);    
      }
    }
  }  
}

void reverse_rect(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2){
  int b,page1,row1,page2,row2,page,col;   
  
  if(x2<x1) {b=x1; x1=x2; x2=b;}
  if(y2<y1) {b=y1; y1=y2; y2=b;} 
  
  if(x1>=LCD_COLUMNS) return; 
  if(x2>=LCD_COLUMNS) x2=LCD_COLUMNS-1;
  if(y1>=LCD_ROWS) return;
  if(y2>=LCD_ROWS) y2=LCD_ROWS-1;  
  
  page1=y1>>3;
  row1=y1&0x07; 
  page2=y2>>3;                                                             
  row2=y2&0x07; 
  
  if(page1==page2){
    ST7565_Cursor(page1,x1);
    for(col=x1;col<=x2;col++){
      screen_buffer[page1][col]^=(0xFF>>(7-row2))&(0xFF<<row1);
      ST7565_data(screen_buffer[page1][col]);  
    }
    return;
  }
  for(page=page1;page<=page2;page++){
    ST7565_Cursor(page,x1);
    for(col=x1;col<=x2;col++){
      if(page==page1){  
        screen_buffer[page][col]^=0xFF<<row1;
        ST7565_data(screen_buffer[page][col]);  
      }
      else if(page==page2){
        screen_buffer[page][col]^=0xFF>>(7-row2);
        ST7565_data(screen_buffer[page][col]);
      }
      else{
        screen_buffer[page][col]^=0xFF;
        ST7565_data(screen_buffer[page][col]);    
      }
    }
  }  
}

unsigned char ASCII_to_LCD(unsigned char c)
{
	if(c<32) return 0;
	if(c=='°') return 95;
	if(c-32>=sizeof(lcd_charset)/5) return 0;
	if(c<127) return c-32;
	return 0;
}

void lcd_putchar(unsigned char c, unsigned char x, unsigned char y, unsigned char normal_reverse)
{
  unsigned char i,page,row,mask;

  if((y>=LCD_ROWS)||(x>=LCD_COLUMNS)) 
	return;

  page=y>>3;
  row=y&0x07;
  mask=0xFF<<row;

  ST7565_Cursor(page,x);
  if(row==0)
  {
	  for(i=0;i<5;i++)
	  if(x+i<LCD_COLUMNS)
	  {
		  if(normal_reverse==0) 
			screen_buffer[page][x+i] = lcd_charset[ASCII_to_LCD(c)][i];
		  else 
			screen_buffer[page][x+i] = (~lcd_charset[ASCII_to_LCD(c)][i]);
		  ST7565_data(screen_buffer[page][x+i]);
	  }
  }
  else
  {
	  for(i=0;i<5;i++)
	  {
		if(x+i<LCD_COLUMNS)
		{
			if(normal_reverse==0)
			screen_buffer[page][x+i]=(screen_buffer[page][x+i]&(~mask))|(lcd_charset[ASCII_to_LCD(c)][i]<<row);
			else
			screen_buffer[page][x+i]=(screen_buffer[page][x+i]&(~mask))|((~lcd_charset[ASCII_to_LCD(c)][i])<<row);
			ST7565_data(screen_buffer[page][x+i]);
		}
		  
	  }

	  if(page==LCD_PAGES-1) 
		return;

	  page++;
	  
	  ST7565_Cursor(page,x);
	  
	  for(i=0;i<5;i++)
	  {
		  if(x+i<LCD_COLUMNS)
		  {
			  if(normal_reverse==0) 
				screen_buffer[page][x+i]=(screen_buffer[page][x+i]&mask)|(lcd_charset[ASCII_to_LCD(c)][i]>>(8-row));
			  else 
				screen_buffer[page][x+i]=(screen_buffer[page][x+i]&mask)|((~lcd_charset[ASCII_to_LCD(c)][i])>>(8-row));
			  ST7565_data(screen_buffer[page][x+i]);
		  }		  
	  }
  }
}

void lcd_putchar6(char c,unsigned char x,unsigned char y,char normal_reverse)
{
  unsigned char page,row,mask;
  
  lcd_putchar(c,x,y,normal_reverse);
  
  page=y>>3;
  row=y&0x07;
  mask=0xFF<<row;
  x+=5;
  
  ST7565_Cursor(page,x);
  
  if(row==0)
  {
	  if(x<LCD_COLUMNS){
		  if(normal_reverse==0) screen_buffer[page][x]=0;
		  else screen_buffer[page][x]=0xFF;
		  ST7565_data(screen_buffer[page][x]);
	  }
  }
  else{
	  if(x<LCD_COLUMNS){
		  if(normal_reverse==0) screen_buffer[page][x]&=(~mask);
		  else screen_buffer[page][x]|=mask;
		  ST7565_data(screen_buffer[page][x]);
		  page++;
		  ST7565_Cursor(page,x);
		  if(normal_reverse==0) screen_buffer[page][x]&=mask;
		  else screen_buffer[page][x]|=(~mask);
		  ST7565_data(screen_buffer[page][x]);
	  }
  }
} 

unsigned char lcd_puts(char *str,unsigned char x,unsigned char y,char normal_reverse)
{
  unsigned char dx=0;
  char c; 

  c =* str;
  if(c == 0) 
  {
	return 0;
  }
  
  while(*str)
  {
    lcd_putchar6(c, x+dx, y, normal_reverse); 
    dx += 6;
    str++;
    c =* str;
  }
  dx -= 6;
  if(normal_reverse)
  {
    ST7565_HorLine(x,x+dx+5,y-1);
    ST7565_VertLine(x-1,y-1,y+7);
  }
  return dx+6;
}

unsigned char lcd_puts_right_alligned(char *str,unsigned char x,unsigned char y,char normal_reverse){
  unsigned char dx=0;
  unsigned char c=0;
  while(*(str+c)!=0) c++; 
  if(c==0) return 0; 
  while(c>0){
    c--;
    lcd_putchar6(*(str+c),x-dx-5,y,normal_reverse);
    dx+=6;
  }
  dx-=6;
  if(normal_reverse){
    ST7565_HorLine(x,x-dx-5,y-1);
    ST7565_VertLine(x-dx-6,y-1,y+7);
  }
  return dx+6;
}

unsigned char ST7565_PutNum(unsigned long int n,unsigned char x,unsigned char y,char normal_reverse)
{
  char digits[10];
  signed char i,count;
  unsigned char dx=0;
    
  digits[0]=n%10;
  count=1;
  n/=10;
  
  while(n>0){
    digits[count]=n%10;
    count++;
    n/=10;
  }  
  
  for(i=count-1;i>=0;i--)
  {
    lcd_putchar6(digits[i]+0x30,x+dx,y,normal_reverse); 
    dx+=6;
  }
  dx-=6;
  if(normal_reverse){
    ST7565_HorLine(x,x+dx+5,y-1);
    ST7565_VertLine(x-1,y-1,y+7);
  }
  return dx+6; 
}

unsigned char lcd_putnum_right_alligned(unsigned long int n,unsigned char x,unsigned char y,char normal_reverse){
  unsigned char dx=0;

  while((n>0)||(dx==0)){
    lcd_putchar6(n%10+0x30,x-dx-5,y,normal_reverse);  
    n/=10;
    dx+=6;
  }
  dx-=6;
  if(normal_reverse){
    ST7565_HorLine(x,x-dx-5,y-1);
    ST7565_VertLine(x-dx-6,y-1,y+7);
  }
  return dx+6;
}

void lcd_putbitmap(char *bitmap){
  unsigned char page,col;
  unsigned int pos=0;
  for(page=0;page<LCD_PAGES;page++){ 
    ST7565_Cursor(page,0);
	SETBIT(ST7565_PORT, ST7565_A0);
    for(col=0;col<LCD_COLUMNS;col++){
      screen_buffer[page][col]=bitmap[pos];
      ST7565_send(bitmap[pos]);
      pos++;
    }
  }    
}