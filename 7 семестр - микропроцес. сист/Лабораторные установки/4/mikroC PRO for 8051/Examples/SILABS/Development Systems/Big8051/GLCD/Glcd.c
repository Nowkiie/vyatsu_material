/*
 * Project name:
     GLCD (Demonstration of the GLCD library routines)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This is a simple demonstration of the GLCD library routines:
     - Init and Clear (pattern fill)
     - Image display
     - Basic geometry - lines, circles, boxes and rectangles
     - Text display and handling
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:GLCD
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - SW12.8 - ON (GLCD Backlight)
*/


//Declarations------------------------------------------------------------------
const code char truck_bmp[1024];
//--------------------------------------------------------------end-declarations

// Glcd module connections
char GLCD_DataPort at P4;

sbit GLCD_CS1 at P2_0_bit;
sbit GLCD_CS2 at P2_1_bit;
sbit GLCD_RS  at P2_2_bit;
sbit GLCD_RW  at P2_3_bit;
sbit GLCD_EN  at P2_4_bit;
sbit GLCD_RST at P2_5_bit;
// End Glcd module connections

void delay2S(){                                      // 2 seconds delay function
  Delay_ms(2000);
}

unsigned int i;

void main() {
  unsigned short ii;
  char *someText;


  WDTCN    = 0xDE;                                   // Sequence for
  WDTCN    = 0xAD;                                   // disabling the watchdog timer



  OSCICN = 0x83;                                     // Configure internal oscillator for
                                                     // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                     // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                    // External Oscillator is an external
                                                     // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//


  XBR2     = 0x40;                                   // Enable crossbar, enable weak pull-ups
  P4MDOUT  = 0x00;                                   // Configure PORT4 pins as open-drain
  P2MDOUT  = 0xFF;                                   // Configure PORT2 pins as push-pull outputs

  #define COMPLETE_EXAMPLE                           // Comment this line to make simpler/smaller example
  Glcd_Init();                                       // Initialize GLCD
  Glcd_Fill(0x00);                                   // Clear GLCD

  while(1) {
    #ifdef COMPLETE_EXAMPLE
      Glcd_Image(truck_bmp);                         // Draw image
      delay2S(); delay2S();
    #endif

    Glcd_Fill(0x00);                                 // Clear GLCD

    Glcd_Box(62,40,124,56,1);                        // Draw box
    Glcd_Rectangle(5,5,84,35,1);                     // Draw rectangle
    Glcd_Line(0, 0, 127, 63, 1);                     // Draw line
    delay2S();

    for(ii = 5; ii < 60; ii+=5 ) {                   // Draw horizontal and vertical lines
      Delay_ms(250);
      Glcd_V_Line(2, 54, ii, 1);
      Glcd_H_Line(2, 120, ii, 1);
    }

    delay2S();

    Glcd_Fill(0x00);                                 // Clear GLCD
    #ifdef COMPLETE_EXAMPLE
      Glcd_Set_Font(Character8x7, 8, 7, 32);         // Choose font, see __Lib_GLCDFonts.c in the Uses folder

      Glcd_Write_Text("mikroE", 1, 7, 2);            // Write string

      for (ii = 1; ii <= 10; ii++)                   // Draw circles
        Glcd_Circle(63,32, 3*ii, 1);
      delay2S();

      Glcd_Box(12,20, 70,57, 2);                     // Draw box
      delay2S();

      Glcd_Fill(0xFF);                               // Fill GLCD

      Glcd_Set_Font(Character8x7, 8, 7, 32);         // Change font
      someText = "8x7 Font";
      Glcd_Write_Text(someText, 5, 0, 2);            // Write string
      delay2S();

      Glcd_Set_Font(System3x5, 3, 5, 32);            // Change font
      someText = "3X5 CAPITALS ONLY";
      Glcd_Write_Text(someText, 60, 2, 2);           // Write string
      delay2S();

      Glcd_Set_Font(font5x7, 5, 7, 32);              // Change font
      someText = "5x7 Font";
      Glcd_Write_Text(someText, 5, 4, 2);            // Write string
      delay2S();

      Glcd_Set_Font(FontSystem5x7_v2, 5, 7, 32);     // Change font
      someText = "5x7 Font (v2)";
      Glcd_Write_Text(someText, 5, 6, 2);            // Write string
      delay2S();
    #endif
  }
}