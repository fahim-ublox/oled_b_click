#include "mbed.h"
#include "ssd1306.h"


SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); 


int main()#include "mbed.h"
#include "ssd1306.h"
#include "rtos.h"

SSD1306 oled(PTD0, PTC12, PTC4, PTD1, PTD2); 
InterruptIn sw2(SW2);

Thread t1;
Thread t2;
Thread t3;

unsigned char message_top[256]={0x00};
unsigned char message_bottom[256]={0x00};

Queue<unsigned char, 256> queue_msg_top;
Queue<unsigned char, 256> queue_msg_bottom;

osEvent evt_top;
osEvent evt_bottom;

void oled_write_top() {    
    while (true) { 
        evt_top = queue_msg_top.get(0);
           
        if (evt_top.status == osEventMessage) {
            unsigned char *temp_msg = (unsigned char*)evt_top.value.p;
            strcpy((char*)message_top, (const char*)temp_msg);
        }   
        if (message_top[0])    
        {
            oled.write_top((const char*)message_top);
        }
    }
}

void oled_write_bottom() {
    while (true) {
        evt_bottom = queue_msg_bottom.get(0);
           
        if (evt_bottom.status == osEventMessage) {
            unsigned char *temp_msg = (unsigned char*)evt_bottom.value.p;
            strcpy((char*)message_bottom, (const char*)temp_msg);
        }   
        if (message_bottom[0])    
        {   
            oled.write_bottom((const char*)message_bottom);
        }
    }
}


void sw1_interrupt (void) {
    unsigned char temp_buffer[256]={0x00};
    static unsigned char count;
    
    switch (count)
    {
        case 0: 
            strcpy((char*)temp_buffer, (const char*)"first message for top row");
            queue_msg_bottom.put((unsigned char*)"Bottom row first message"); 
            count++;
        break;
        
        case 1:
            strcpy((char*)temp_buffer, (const char*)"second message put into queue");
            queue_msg_bottom.put((unsigned char*)"Bottom row second message");
            count++;
        break;
            
        case 2:
            strcpy((char*)temp_buffer, (const char*)"third message put into queue");
            queue_msg_bottom.put((unsigned char*)"Bottom row third message");
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

    t1.start(oled_write_top);
    t2.start(oled_write_bottom);
}
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
