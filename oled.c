/*----------------------------------------------------------------------------
 * Name:    oled.c
 * Purpose: driver for OLED B Click
 *----------------------------------------------------------------------------*/


#include "main.h"

/* MicroE logo*/
unsigned char pic[]={
0xFF, 0xFF, 0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0x83, 0xC3, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0x03, 0x03, 0x83, 0xC3, 0xE3, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x63,
0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x83, 0xC3, 0xE3, 0x63, 0x63, 0x63, 0x63, 0xC3, 0xC3, 0x83,
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xF3, 0xFF, 0x8C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xFF, 0xC1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0x00, 0x00, 0x3E, 0xFF, 0xC1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC1, 0xFF,
0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x81, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0x03, 0x00, 0x80, 0x83,
0x03, 0x03, 0xC3, 0xC3, 0xC3, 0x83, 0x03, 0x03, 0x03, 0x00, 0x00, 0x83, 0xC3, 0xC3, 0xC3, 0x03,
0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
0x31, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0C, 0x0C, 0x1C, 0xF8, 0xF0, 0x00, 0x0C, 0x0C,
0x18, 0xFC, 0xFC, 0x00, 0x00, 0x04, 0x8C, 0xF8, 0x70, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0xFD, 0xFD,
0x00, 0x00, 0xFF, 0xFF, 0x03, 0x1F, 0xFC, 0xC0, 0x00, 0xC0, 0xFC, 0x1F, 0x03, 0xFF, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x3C, 0xF0, 0xC0, 0x00, 0xC0, 0xF0, 0x3C, 0x0C, 0x00, 0xF0, 0xF8,
0x1C, 0x0C, 0x0C, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
0xFF, 0xFE, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86,
0x86, 0x87, 0x87, 0x80, 0x80, 0x81, 0x83, 0x87, 0x86, 0x86, 0x87, 0x83, 0x81, 0x80, 0x80, 0x80,
0x80, 0x87, 0x87, 0x80, 0x80, 0x86, 0x87, 0x81, 0x80, 0x80, 0x87, 0x87, 0x80, 0x80, 0x87, 0x87,
0x80, 0x80, 0x87, 0x87, 0x80, 0x80, 0x81, 0x87, 0x86, 0x87, 0x81, 0x80, 0x80, 0x87, 0x87, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x87, 0x9F, 0xBF, 0xB1, 0xB0, 0x80, 0x80, 0x81, 0x83,
0x87, 0x86, 0x86, 0x83, 0x87, 0x87, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0xF8, 0xFE, 0xFF
};

/* 6x8 font */
unsigned char ssd1306_font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x07, 0x00, 0x07, 0x00,
	0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x00, 0x23, 0x13, 0x08, 0x64, 0x62,
	0x00, 0x36, 0x49, 0x55, 0x22, 0x50,
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08,
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0xA0, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02,
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,
	0x00, 0x62, 0x51, 0x49, 0x49, 0x46,
	0x00, 0x22, 0x41, 0x49, 0x49, 0x36,
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39,
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03,
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36,
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00,
	0x00, 0x00, 0xAC, 0x6C, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00,
	0x00, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08, 0x00,
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06,
	0x00, 0x32, 0x49, 0x79, 0x41, 0x3E,
	0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E,
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,
	0x00, 0x3E, 0x41, 0x41, 0x51, 0x72,
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,
	0x00, 0x26, 0x49, 0x49, 0x49, 0x32,
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63,
	0x00, 0x03, 0x04, 0x78, 0x04, 0x03,
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x00, 0x00,
	0x00, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x7F, 0x00, 0x00,
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04,
	0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x00, 0x01, 0x02, 0x04, 0x00, 0x00,
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78,
	0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,
	0x00, 0x38, 0x44, 0x44, 0x28, 0x00,
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02, 0x00,
	0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x00, 0x7D, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x84, 0x7D, 0x00, 0x00,
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00, 0x00,
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,
	0x00, 0x7C, 0x08, 0x04, 0x7C, 0x00,
	0x00, 0x38, 0x44, 0x44, 0x38, 0x00,
	0x00, 0xFC, 0x24, 0x24, 0x18, 0x00,
	0x00, 0x18, 0x24, 0x24, 0xFC, 0x00,
	0x00, 0x00, 0x7C, 0x08, 0x04, 0x00,
	0x00, 0x48, 0x54, 0x54, 0x24, 0x00,
	0x00, 0x04, 0x7F, 0x44, 0x00, 0x00,
	0x00, 0x3C, 0x40, 0x40, 0x7C, 0x00,
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44,
	0x00, 0x1C, 0xA0, 0xA0, 0x7C, 0x00,
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00, 0x00,
	0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00, 0x00,
	0x00, 0x02, 0x01, 0x01, 0x02, 0x01,
	0x00, 0x02, 0x05, 0x05, 0x02, 0x00, /* degree symbol */
};




/* Function to send a command to LCD over SPI */
void OLED_M_command(unsigned char temp){
    OLED_CS_CLR();
    OLED_DC_CLR();
    SPI0_Write(temp);
    OLED_CS_SET();
}

/* Function to send a data byte to LCD over SPI */
void OLED_M_data(unsigned char temp){
    OLED_CS_CLR();
    OLED_DC_SET();
    SPI0_Write(temp);
    OLED_CS_SET();
}

/* Function to initialize LCD */
void OLED_M_Init(){
    OLED_RST_CLR();
    Delay_ms(10);
    OLED_RST_SET();
    Delay_ms(10);
    OLED_M_command(SSD1306_DISPLAYOFF);             //0xAE  Set OLED Display Off
    OLED_M_command(SSD1306_SETDISPLAYCLOCKDIV);     //0xD5  Set Display Clock Divide Ratio/Oscillator Frequency
    OLED_M_command(0x80);
    OLED_M_command(SSD1306_SETMULTIPLEX);           //0xA8  Set Multiplex Ratio
    OLED_M_command(0x27);
    OLED_M_command(SSD1306_SETDISPLAYOFFSET);       //0xD3  Set Display Offset
    OLED_M_command(0x00);
    OLED_M_command(SSD1306_SETSTARTLINE);           //0x40  Set Display Start Line
    OLED_M_command(SSD1306_CHARGEPUMP);             //0x8D  Set Charge Pump
    OLED_M_command(0x14);                           //0x14  Enable Charge Pump
    //OLED_M_command(SSD1306_SETSTARTLINE | 0x0);     //A0
    OLED_M_command(SSD1306_COMSCANDEC);             //0xC8  Set COM Output Scan Direction
    OLED_M_command(SSD1306_SETCOMPINS);             //0xDA  Set COM Pins Hardware Configuration
    OLED_M_command(0x12);
    OLED_M_command(SSD1306_SETCONTRAST);            //0x81   Set Contrast Control
    OLED_M_command(0xAF);
    OLED_M_command(SSD1306_SETPRECHARGE);           //0xD9   Set Pre-Charge Period
    OLED_M_command(0x25);
    OLED_M_command(SSD1306_SETVCOMDETECT);          //0xDB   Set VCOMH Deselect Level
    OLED_M_command(0x20);
    OLED_M_command(SSD1306_DISPLAYALLON_RESUME);    //0xA4   Set Entire Display On/Off
    OLED_M_command(SSD1306_NORMALDISPLAY);          //0xA6   Set Normal/Inverse Display
    OLED_M_command(SSD1306_DISPLAYON);              //0xAF   Set OLED Display On
}



void ssd1306_putc(unsigned char c)
{
	uint8_t i = 0;

    for(i=0; i<6; i++)
    {
        OLED_M_data(ssd1306_font[((c - 0x20) * 6) + i]);
    }	
}

void ssd1306_puts(char *string)
{
  while (*string) 
  {
    ssd1306_putc(*string);
    string++;
  }
}

//Set page adress for Page Addressing Mode
void Set_Page_Address(unsigned char add)
{
    add=0xb0|add;
    OLED_M_command(add);
}
//Set column adress for Page Addressing Mode
void Set_Column_Address(unsigned char add)
{
        OLED_M_command((0x10|(add>>4)));
        OLED_M_command((0x0f&add));
}

void ssd1306_clear()
{
    unsigned char i,j;

    OLED_M_command(SSD1306_DISPLAYOFF);
    
	for(i=0; i<5; i++)       //clear page 0~8
	{
        Set_Page_Address(i);  //set page
        Set_Column_Address(0x00);
		for(j=0; j<96; j++)     //clear all columns upto 130    
		OLED_M_data(0x00);   
    }
    
    OLED_M_command(SSD1306_DISPLAYON);
}

void ssd1306_fill()
{
    unsigned char i,j;

    OLED_M_command(SSD1306_DISPLAYOFF);
    
	for(i=0; i<5; i++)       //clear page 0~8
	{
        Set_Page_Address(i);  //set page
        Set_Column_Address(0x00);
		for(j=0; j<96; j++)     //clear all columns upto 130    
		OLED_M_data(0xFF);   
    }
    
    OLED_M_command(SSD1306_DISPLAYON);

}


//Display picture for Page Addressing Mode
void Display_Picture(unsigned char pic[])
{
    unsigned char i,j=0;
    
    for(i=0;i<0x05;i++)
    {
        Set_Page_Address(i);
        Set_Column_Address(0x00);

        for(j=0;j<0x60;j++)
        {
            OLED_M_data(pic[i*0x60+j]);
        }
    }
}
//Set contrast control
void contrast_control(unsigned char temp){
        OLED_M_command(SSD1306_SETCONTRAST);           //0x81   Set Contrast Control
        OLED_M_command(temp);                          // contrast step 1 to 256
}

void startscroll_Right(unsigned char x, unsigned char y){
       OLED_M_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);      //0x26  Right Horizontal scroll
       OLED_M_command(0X00);                                 //dummy byte
       OLED_M_command(x);                                    //define start page address
       OLED_M_command(0X00);                                 //Set time interval between each scroll
       OLED_M_command(y);                                    //Define end page address
       OLED_M_command(0X00);                                 //dummy byte
       OLED_M_command(0XFF);                                 //dummy byte
       OLED_M_command(SSD1306_ACTIVATE_SCROLL);
}

void startscroll_Left(unsigned char x, unsigned char y){
       OLED_M_command(SSD1306_LEFT_HORIZONTAL_SCROLL);       //0x27  Right Horizontal scroll
       OLED_M_command(0X00);                                 //dummy byte
       OLED_M_command(x);                                    //define start page address
       OLED_M_command(0X00);                                 //Set time interval between each scroll
       OLED_M_command(y);                                    //Define end page address
       OLED_M_command(0X00);                                 //dummy byte
       OLED_M_command(0XFF);                                 //dummy byte
       OLED_M_command(SSD1306_ACTIVATE_SCROLL);              //0x2F Activate scroll
}

void startscroll_DiagRight(unsigned char x, unsigned char y){
       OLED_M_command(SSD1306_SET_VERTICAL_SCROLL_AREA);              //0xA3 Set Vertical Scroll Area
       OLED_M_command(0X00);                                          //Set No. of rows in top fixed area
       OLED_M_command(SSD1306_LCDHEIGHT);                             //Set No. of rows in scroll area
       OLED_M_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);  //0x29 Vertical and Right Horizontal Scroll
       OLED_M_command(0X00);                                          //dummy byte
       OLED_M_command(x);                                             //Define start page address
       OLED_M_command(0X00);                                          //Set time interval between each scroll
       OLED_M_command(y);                                             //Define end page address
       OLED_M_command(0X01);                                          //Vertical scrolling offset
       OLED_M_command(SSD1306_ACTIVATE_SCROLL);                       //0x2F Activate scroll
}

void startscroll_DiagLeft(unsigned char x, unsigned char y){
       OLED_M_command(SSD1306_SET_VERTICAL_SCROLL_AREA);              //0xA3 Set Vertical Scroll Area
       OLED_M_command(0X00);                                          //Set No. of rows in top fixed area
       OLED_M_command(SSD1306_LCDHEIGHT);                             //Set No. of rows in scroll area
       OLED_M_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);   //0x2A Vertical and Right Horizontal Scroll
       OLED_M_command(0X00);                                          //dummy byte
       OLED_M_command(x);                                             //Define start page address
       OLED_M_command(0X00);                                          //Set time interval between each scroll
       OLED_M_command(y);                                             //Define end page address
       OLED_M_command(0X01);                                          //Vertical scrolling offset
       OLED_M_command(SSD1306_ACTIVATE_SCROLL);                       //2F Activate scroll
}

void scroll_STOP(void){
     OLED_M_command(0x2E);    //0x2E deactivate scroll
}

void set_pos(uint8_t x, uint8_t y)
{
	Set_Page_Address(y);
	Set_Column_Address(x);
}


















