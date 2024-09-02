/*
 * Project name:
     ManchesterReceiver (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for receiving data. The
     example works in conjuction with Transmitter example which sends the word
     "mikroElektronika" using Manchester encoding. During the receive process,
     message letters are being written on the LCD.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    LCD 2x16, Superhet receiver on some household-use frequency
                      (e.g. 433MHz) - OPTIONAL
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - If you decide to try this example(s) with transmitter/receiver modules,
       make sure that both transmitter and a receiver work on the same frequency.
     - Turn on LCD backlight switch on development board.
 */

// LCD module connections
sbit LCD_RS at P2_0_bit;
sbit LCD_EN at P2_1_bit;

sbit LCD_D4 at P2_2_bit;
sbit LCD_D5 at P2_3_bit;
sbit LCD_D6 at P2_4_bit;
sbit LCD_D7 at P2_5_bit;
// End LCD module connections

// Manchester module connections
sbit MANRXPIN at P0_0_bit;
sbit MANTXPIN at P0_1_bit;
// End Manchester module connections

char error, ErrorCount, temp;

void main() {
  ErrorCount = 0;
  Lcd_Init();                                     // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);                            // Clear LCD display

  Man_Receive_Init();                             // Initialize Receiver
  
  while (1) {                                     // Endless loop

      Lcd_Cmd(_LCD_FIRST_ROW);                    // Move cursor to the 1st row
       
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
            Lcd_Chr_CP('?');                      // Write question mark on LCD
            ErrorCount++;                         // Update error counter
            if (ErrorCount > 20) {                // In case of multiple errors
              temp = Man_Synchro();               // Try to synchronize again
              //Man_Receive_Init();               // Alternative, try to Initialize Receiver again
              ErrorCount = 0;                     // Reset error counter
              }
            }
          else {                                  // No error occured
            if (temp != 0x0E)                     // If "End" byte was received(see Transmitter example)
              Lcd_Chr_CP(temp);                   //   do not write received byte on LCD
              }
          Delay_ms(25);
        }
      while (temp != 0x0E) ;                      // If "End" byte was received exit do loop
   }
}