
#include "mbed.h"
#include "ssd1306.h"
#include "standard_font.h"

#include <stdarg.h>



SSD1306::SSD1306(PinName cs, PinName rs, PinName dc, PinName clk, PinName data)
    : _spi(data, NC, clk), 
      _cs(cs), 
      _reset(rs), 
      _dc(dc)
{
}

void SSD1306::off()
{
    oled_command(0xAE);
}

void SSD1306::on()
{
    oled_command(0xAF);
}


void SSD1306::start_horizontal_scroll(unsigned char direction, unsigned char start, unsigned char end, unsigned char interval) 
{
    oled_command(direction ? 0x27 : 0x26);
    oled_command(0x00);
    oled_command(start & 0x05);
    switch (interval) {
        case   2: oled_command(0x07); break; // 111b
        case   3: oled_command(0x04); break; // 100b
        case   4: oled_command(0x05); break; // 101b
        case   5: oled_command(0x00); break; // 000b
        case  25: oled_command(0x06); break; // 110b
        case  64: oled_command(0x01); break; // 001b
        case 128: oled_command(0x02); break; // 010b
        case 255: oled_command(0x03); break; // 011b
        default:
            // default to 2 frame interval
            oled_command(0x07); break;
    }
    oled_command(end & 0x05);
    oled_command(0x00);
    oled_command(0xFF);
    
    // activate scroll
    oled_command(0x2F);
}

void SSD1306::start_vertical_and_horizontal_scroll(unsigned char direction, unsigned char start, unsigned char end, unsigned char interval, unsigned char vertical_offset)
{
	oled_command(SSD1306_SET_VERTICAL_SCROLL_AREA);              //0xA3 Set Vertical Scroll Area
    oled_command(0X00);                                          //Set No. of rows in top fixed area
    oled_command(SSD1306_LCDHEIGHT);
    oled_command(direction ? 0x2A : 0x29);
    oled_command(0x00);
    oled_command(start & 0x05);
    switch (interval) {
        case   2: oled_command(0x07); break; // 111b
        case   3: oled_command(0x04); break; // 100b
        case   4: oled_command(0x05); break; // 101b
        case   5: oled_command(0x00); break; // 000b
        case  25: oled_command(0x06); break; // 110b
        case  64: oled_command(0x01); break; // 001b
        case 128: oled_command(0x02); break; // 010b
        case 255: oled_command(0x03); break; // 011b
        default:
            // default to 2 frame interval
            oled_command(0x07); break;
    }
    oled_command(end & 0x05);
    oled_command(vertical_offset);    
    
    // activate scroll
    oled_command(0x2F);
}

void SSD1306::stop_scroll()
{
    // all scroll configurations are removed from the display when executing this command.
    oled_command(0x2E);
}

void SSD1306::pam_set_start_address(unsigned char address)
{
	oled_command((0x10|(address>>4)));
    oled_command((0x0f&address));
}

void SSD1306::pam_set_page_start(unsigned char address)
{
	address=0xb0|address;
    oled_command(address);
}


void SSD1306::initialise()
{
    // Init
    _reset = 1;
    wait(0.01);
    _reset = 0;
    wait(0.10);
    _reset = 1;
    
    off();

    oled_command(SSD1306_DISPLAYOFF);             //0xAE  Set OLED Display Off
    oled_command(SSD1306_SETDISPLAYCLOCKDIV);     //0xD5  Set Display Clock Divide Ratio/Oscillator Frequency
    oled_command(0x80);
    oled_command(SSD1306_SETMULTIPLEX);           //0xA8  Set Multiplex Ratio
    oled_command(0x27);
    oled_command(SSD1306_SETDISPLAYOFFSET);       //0xD3  Set Display Offset
    oled_command(0x00);
    oled_command(SSD1306_SETSTARTLINE);           //0x40  Set Display Start Line
    oled_command(SSD1306_CHARGEPUMP);             //0x8D  Set Charge Pump
    oled_command(0x14);                           //0x14  Enable Charge Pump    
    oled_command(0x20);
    oled_command(2);    
    oled_command(SSD1306_COMSCANINC);             //0xC8  Set COM Output Scan Direction
    oled_command(SSD1306_SETCOMPINS);             //0xDA  Set COM Pins Hardware Configuration
    oled_command(0x12);
    oled_command(SSD1306_SETCONTRAST);            //0x81   Set Contrast Control
    oled_command(0xAF);
    oled_command(SSD1306_SETPRECHARGE);           //0xD9   Set Pre-Charge Period
    oled_command(0x25);
    oled_command(SSD1306_SETVCOMDETECT);          //0xDB   Set VCOMH Deselect Level
    oled_command(0x20);
    oled_command(SSD1306_DISPLAYALLON_RESUME);    //0xA4   Set Entire Display On/Off
    oled_command(SSD1306_NORMALDISPLAY);          //0xA6   Set Normal/Inverse Display
    oled_command(SSD1306_DISPLAYON);              //0xAF   Set OLED Display On
    
    
}



void SSD1306::putc(unsigned char c)
{
	uint8_t i = 0;

    for(i=0; i<6; i++)
    {
        oled_data(ssd1306_font[((c - 0x20) * 6) + i]);
    }
         
}

void SSD1306::printf(const char *format, ...)
{
    static char buffer[128];
    
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    
    char *c = (char *)&buffer;
    while (*c != 0)
    {
        putc(*c++);
    }
}

void SSD1306::clear()
{
    uint8_t i,j;
    
	for(i=0; i<5; i++)       //clear page 0~8
	{
        pam_set_page_start(i);  //set page
        pam_set_start_address(0x00);
		for(j=0; j<128; j++)     //clear all columns upto 130    
		oled_data(0x00);   
    }
}

void SSD1306::set_cursor(unsigned char x, unsigned char y)
{
	pam_set_start_address(x);
	pam_set_page_start(y);
}

void SSD1306::oled_command(unsigned char code)
{
    _cs = 1;
    _dc = 0;
    _cs = 0;
    _spi.write(code);
    _cs = 1;
}

void SSD1306::oled_data(unsigned char value)
{
    _cs = 1;
    _dc = 1;
    _cs = 0;
    _spi.write(value);
    _cs = 1;
}

