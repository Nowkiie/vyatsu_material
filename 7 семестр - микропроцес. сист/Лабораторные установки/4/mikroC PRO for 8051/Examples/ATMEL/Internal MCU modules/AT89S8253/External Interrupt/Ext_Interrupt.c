/* Project name:
     External Interrupt on Port0 (Simple 'Hello World' project)
 * Copyright:
     (c) Mikroelektronika, 2010.
 * Revision History:
     20101007:
      - initial release;
     20110224(TL):
      - adapted for PRO version
 * Description:
     This is a simple 'Hello World' project. It counts presses on PORT3.2 and
     shows result on diodes connected to PORT0.
 * Test configuration:
     MCU:          AT89S8253
     http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.board:    Easy8051 v6
                   http://www.mikroe.com/easy8051/
     Oscillator:   HS, 10.0000 MHz
     Ext. Modules: -
     SW:           mikroC PRO for 8051
                   http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Make sure you turn ON the PORT0 LEDs (SW7.1), set Pull up PORT3.2 (SW4.3) and set jumper J4 in GND position
 */

int tmp = 0, cnt = 0xFF;                    // Global variable cnt and tmp with starting values

void External_ISR()org 0x0003 ilevel 0 {    // Interrupt rutine
  EA_bit = 0;                               // Disable Interrupts
  tmp = 1;                                  // Increment variable cnt
  EA_bit = 1;                               // Enable Interrupts
}

void main() {                               // Main program

  P0 = 0xFF;                                // Set P0 as output
  P3 = 0xFF;                                // Set P3 as input

  IE = 0x81;                                // Setting the Interrupts:

  while(1){                                 // Unending loop
    if (tmp) {                          // tmp is temporary variable that enables us to control Interrupt counting
      cnt = cnt - 1;                      // Decreasing cnt variable (negative logic)
      tmp = 0;                            // Deleting tmp variable
    }
    P0 = cnt;                             // Write on Port0 value of varibale cnt
    delay_ms(250);                         // This is needed for button debounce
  }
}