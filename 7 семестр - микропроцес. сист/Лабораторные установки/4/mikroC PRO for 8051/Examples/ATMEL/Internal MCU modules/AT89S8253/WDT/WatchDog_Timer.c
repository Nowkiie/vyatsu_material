/*
 * Project name:
     WatchDog_Timer (Demonstration of the Watchdog Timer usage)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This code demonstrates how to work with the Watchdog timer.
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
     - Turn on PORT0 LEDs.
*/

void main() {

  P0 = 0x0F;            // Initialize P0
  
  WDTCON = 0b11111001;  // Enable WatchDog Timer, set prescaller bits to 111
  Delay_ms(300);        // Wait 0.3 seconds
  
  P0 = 0xF0;            // Change PORT0 value
  
  while (1)             // endless loop, WatchDog Timer will reset MCU
    ;
}
