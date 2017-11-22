
#ifndef __MAIN_H
#define __MAIN_H

#include "MK64F12.h"
#include "oled.h"


/* k64f MCU pin macros*/
#define PIN_DC          0
#define PIN_RST         1
#define PIN_CS          2

#define PPORT_C         0
#define PPORT_D         1





/* gpio set clear functions */                
void Delay_ms(__IO uint32_t nTime);
void pin_clear (unsigned int idx, unsigned int pin);
void pin_set (unsigned int idx, unsigned int pin);




























#endif
