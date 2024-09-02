/*
 * Project name:
     SPI_Glcd (Demonstration of using Spi_Glcd Library)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a simple demonstration of the serial Glcd library routines:
     - Init and Clear (pattern fill)
     - Image display
     - Drawing shapes
     - Writing text           
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:Serial_GLCD_128x64_Adapter_Board on PORT1, Glcd 128x64(KS108/107 controller)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

const code char truck_bmp[1024];

// Port Expander module connections
sbit SPExpanderRST at P1_0_bit;
sbit SPExpanderCS  at P1_1_bit;
// End Port Expander module connections

void Delay2s(){                         // 2 seconds delay function
  Delay_ms(2000);
}

void main() {
  char counter;
  char *someText;

  #define COMPLETE_EXAMPLE
  // If Port Expander Library uses SPI1 module
  SPI1_Init_Advanced(_SPI_FCY_DIV4 | _SPI_CLK_IDLE_LO | _SPI_CLK_IDLE_2_ACTIVE); // Initialize SPI module used with PortExpander
  
//  // If Port Expander Library uses SPI2 module
//  SPI2_Init();                                   // Initialize SPI module used with PortExpander

  SPI_Glcd_Init(0);                              // Initialize Glcd via SPI
  SPI_Glcd_Fill(0x00);                           // Clear Glcd

  while(1) {
    #ifdef COMPLETE_EXAMPLE
      SPI_Glcd_Image(truck_bmp);                   // Draw image
      Delay2s(); Delay2s();

      SPI_Glcd_Fill(0x00);                         // Clear Glcd
      Delay2s;

      SPI_Glcd_Box(62,40,124,56,1);                // Draw box
      SPI_Glcd_Rectangle(5,5,84,35,1);             // Draw rectangle
      SPI_Glcd_Line(0, 63, 127, 0,1);              // Draw line
      Delay2s();
    #endif
    for(counter = 5; counter < 60; counter+=5 ) {  // Draw horizontal and vertical line
      Delay_ms(250);
      SPI_Glcd_V_Line(2, 54, counter, 1);
      SPI_Glcd_H_Line(2, 120, counter, 1);
    }
    Delay2s();

    SPI_Glcd_Fill(0x00);                         // Clear Glcd
    #ifdef COMPLETE_EXAMPLE
      SPI_Glcd_Set_Font(Character8x7, 8, 8, 32);   // Choose font, see __Lib_GLCDFonts.c in Uses folder
      SPI_Glcd_Write_Text("mikroE", 5, 7, 2);      // Write string

      for (counter = 1; counter <= 10; counter++)  // Draw circles
        SPI_Glcd_Circle(63,32, 3*counter, 1);
      Delay2s();
    
      SPI_Glcd_Box(12,20, 70,63, 2);               // Draw box
      Delay2s();

      SPI_Glcd_Fill(0xFF);                         // Fill Glcd
      SPI_Glcd_Set_Font(Character8x7, 8, 7, 32);   // Change font
      someText = "8x7 Font";
      SPI_Glcd_Write_Text(someText, 5, 1, 2);      // Write string
      Delay2s();

      SPI_Glcd_Set_Font(System3x5, 3, 5, 32);      // Change font
      someText = "3X5 CAPITALS ONLY";
      SPI_Glcd_Write_Text(someText, 5, 3, 2);      // Write string
      Delay2s();

      SPI_Glcd_Set_Font(font5x7, 5, 7, 32);        // Change font
      someText = "5x7 Font";
      SPI_Glcd_Write_Text(someText, 5, 5, 2);      // Write string
      Delay2s();

      SPI_Glcd_Set_Font(FontSystem5x7_v2, 5, 7, 32); // Change font
      someText = "5x7 Font (v2)";
      SPI_Glcd_Write_Text(someText, 5, 7, 2);      // Write string
      Delay2s();
    #endif
    }
}