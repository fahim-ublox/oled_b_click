#ifndef __SSD1306_H__
#define __SSD1306_H__

class SSD1306
{
public:
	/** Construct a new LCD object
	 *  @param cs The connected C/S pin.
     *  @param rs The connected RS pin.
     *  @param dc The connected DC pin.
     *  @param clk The connected CLK pin.
     *  @param data The connected Data pin.
     */
    SSD1306(PinName cs, PinName rs, PinName dc, PinName clk, PinName data);

	/** Initialize LCD with default configurations */
    void initialise();    

	/** Turn display off */
    void off();
    
	/** Turn display on */
    void on();

	/** Start horizontal scroll. 
      * @param direction 0 for right, 1 for left.
      * @param start Start page address, 0 - 4.
      * @param end End page address, 0 - 4.
      * @param interval Interval in frame frequency.  Valid values are: 2, 3, 4, 5, 25, 64, 128, 256.      
      */
    void start_horizontal_scroll(unsigned char direction, unsigned char start, unsigned char end, unsigned char interval);

	/** Start horizontal and vertical scroll. 
	  * @param direction 0 for vertical and right horizontal scroll, 1 for vertical and left horizontal scroll.
      * @param start Start page address, 0 - 4
      * @param end End page address, 0 - 4
      * @param interval Interval in frame frequency.  Valid values are: 2, 3, 4, 5, 25, 64, 128, 256.
      * @param vertical_offset Offset of vertical scroll, 1 - 39.
	  */
    void start_vertical_and_horizontal_scroll(unsigned char direction, unsigned char start, unsigned char end, unsigned char interval, unsigned char vertical_offset);
    
	/** stop scrolling */
    void stop_scroll();
    
	/** set column address  
	 *  @param address Start column address, 0 - 96
	 */
    void pam_set_start_address(unsigned char address);       
    
	/** set row address  
	 *  @param address Start column address, 0 - 96
	 */
    void pam_set_page_start(unsigned char address);    
        
		    
	/** Put one character on LCD */
    void putc(unsigned char c);
    
	/** Put formatted string on LCD */
    void printf(const char *format, ...);
	
	/** move cursor to desire position, x: 0-96, y: 0-4 */
	void set_cursor(unsigned char x, unsigned char y);
	
	/** clear all display */
	void clear();
	
private:
    SPI _spi;
    DigitalOut _cs, _reset, _dc;

    void oled_command(unsigned char code);
    void oled_data(unsigned char value);

};

/* LCD controller commands */
#define SSD1306_96_39
#define SSD1306_LCDWIDTH                  96
#define SSD1306_LCDHEIGHT                 40

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

#endif
