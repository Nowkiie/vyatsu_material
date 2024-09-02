/*
 * Project name:
     Button (Demonstration of using Button Library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This program demonstrates usage on-board button as PORT3 input.
     On every P3.7 one-to-zero transition P1.6 is inverted.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:Buttons
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

// Button connections
sbit Button_Pin at P3_7_bit;        // Declare Button_Pin. It will be used by Button Library.
// End Button connections

bit oldstate;                       // Old state flag

void main(){


  WDTCN    = 0xDE;                               // Sequence for
  WDTCN    = 0xAD;                               // disabling the watchdog timer



  OSCICN = 0x83;                                 // Configure internal oscillator for
                                                 // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                 // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                // External Oscillator is an external
                                                 // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;

   XBR2 = 0x40;                                  // Enable crossbar and weak pull-ups


  P1MDOUT.B6 = 1;     // Configure P1.6 pins as push-pull output

  P3 = 255;                         // Configure PORT3 as input
  P1_6_bit = 1;                     // Initial P1.6 value
  oldstate = 0;

  do {
    if (Button(1, 1))               // Detect logical one
      oldstate = 1;                 // Update flag
    if (oldstate && Button(1, 0)) { // Detect one-to-zero transition
      P1_6_bit = ~P1_6_bit;         // Invert P1.6
      oldstate = 0;                 // Update flag
    }
  } while(1);                       // Endless loop
}