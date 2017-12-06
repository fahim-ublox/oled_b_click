#ifdef UIF_LCD_EXAMPLE
#include "mbed.h"
#endif
#include "lcd_implementation.h"

SSD1306 oled( SPI_NSS /*CS*/, A3 /*RS*/, D6 /*DC*/, SPI_CLK /*clk*/, SPI_MOSI /*data*/); //for UBX C030
//SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); //for FRDM K64F

#ifdef UIF_LCD_EXAMPLE
InterruptIn sw2(SW0);
//InterruptIn sw3(SW3); //not present in C030

void sw2_interrupt (void) {
    static unsigned char count;
    
    switch (count)
    {
        case 0: 
            oled.queue_put_top((unsigned char *)"Top row: first message");  
            count++;
        break;
        
        case 1:
            oled.queue_put_top((unsigned char *)"Top row: second message");
            count++;
        break;
            
        case 2:
            oled.queue_put_top((unsigned char *)"Top row: third message");
            count=0;
        break;
        
        default: 
            count=0;
        break;
        
    }  
}
/*
void sw3_interrupt (void) {
    static unsigned char count;
    
    switch (count)
    {
        case 0: 
            oled.queue_put_bottom((unsigned char *)"Bottom row: first message");  
            count++;
        break;
        
        case 1:
            oled.queue_put_bottom((unsigned char *)"Bottom row: second message");
            count++;
        break;
            
        case 2:
            oled.queue_put_bottom((unsigned char *)"Bottom row: third message");
            count=0;
        break;
        
        default: 
            count=0;
        break;
        
    } 
    
}
*/
int main() {  
    sw2.mode(PullUp);
    wait(0.1);
    sw2.fall(&sw2_interrupt);
    /*
    sw3.mode(PullUp);
    wait(0.1);
    sw3.fall(&sw3_interrupt);
    */

    oled.set_cursor(16,2);
    oled.printf("%s", "OLED CLICK");  

}
#endif
