/*
 * Project name:
     Spi_Glcd (Demonstration of using Spi_Glcd Library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This is a simple demonstration of the serial Glcd library routines:
     - Init and Clear (pattern fill)
     - Image display
     - Drawing shapes
     - Writing text           
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     ext. modules:    ac:Serial_LCD_GLCD me serial lcd/glcd adapter board board on port0, glcd 128x64(ks108/107 controller)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
 */

const code char truck_bmp[1024];

// Port Expander module connections
sbit SPExpanderRST at P0_4_bit;
sbit SPExpanderCS  at P0_5_bit;
// End Port Expander module connections

void Delay2s(){                         // 2 seconds delay function
  Delay_ms(2000);
}

void main() {
  char counter;
  char *someText;

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

  #define COMPLETE_EXAMPLE
  // If Port Expander Library uses SPI1 module
  SPI1_Init(100000);                             // Initialize SPI module used with PortExpander
  
//  // If Port Expander Library uses SPI2 module
//  SPI2_Init(100000);                             // Initialize SPI module used with PortExpander

  Spi_Glcd_Init(0);                              // Initialize Glcd via SPI
  Spi_Glcd_Fill(0x00);                           // Clear Glcd

  while(1) {
    #ifdef COMPLETE_EXAMPLE
      Spi_Glcd_Image(truck_bmp);                   // Draw image
      Delay2s(); Delay2s();

      Spi_Glcd_Fill(0x00);                         // Clear Glcd
      Delay2s;

      Spi_Glcd_Box(62,40,124,56,1);                // Draw box
      Spi_Glcd_Rectangle(5,5,84,35,1);             // Draw rectangle
      Spi_Glcd_Line(0, 63, 127, 0,1);              // Draw line
      Delay2s();
    #endif
    for(counter = 5; counter < 60; counter+=5 ) {  // Draw horizontal and vertical line
      Delay_ms(250);
      Spi_Glcd_V_Line(2, 54, counter, 1);
      Spi_Glcd_H_Line(2, 120, counter, 1);
    }
    Delay2s();

    Spi_Glcd_Fill(0x00);                         // Clear Glcd
    #ifdef COMPLETE_EXAMPLE
      Spi_Glcd_Set_Font(Character8x7, 8, 8, 32);   // Choose font, see __Lib_GLCDFonts.c in Uses folder
      Spi_Glcd_Write_Text("mikroE", 5, 7, 2);      // Write string

      for (counter = 1; counter <= 10; counter++)  // Draw circles
        Spi_Glcd_Circle(63,32, 3*counter, 1);
      Delay2s();
    
      Spi_Glcd_Box(12,20, 70,63, 2);               // Draw box
      Delay2s();

      Spi_Glcd_Fill(0xFF);                         // Fill Glcd
      Spi_Glcd_Set_Font(Character8x7, 8, 7, 32);   // Change font
      someText = "8x7 Font";
      Spi_Glcd_Write_Text(someText, 5, 1, 2);      // Write string
      Delay2s();

      Spi_Glcd_Set_Font(System3x5, 3, 5, 32);      // Change font
      someText = "3X5 CAPITALS ONLY";
      Spi_Glcd_Write_Text(someText, 5, 3, 2);      // Write string
      Delay2s();

      Spi_Glcd_Set_Font(font5x7, 5, 7, 32);        // Change font
      someText = "5x7 Font";
      Spi_Glcd_Write_Text(someText, 5, 5, 2);      // Write string
      Delay2s();

      Spi_Glcd_Set_Font(FontSystem5x7_v2, 5, 7, 32); // Change font
      someText = "5x7 Font (v2)";
      Spi_Glcd_Write_Text(someText, 5, 7, 2);      // Write string
      Delay2s();
    #endif
    }
}