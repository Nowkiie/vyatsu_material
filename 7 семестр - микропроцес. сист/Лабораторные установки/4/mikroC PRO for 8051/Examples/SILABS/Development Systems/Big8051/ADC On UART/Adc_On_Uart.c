/*
 * Project name:
     Adc_On_UART;
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     A simple example of using the on-chip ADC module.
     ADC results are being sent to PC via UART.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:ADC
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - VREF0 = VREF (SW14.8 - ON)
*/


void ADC1_Init() {
   REF0CN = 0x03;                                  // Internal Vref, internal bias on

   ADC0CN = 0x00;                                  // ADC0 disabled; normal tracking
                                                   // mode; ADC0 data is right-justified
   AMX0CF = 0x00;                                  // AIN inputs are single-ended
   AMX0SL = 0x00;                                  // Select AIN0.0 pin as ADC mux input
   ADC0CF = 0b11111000;                            // Default settings
}


unsigned AIN0_0_Get_Sample(){
  unsigned volatile temp;

  ADC0CN.AD0INT = 0;                               // Clear ADOINT flag
  ADC0CN |= 0x90;                                  // ADC enable, Start conversion
  while (ADC0CN.AD0INT == 0)
    ;

  temp = ADC0L;
  return temp | (ADC0H << 8);
}


unsigned int adc_result;
char txt[6];

void main(){

  WDTCN    = 0xDE;                                 // Sequence for
  WDTCN    = 0xAD;                                 // disabling the watchdog timer

  OSCICN = 0x83;                                   // Configure internal oscillator for
                                                   // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                   // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                  // External Oscillator is an external
                                                   // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//



   XBR0 = 0x04;
   XBR1 = 0x00;
   XBR2 = 0x40;                                    // Enable crossbar and weak pull-ups

   P0MDOUT |= 0x01;                                // Configure P0.0 (TX) pin as push-pull

   UART1_Init(4800);                               // Initialize UART2
   Delay_ms(100);

   ADC1_Init();                                    // Initialize ADC2 module
   Delay_ms(100);

  while (1) {
    adc_result = AIN0_0_Get_Sample();              // Read AIN0.0 analog input
    WordToStr(adc_result, txt);                    // convert result to string
    UART1_Write_Text(txt);                         // send string to UART
    UART1_Write(13);                               // send new line (CR+LF)
    UART1_Write(10);
    Delay_ms(500);
  }

}