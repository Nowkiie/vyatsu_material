/*
 * Project name:
     Soft_UART (Demonstration of using Soft UART library routines) 
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code demonstrates how to use software UART library routines.
     Upon receiving data via RS232, MCU immediately sends it back to the sender.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn ON RX and TX UART switches (SW8.5 and SW8.6).
     - Turn ON PORT2 LEDs.
*/

// Soft UART connections
sbit  Soft_Uart_RX at P3_0_bit;
sbit  Soft_Uart_TX at P3_1_bit;
// End Soft UART connections

char i, error, byte_read;                 // Auxiliary variables

void main(){

  P2 = 0;                                 // P2 is used for error signalization : No error

  error = Soft_UART_Init(4800, 0);        // Initialize Soft UART at 4800 bps

  if (error > 0) {
    P2 = error;                           // Signalize Init error
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
      P2 = error;                         //   signal it on P2
    else
      Soft_UART_Write(byte_read);         // If error was not detected, return byte read
    }      
}