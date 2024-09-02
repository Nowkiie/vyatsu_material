/*
 * Project name:
     ManchesterTransmitter (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20070601:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for sending data. The
     example works in conjuction with Receiver example. This node sends the
     word "mikroElektronika" using Manchester encoding.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    LCD 2x16, Superhet receiver on some household-use frequency
                      (e.g. 433MHz) - OPTIONAL
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - If you decide to try this example(s) with transmitter/receiver modules,
       make sure that both transmitter and a receiver work on the same frequency.
 */

// Manchester module connections
sbit MANRXPIN at P0_0_bit;
sbit MANTXPIN at P0_1_bit;
// End Manchester module connections

char index, character;
char s1[] = "mikroElektronika";

void main() {
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                //   disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
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
  CLKSEL = 0x01;//

  XBR2      = 0x40;

  P0MDOUT.B1 = 1;                  // Configure P0.1 (MANTXPIN) pin as push-pull

  Man_Send_Init();                 // Initialize transmitter

  while (1) {                      // Endless loop
    Man_Send(0x0B);                // Send "start" byte
    Delay_ms(100);                 // Wait for a while

    character = s1[0];             // Take first char from string
    index = 0;                     // Initialize index variable  
    while (character) {            // String ends with zero
      Man_Send(character);         // Send character
      Delay_ms(90);                // Wait for a while 
      index++;                     // Increment index variable
      character = s1[index];       // Take next char from string 
      }
    Man_Send(0x0E);                // Send "end" byte
    Delay_ms(1000);
  }
}