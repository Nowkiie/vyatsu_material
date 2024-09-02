/*
 * Project name:
     ManchesterTransmitter (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for sending data. The
     example works in conjuction with Receiver example. This node sends the
     word "mikroElektronika" using Manchester encoding.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    none.
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