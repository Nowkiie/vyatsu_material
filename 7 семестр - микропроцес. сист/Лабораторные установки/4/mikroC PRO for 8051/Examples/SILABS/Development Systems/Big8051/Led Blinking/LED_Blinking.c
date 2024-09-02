/*
 * Project name:
     LED_Blinking (Simple 'Hello World' project)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This is a simple 'Hello World' project. It turns on/off diodes connected to
     PORT1.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:LED
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn ON the PORT LEDs (SW9).
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


   P0MDOUT |= 0xFF;                   // PORT as a push-pull output
   P1MDOUT |= 0xFF;                   // PORT as a push-pull output
   P2MDOUT |= 0xFF;                   // PORT as a push-pull output
   P3MDOUT |= 0xFF;                   // PORT as a push-pull output
   P4MDOUT |= 0xFF;                   // PORT as a push-pull output
   P5MDOUT |= 0xFF;                   // PORT as a push-pull output
   P6MDOUT |= 0xFF;                   // PORT as a push-pull output
   P7MDOUT |= 0xFF;                   // PORT as a push-pull output

   XBR1 = 0x00;                       // Don't Route /SYSCLK to a port pin
   XBR2 = 0x40;                       // Enable crossbar and weak pull-ups


  do {
    P0 = 0x00;                        // Turn OFF diodes as PORT1
    P1 = 0x00;                        // Turn OFF diodes as PORT1
    P2 = 0x00;                        // Turn OFF diodes as PORT1
    P3 = 0x00;                        // Turn OFF diodes as PORT1
    P4 = 0x00;                        // Turn OFF diodes as PORT1
    P5 = 0x00;                        // Turn OFF diodes as PORT1
    P6 = 0x00;                        // Turn OFF diodes as PORT1
    P7 = 0x00;                        // Turn OFF diodes as PORT1

    Delay_ms(1000);                   // 1 second delay
    
    P0 = 0xFF;                        // Turn ON diodes as PORT1
    P1 = 0xFF;                        // Turn ON diodes as PORT1
    P2 = 0xFF;                        // Turn ON diodes as PORT1
    P3 = 0xFF;                        // Turn ON diodes as PORT1
    P4 = 0xFF;                        // Turn ON diodes as PORT1
    P5 = 0xFF;                        // Turn ON diodes as PORT1
    P6 = 0xFF;                        // Turn ON diodes as PORT1
    P7 = 0xFF;                        // Turn ON diodes as PORT1

    Delay_ms(1000);                   // 1 second delay

  } while(1);                         // Endless loop
}