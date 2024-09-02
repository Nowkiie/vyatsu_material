/*
 * Project name:
     ManchesterReceiver (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20070601:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for receiving data. The
     example works in conjuction with Transmitter example which sends the word
     "mikroElektronika" using Manchester encoding. During the receive process,
     message letters are being written on the UART.
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
sbit MANRXPIN at P0_2_bit;
sbit MANTXPIN at P0_3_bit;
// End Manchester module connections

char error, ErrorCount, temp;

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
  P0MDOUT.B0 = 1;                  // Configure P0.0 (TX) pin as push-pull

  UART1_Init(4800);               // Initialize UART module at 4800 bps
  Delay_ms(100);                  // Wait for UART module to stabilize


  ErrorCount = 0;
  Man_Receive_Init();                             // Initialize Receiver
  
  while (1) {                                     // Endless loop

      while (1) {                                 // Wait for the "start" byte
        temp = Man_Receive(&error);               // Attempt byte receive 
        if (temp == 0x0B)                         // "Start" byte, see Transmitter example
          break;                                  // We got the starting sequence
        if (error)                                // Exit so we do not loop forever
          break;
        }
        
      do
        {
          temp = Man_Receive(&error);             // Attempt byte receive
          if (error) {                            // If error occured
            UART1_Write('?');                      // Write question mark on LCD
            ErrorCount++;                         // Update error counter
            if (ErrorCount > 20) {                // In case of multiple errors
              temp = Man_Synchro();               // Try to synchronize again
              //Man_Receive_Init();               // Alternative, try to Initialize Receiver again
              ErrorCount = 0;                     // Reset error counter
              }
            }
          else {                                  // No error occured
            if (temp != 0x0E)                     // If "End" byte was received(see Transmitter example)
              UART1_Write(temp);                   //   do not write received byte on LCD
              }
          Delay_ms(25);
        }
      while (temp != 0x0E) ;                      // If "End" byte was received exit do loop
   }
}