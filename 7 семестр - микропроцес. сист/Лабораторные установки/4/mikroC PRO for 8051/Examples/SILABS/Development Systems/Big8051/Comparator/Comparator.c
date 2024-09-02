/*
 * Project name:
     Comparator (Demonstration of using the MCU's comparator)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This project is a simple demonstration of how to use the on-chip comparator module.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:Comparator
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
    - SW15.5, SW15.6 - ON
    - Turn on P0 and P3 LEDs (SW9.1, SW9.1, - ON)
*/



void main() {

  WDTCN    = 0xDE;                    // Sequence for
  WDTCN    = 0xAD;                    // disabling the watchdog timer



  OSCICN = 0x83;                      // Configure internal oscillator for
                                      // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                      // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                     // External Oscillator is an external
                                      // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);


   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//


   P2MDIN   = 0xC0;                   // P2.6 and P2.7 set as analog inputs
   P2MDOUT = 0x3F;
   P2 = 0xC0;
   
   CPT0CN = 0x83;                     // Comparator0 enabled
   P0MDOUT |= 0xFF;                   // Enable LED as a push-pull output
   P3MDOUT |= 0xFF;                   // Enable LED as a push-pull output

   XBR0     = 0x00;                   // No clockout
   XBR1     = 0x00;                   // No peripherals selected
   XBR2     = 0x40;                   // Enable crossbar and weak pullups

   P0 = 0x00;                         // Turn OFF LEDs at PORT0
   P3 = 0x00;                         // Turn OFF LEDs at PORT3

 while(1){

 if (CP0OUT_bit){
    P0 = 0;                           // Turn OFF LEDs at PORT0
    P3 = 0xFF;                        // Turn ON LEDs at PORT3
   }
  else
  {
    P0 = 0xFF;                        // Turn ON LEDs at PORT0
    P3 = 0;                           // Turn OFF LEDs at PORT3
   }

  Delay_ms(300);
 }

}