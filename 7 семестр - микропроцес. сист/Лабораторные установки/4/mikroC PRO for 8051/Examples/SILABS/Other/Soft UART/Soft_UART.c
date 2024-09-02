/*
 * Project name:
     Soft_UART (Demonstration of using Soft UART library routines) 
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code demonstrates how to use software UART library routines.
     Upon receiving data via RS232, MCU immediately sends it back to the sender.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    -                                                                          
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

// Soft UART connections
sbit Soft_Uart_RX at P0_1_bit;
sbit Soft_Uart_TX at P0_0_bit;
// End Soft UART connections

sbit ErrorSignal at P1_6_bit;

char i, error, byte_read;                 // Auxiliary variables

void main(){
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
  P1MDOUT.B6 = 1;     // Configure P1.6 pins as push-pull output

  ErrorSignal = 0;                        // P2 is used for error signalization : No error

  error = Soft_UART_Init(9600, 0);        // Initialize Soft UART at 9600 bps

  if (error > 0) {
    ErrorSignal = 1;                      // Signalize Init error
    while(1) ;                            // Stop program
  }
  Delay_ms(100);

  for (i = 'z'; i >= 'A'; i--) {          // Send bytes from 'z' downto 'A'
    Soft_UART_Write(i);
    Delay_ms(100);
  }
   
  while(1) {                              // Endless loop
    byte_read = Soft_UART_Read(&error);   // Read byte, then test error flag
    if (error)                            // If error was detected
      ErrorSignal = 1;                    //   signal it
    else
      Soft_UART_Write(byte_read);         // If error was not detected, return byte read
    }
}