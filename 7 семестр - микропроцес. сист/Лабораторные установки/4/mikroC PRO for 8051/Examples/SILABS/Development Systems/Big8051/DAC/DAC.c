/*
 * Project name:
     DAC (Demonstration of using the on-chip 12-bit DA converters)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This project is a simple demonstration of using the on-chip 12-bit DA converters.
     Use the voltmeter to measeure the output of DAC0 and DAC1 converters.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:DAC
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - SW14.7 - ON (VREF = VREFD)
*/

unsigned int i, value;

void main(){

  WDTCN    = 0xDE;                     // Sequence for
  WDTCN    = 0xAD;                     // disabling the watchdog timer

  OSCICN = 0x83;                       // Configure internal oscillator for
                                       // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                       // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                      // External Oscillator is an external
                                       // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//



  REF0CN |= 0x03;                      // Internal Reference Buffer On(2.4V)
                                       // Internal voltage reference is driven on the VREF pin
                                       // Internal Bias Generator On


  DAC0CN = 0x80;                       // Enable DAC1(12Bit) in right-justified mode
                                       // DAC output updates occur on a write to DAC1H
                                       // The most significant nibble of the DAC1 Data Word is in DAC1H[3:0],
                                       // while the least significant byte is in DAC1L


  DAC1CN = 0x80;                       // Enable DAC1(12Bit) in right-justified mode
                                       // DAC output updates occur on a write to DAC1H
                                       // The most significant nibble of the DAC1 Data Word is in DAC1H[3:0],
                                       // while the least significant byte is in DAC1L


  value = 0;



  while (1) {                          // Endless loop

    if (value < 4095) {
       value++;                        // Increment value
    }
    else {
      Delay_ms(500);
      value = 0;
    }

    DAC0L = value;                     // Send value to DAC0
    DAC0H = value >> 8;
    DAC1L = value;                     // Send value to DAC1
    DAC1H = value >> 8;

    Delay_ms(1);                       // Slow down key repeat pace

  }

}