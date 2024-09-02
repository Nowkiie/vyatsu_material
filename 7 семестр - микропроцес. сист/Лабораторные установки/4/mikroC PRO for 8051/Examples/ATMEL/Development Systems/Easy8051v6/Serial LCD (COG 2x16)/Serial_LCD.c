/*
 * Project name:
     SPI_Lcd_COG_2x16 (Simple demonstration of the SPI Lcd 4-bit Library functions)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a simple demonstration of SPI Lcd library functions.
     SPI Lcd Library sends commands to Port Expander and it controls
     Port Expander's output (connected to Serial LCD).
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6 - ac:COG_2X16
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    none
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn on Port Expander switches SW6.2, SW6.3, SW6.4, SW6.5 and SW6.6.
     - Turn on COG LCD 2x16 switches SW9.
*/

char *text = "www.mikroe.com";

// Port Expander module connections
sbit  SPExpanderCS  at P3_4_bit;
sbit  SPExpanderRST at P3_7_bit;
// End Port Expander module connections

char i;                                     // Loop variable

void Move_Delay() {                         // Function used for text moving
  Delay_ms(500);                            // You can change the moving speed here
}

void main() {


// Port Expander Library uses SPI1 module
  SPI1_Init();                              // Initialize SPI module used with PortExpander

  SPI_Lcd_Config(0);                        // Initialize Lcd over SPI interface
  SPI_Lcd_Cmd(_LCD_CLEAR);                  // Clear display
  SPI_Lcd_Cmd(_LCD_CURSOR_OFF);             // Turn cursor off
  SPI_Lcd_Out(1,1, "mikroElektronika");     // Print text to Lcd, 1st row, 1st column
  SPI_Lcd_Out(2,2, text);                   // Print text to Lcd, 2nd row, 2nd column

  Delay_ms(2000);

// Moving text
  for(i=0; i<4; i++) {                      // Move text to the right 4 times
    SPI_Lcd_Cmd(_LCD_SHIFT_RIGHT);
    Move_Delay();
  }

  while(1) {                                // Endless loop
    for(i=0; i<8; i++) {                    // Move text to the left 7 times
      SPI_Lcd_Cmd(_LCD_SHIFT_LEFT);
      Move_Delay();
    }

    for(i=0; i<8; i++) {                    // Move text to the right 7 times
      SPI_Lcd_Cmd(_LCD_SHIFT_RIGHT);
      Move_Delay();
    }
  }
}