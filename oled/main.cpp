#include "mbed.h"
#include "ssd1306.h"
#include "rtos.h"

SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); 
InterruptIn sw2(SW2);

Thread scroll_top_thread;
Thread scroll_bot_thread;

unsigned char message_top[256]={0x00};
unsigned char message_bottom[256]={0x00};

Queue<unsigned char, 256> queue_msg_top;
Queue<unsigned char, 256> queue_msg_bottom;




void oled_write_top() {    
    osEvent evt = queue_msg_top.get();
    while (true) {
        if (evt.status == osEventMessage) {
            unsigned char *temp_msg = (unsigned char*)evt.value.p;
            strcpy((char*)message_top, (const char*)temp_msg);
        }        
    	oled.write_top((const char*)message_top);
    }
}

void oled_write_bottom() {
    while (true) {
    	oled.write_bottom("Writing on both rows is implemented through mbed rtos threading");
    }
}

void sw1_interrupt (void) {
    unsigned char temp_buffer[256]={0x00};
    static unsigned char count;
    
    switch (count)
    {
        case 0: 
            strcpy((char*)temp_buffer, (const char*)"first message for top row");
            count++;
        break;
        
        case 1:
            strcpy((char*)temp_buffer, (const char*)"second message put into queue");
            count++;
        break;
            
        case 2:
            strcpy((char*)temp_buffer, (const char*)"third message put into queue");
            count=0;
        break;
        
        default: 
            count=0;
        break;
        
    } 
    queue_msg_top.put(temp_buffer);  
}

int main() {  
    sw2.mode(PullUp);
    wait(0.1);
    sw2.fall(&sw1_interrupt);
    
    oled.initialise();
    oled.clear();
    oled.set_cursor(16,2);
    oled.printf("%s", "OLED CLICK");  

    scroll_top_thread.start(oled_write_top);
    scroll_bot_thread.start(oled_write_bottom);
}
