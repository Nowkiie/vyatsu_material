/*
 * Project name:
     Spi_Lcd8 (Simple demonstration of the SPI Lcd 8-bit interface library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This is a simple demonstration of SPI Lcd 8-bit library functions.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    ac:Serial_LCD mE Serial LCD/GLCD Adapter Board board on PORT0
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

char *text = "mikroElektronika";

// Port Expander module connections
sbit SPExpanderRST at P0_4_bit;
sbit SPExpanderCS  at P0_5_bit;
// End Port Expander module connections

char i;                              // Loop variable

void Move_Delay() {                  // Function used for text moving
  Delay_ms(500);                     // You can change the moving speed here
}

void main() {
  WDTCN    = 0xDE;             // Sequence for
  WDTCN    = 0xAD;             // disabling the watchdog timer

  OSCICN = 0x83;               // Configure internal oscillator for
                               // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;               // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;              // External Oscillator is an external
                               // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//


  XBR2     = 0x40;             // Enable crossbar, enable weak pull-ups
  P0MDOUT |= 0b00110101;           // Configure P0.2(MOSI), P0.0(SCK)
                                   // P0.5(CS) and P0.4(RST) pin as push-pull

  // If Port Expander Library uses SPI1 module
  SPI1_Init(100000);                               // Initialize SPI module used with PortExpander

//  // If Port Expander Library uses SPI2 module
//  SPI2_Init(100000);                             // Initialize SPI module used with PortExpander

  Spi_Lcd8_Config(0);                     // Initialize Lcd over SPI interface
  Spi_Lcd8_Cmd(_LCD_CLEAR);               // Clear display
  Spi_Lcd8_Cmd(_LCD_CURSOR_OFF);          // Turn cursor off
  Spi_Lcd8_Out(1,6, "mikroE");            // Print text to Lcd, 1st row, 6th column
  Spi_Lcd8_Chr_CP('!');                   // Append '!'
  Spi_Lcd8_Out(2,1, text);                // Print text to Lcd, 2nd row, 1st column

  // Spi_Lcd8_Out(3,1,"mikroE");          // For Lcd with more than two rows
  // Spi_Lcd8_Out(4,15,"mikroE");         // For Lcd with more than two rows
  
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