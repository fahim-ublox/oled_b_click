#include "mbed.h"
#include "ssd1306.h"


SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); 


int main()
{
    oled.initialise();
    oled.clear();

    oled.set_cursor(0,0);
    oled.printf("%s", "OLED CLICK");
    oled.set_cursor(10,2);
    oled.printf("%s","   Display ");
    oled.set_cursor(15,3);
    oled.printf("%s","   TEST  ");	
	oled.start_horizontal_scroll(0, 0, 1, 5);
    while (1)
    {

    }
}
