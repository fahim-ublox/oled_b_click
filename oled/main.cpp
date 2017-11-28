#include "mbed.h"
#include "ssd1306.h"


SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); 


int main()
{
    oled.initialise();
    oled.clear();

    
    oled.set_cursor(16,2);
    oled.printf("%s", "OLED CLICK");
    oled.set_cursor(10,3);    
    wait(1);
    
    while (1)
    {
       oled.write_top("This is a long text message for testing. The length of this message is 80 chars!"); 
    }
}
