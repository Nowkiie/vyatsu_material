/*
 * Project name:
     Spi_Lcd8 (Simple demonstration of the SPI Lcd 8-bit interface library)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a simple demonstration of SPI Lcd 8-bit library functions.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:Serial_LCD_2x16_Adapter_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

char *text = "mikroElektronika";

// Port Expander module connections
sbit SPExpanderRST at P1_0_bit;
sbit SPExpanderCS  at P1_1_bit;
// End Port Expander module connections

char i;                              // Loop variable

void Move_Delay() {                  // Function used for text moving
  Delay_ms(500);                     // You can change the moving speed here
}

void main() {

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                                   // Initialize SPI module used with PortExpander

//  // If Port Expander Library uses SPI2 module
//  SPI2_Init();                                   // Initialize SPI module used with PortExpander

  SPI_Lcd8_Config(0);                     // Initialize Lcd over SPI interface
  SPI_Lcd8_Cmd(_LCD_CLEAR);               // Clear display
  SPI_Lcd8_Cmd(_LCD_CURSOR_OFF);          // Turn cursor off
  SPI_Lcd8_Out(1,6, "mikroE");            // Print text to Lcd, 1st row, 6th column
  SPI_Lcd8_Chr_CP('!');                   // Append '!'
  SPI_Lcd8_Out(2,1, text);                // Print text to Lcd, 2nd row, 1st column

  // SPI_Lcd8_Out(3,1,"mikroE");          // For Lcd with more than two rows
  // SPI_Lcd8_Out(4,15,"mikroE");         // For Lcd with more than two rows
  
  Delay_ms(2000);

  // Moving text
  for(i=0; i<4; i++) {                    // Move text to the right 4 times
    Spi_Lcd8_Cmd(_LCD_SHIFT_RIGHT);
    Move_Delay();
  }

  while(1) {                              // Endless loop
    for(i=0; i<8; i++) {                  // Move text to the left 7 times
      Spi_Lcd8_Cmd(_LCD_SHIFT_LEFT);
      Move_Delay();
    }

    for(i=0; i<8; i++) {                  // Move text to the right 7 times
      Spi_Lcd8_Cmd(_LCD_SHIFT_RIGHT);
      Move_Delay();
    }
  }

}