/*
 * Project name:
     WatchDog_Timer (Demonstration of the Watchdog Timer usage)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This code demonstrates how to work with the Watchdog timer.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
      Oscillator:     External oscillator 24.5MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn on PORT0 LEDs.
*/

void main() {
  WDTCN = 0xA7; // Enable WDT

  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC = 0x04;                  // Enable missing clock detector

  // Consult datasheet for more details about starting External oscillator
  // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                  // External Oscillator is an external
                                  // crystal (no divide by 2 stage)
  OSCXCN |= 7;

  // Step 2. Wait at least 1 ms.
  Delay_ms(5);

  // Step 3. Poll for XTLVLD => ‘1’.
  while ((OSCXCN & 0x80) != 0x80);

  // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;//

  XBR2      = 0x40;
  
  P0MDOUT = 0xFF;            // Initialize P0
  P0 = 0;

  Delay_ms(300);             // Wait 0.3 seconds
  
  P0 = 0xFF;                 // Change PORT0 value
  
  while (1)                  // endless loop, WatchDog Timer will reset MCU
  ;

}