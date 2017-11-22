/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Example application for OLED B Click using FRDM-K64F board
 *----------------------------------------------------------------------------*/

#include "MK64F12.h"
#include "main.h"

/* k64F SPI config macros */
#define SPI_PUSHR_PCS0_ON   0x10000
#define SPI_PUSHR_PCS1_ON   0x20000
#define SPI_PUSHR_PCS2_ON   0x40000
#define SPI_PUSHR_PCS3_ON   0x80000
#define SPI_PUSHR_PCS4_ON   0x100000
#define SPI_PUSHR_PCS5_ON   0x200000
#define SPI_CTAR_FMSZ_8BIT  0x38000000
#define SPI_CTAR_FMSZ_16BIT 0x78000000



volatile uint32_t G_TimingDelay;
extern unsigned char pic[];
extern uint8_t ssd1306_font[];

/* k64F GPIO config */
const unsigned int pin_mask[] = { 1UL << 4,
                              1UL << 12,
                              1UL << 0 };

GPIO_Type * port_mask[]    = { PTC,
                              PTD
                               };



/*----------------------------------------------------------------------------
  Function that initializes GPIO
 *----------------------------------------------------------------------------*/
void gpio_init(void) {

  SIM->SCGC5     |= ( (1UL <<  12) | (1UL <<  11) );                   /* Enable Port C Clock */
  PORTC->PCR[4]   = (1UL <<  8);                    /* PTC4 is DC pin     */
  PORTC->PCR[12]  = (1UL <<  8);                    /* PTC12 is RST pin     */
  PORTD->PCR[0]   = (1UL <<  8);                    /* PTD0 is CS pin     */

  /* Switch LEDs off and enable output                                        */
  PTC->PDOR = (pin_mask[PIN_DC] | pin_mask[PIN_RST]);
  PTD->PDOR = pin_mask[PIN_CS];
    
  PTC->PDDR = (pin_mask[PIN_RST] | pin_mask[PIN_DC]);
  PTD->PDDR = pin_mask[PIN_CS];
}

/*----------------------------------------------------------------------------
  Function that clears a pin
 *----------------------------------------------------------------------------*/
void pin_clear (unsigned int idx, unsigned int pin) {
   port_mask[idx]->PCOR = pin_mask[pin];  
}

/*----------------------------------------------------------------------------
  Function that sets a pin
 *----------------------------------------------------------------------------*/
void pin_set (unsigned int idx, unsigned int pin) {
    port_mask[idx]->PSOR = pin_mask[pin];  
}

/*----------------------------------------------------------------------------
  SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
  if (G_TimingDelay != 0x00)
  { 
    G_TimingDelay--;
  }
}

/* Function to create 1ms delay using Systick*/
void Delay_ms(__IO uint32_t nTime)
{ 
    G_TimingDelay = nTime;

    while(G_TimingDelay != 0)
    {}
}

/* SPI write byte function */
void SPI0_Write(unsigned char temp){
   
  SPI0_MCR |=  SPI_MCR_HALT_MASK;
  SPI0_MCR |= (SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK); //flush the fifos
  SPI0_SR  |= (SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK); //clear the status bits (write-1-to-clear)
  SPI0_TCR |= SPI_TCR_SPI_TCNT_MASK;
  SPI0_MCR &=  ~SPI_MCR_HALT_MASK;
      
  SPI0_PUSHR = (SPI_PUSHR_CONT_MASK | SPI_PUSHR_PCS0_ON | temp);
  while(!(SPI0_SR & SPI_SR_TCF_MASK));
    
}



/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) {

    int i=0x00 /*, scroll*/;
    
    SystemCoreClockUpdate ();                 /* Update system core clock       */
    SysTick_Config(SystemCoreClock/1000);     /* Generate interrupt each 1 ms  */
    gpio_init();                              /* RST DC Initialization             */
    
    //configure ports
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // Enable PORT clock gating ctrl
    SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;
    
    
    //PORT D
    PORTD_PCR(0) = PORT_PCR_MUX(2); //PCS0
    PORTD_PCR(1) = PORT_PCR_MUX(2); //SCK
    PORTD_PCR(2) = PORT_PCR_MUX(2); //SOUT
    PORTD_PCR(3) = PORT_PCR_MUX(2); //SIN
    
    
    // Clear all registers
    SPI0_SR = (SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK); //clear the status bits (write-1-to-clear)
    SPI0_TCR = 0;
    SPI0_RSER = 0;
    SPI0_PUSHR = 0; //Clear out PUSHR register. Since DSPI is halted, nothing should be transmitted
    SPI0_CTAR0 = 0;
    
    
    // configure registers
    SPI0_MCR |= SPI_MCR_MSTR_MASK | SPI_MCR_PCSIS_MASK;
    SPI0_MCR &= (~SPI_MCR_DIS_RXF_MASK & ~SPI_MCR_DIS_TXF_MASK); // enable FIFOs
    SPI0_MCR &=  (~SPI_MCR_MDIS_MASK & ~SPI_MCR_HALT_MASK); //enable SPI and start transfer
    SPI0_CTAR0 |=  SPI_CTAR_FMSZ_8BIT | SPI_CTAR_CPOL_MASK | SPI_CTAR_CPHA_MASK | SPI_CTAR_BR(6); // 8 bits, 500khz at 120Mhz
    
    OLED_M_Init();   
    
    while(1){

       Display_Picture(pic);
       Delay_ms(2000);
       OLED_M_command(SSD1306_INVERTDISPLAY);
       Delay_ms(2000);
       OLED_M_command(SSD1306_NORMALDISPLAY);
       Delay_ms(2000);

       for(i=0xAF; i>0x00; i--){
                                contrast_control(i);
                                Delay_ms(20);
       }
       for(i=0x00; i<0xAF; i++){
                                contrast_control(i);
                                Delay_ms(20);
       }
       startscroll_Right(0x00, 0x05);
       Delay_ms(3000);
       scroll_STOP();
       Display_Picture(pic);
       
       
       startscroll_Left(0x00, 0x05);
       Delay_ms(3000);
       scroll_STOP();
       Display_Picture(pic);
       
       startscroll_DiagRight(0x00, 0x05);
       Delay_ms(3000);
       scroll_STOP();
       Display_Picture(pic);

       startscroll_DiagLeft(0x00, 0x05);
       Delay_ms(3000);
       scroll_STOP();
    }  
}



//*****************************************************************************************************************************************

