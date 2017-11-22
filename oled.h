/**************************************************************************************************
* File: SF_Test.h
* File Type: C - Header File
* Company: (c) mikroElektronika, 2011
* Revision History:
* Description:
*     This module contains a set of functions that are used for communication with
*     Serial Flash.
* Test configuration:
*     MCU:             STM32F107VC
*                      http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00220364.pdf
*     Dev.Board:       EasyMx PRO v7 for STM32(R) ARM(R)
*                      http://www.mikroe.com/easymx-pro/stm32/
*                      ac:tft_touchpanel
*                      ac:serial-flash
*
*     Oscillator:      HSE-PLL, 72.000MHz
*     SW:              mikroC PRO for ARM
*                      http://www.mikroe.com/mikroc/arm/
* NOTES:
*     Serial Flash use SPI bus to communicate with MCU.
*     Turn on TFT backlight on SW11.3
*     Turn on SPI lines at SW13.1, SW13.2, sw13.3 and Serial Flash CS at SW13.8
**************************************************************************************************/

#ifndef __OLED_H
#define __OLED_H

#define SSD1306_96_39
#define SSD1306_LCDWIDTH                  96
#define SSD1306_LCDHEIGHT                 39

#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_SETSEGMENTREMAP 0xA1  // ja
#define SSD1306_SEGREMAP 0xA0

#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_DISPLAYON 0xAF



#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2



#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


#define OLED_CS_CLR()     pin_clear(PPORT_D, PIN_CS); 
#define OLED_CS_SET()     pin_set(PPORT_D, PIN_CS); 

#define OLED_DC_CLR()     pin_clear(PPORT_C, PIN_DC); 
#define OLED_DC_SET()     pin_set(PPORT_C, PIN_DC); 


#define OLED_RST_CLR()     pin_clear(PPORT_C, PIN_RST); 
#define OLED_RST_SET()     pin_set(PPORT_C, PIN_RST); 



void OLED_M_command(unsigned char temp);
void SPI0_Write(unsigned char temp);
void OLED_M_Init(void);
void ssd1306_putc(unsigned char c);
void ssd1306_puts(char * string);
void Set_Page_Address(unsigned char add);
void Set_Column_Address(unsigned char add);
void ssd1306_clear(void);
void ssd1306_fill(void);
void Display_Picture(unsigned char pic[]);
void contrast_control(unsigned char temp);
void startscroll_Right(unsigned char x, unsigned char y);
void startscroll_Left(unsigned char x, unsigned char y);
void startscroll_DiagRight(unsigned char x, unsigned char y);
void startscroll_DiagLeft(unsigned char x, unsigned char y);
void scroll_STOP(void);
void set_pos(uint8_t x, uint8_t y);




#endif
/**************************************************************************************************
* End of File
**************************************************************************************************/
