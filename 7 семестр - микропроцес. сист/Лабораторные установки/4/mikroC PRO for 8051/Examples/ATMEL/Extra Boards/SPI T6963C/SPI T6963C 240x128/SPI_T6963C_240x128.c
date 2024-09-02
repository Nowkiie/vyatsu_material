/*
 * Project Name:
     SPI_T6963C_240x128 (SPI_GLCD Library demo for Toshiba's T6963C Controller)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release; Credits to Bruno Gavand.
 * Description:
     This code in intended to work with GLCD's based on TOSHIBA T6963C 
     controller via SPI communication.
     Pressing buttons P0.0 .. P0.4 generates commands for text and graphic displaying.
     This parts may need a -15V power supply on Vee for LCD drive,
     a simple DC/DC converter can be made with a 2N2905, 220 �H self, diode & 47 �F cap,
     transistor base is driven with PWM through a current limiting resistor.
     This parts have a 8 Kb built-in display RAM, this allows 2 graphics panels
     and one text panel.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:Serial_GLCD_240x128_Adapter_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
      - Put button jumper into GND position and pull-up PORT0.
 */

#include        "__SPIT6963C.h"

// Port Expander module connections
sbit SPExpanderRST at P1_0_bit;
sbit SPExpanderCS  at P1_1_bit;
// End Port Expander module connections

/*
 * bitmap pictures stored in ROM
 */
const code char mikroE_240x128_bmp[];
const code char einstein[];


void main() {
  char idata txt1[] = " EINSTEIN WOULD HAVE LIKED mE";
  char idata txt[] =  " GLCD LIBRARY DEMO, WELCOME !";

  unsigned char  panel;         // Current panel
  unsigned int   i;             // General purpose register
  unsigned char  curs;          // Cursor visibility
  unsigned int   cposx, cposy;  // Cursor x-y position
  
  #define COMPLETE_EXAMPLE      // comment this line to make simpler/smaller example
  
  
  // If SPI_T6963C Library uses SPI1 module
  SPI1_Init_Advanced(_SPI_FCY_DIV4 | _SPI_CLK_IDLE_LO | _SPI_CLK_IDLE_2_ACTIVE); // Initialize SPI module

//  // If SPI_T6963C Library uses SPI2 module
//  SPI2_Init_Advanced(_SPI_FCY_DIV4 | _SPI_CLK_IDLE_LO | _SPI_CLK_IDLE_2_ACTIVE); // Initialize SPI module
  
  /*
   * init display for 240 pixel width and 128 pixel height
   * 8 bits character width
   * data bus on MCP23S17 portB
   * control bus on MCP23S17 portA
   * bit 2 is !WR
   * bit 1 is !RD
   * bit 0 is !CD
   * bit 4 is RST
   * chip enable, reverse on, 8x8 font internaly set in library
   */
  SPI_T6963C_Config(240, 128, 8, 0, 2, 1, 0, 4);
  Delay_ms(1000);

  /*
   * Enable both graphics and text display at the same time
   */
  SPI_T6963C_graphics(1);
  SPI_T6963C_text(1);

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;
  /*
   * Text messages
   */
  SPI_T6963C_write_text(txt, 0, 0, SPI_T6963C_ROM_MODE_XOR);
  SPI_T6963C_write_text(txt1, 0, 15, SPI_T6963C_ROM_MODE_XOR);

  /*
   * Cursor
   */
  SPI_T6963C_cursor_height(8);       // 8 pixel height
  SPI_T6963C_set_cursor(0, 0);       // move cursor to top left
  SPI_T6963C_cursor(0);              // cursor off
  
  #ifdef COMPLETE_EXAMPLE
  /*
   * Draw rectangles
   */
  SPI_T6963C_rectangle(0, 0, 239, 127, SPI_T6963C_WHITE);
  SPI_T6963C_rectangle(20, 20, 219, 107, SPI_T6963C_WHITE);
  SPI_T6963C_rectangle(40, 40, 199, 87, SPI_T6963C_WHITE);
  SPI_T6963C_rectangle(60, 60, 179, 67, SPI_T6963C_WHITE);

  /*
   * Draw a cross
   */
  SPI_T6963C_line(0, 0, 239, 127, SPI_T6963C_WHITE);
  SPI_T6963C_line(0, 127, 239, 0, SPI_T6963C_WHITE);

  /*
   * Draw solid boxes
   */
  SPI_T6963C_box(0, 0, 239, 8, SPI_T6963C_WHITE);
  SPI_T6963C_box(0, 119, 239, 127, SPI_T6963C_WHITE);

  /*
   * Draw circles
   */
  SPI_T6963C_circle(120, 64, 10, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 30, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 50, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 70, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 90, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 110, SPI_T6963C_WHITE);
  SPI_T6963C_circle(120, 64, 130, SPI_T6963C_WHITE);

  SPI_T6963C_sprite(76, 4, einstein, 88, 119);            // Draw a sprite

  SPI_T6963C_setGrPanel(1);                               // Select other graphic panel

  SPI_T6963C_image(mikroE_240x128_bmp);                   // Draw an image

  #endif

  for(;;) {                                               // Endless loop
     /*
      * If P0.0 is pressed, display only graphic panel
      */
    if(!P0_0_bit) {
      SPI_T6963C_graphics(1);
      SPI_T6963C_text(0);
      Delay_ms(300);
    }
    #ifdef COMPLETE_EXAMPLE
     /*
      * If P0.1 is pressed, toggle the display between graphic panel 0 and graphic panel 1
      */
    else if(!P0_1_bit) {
      panel++;
      panel &= 1;
      SPI_T6963C_displayGrPanel(panel);
      Delay_ms(300);
    }
    #endif
    /*
     * If P0.2 is pressed, display only text panel
     */
    else if(!P0_2_bit) {
      SPI_T6963C_graphics(0);
      SPI_T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If P0.3 is pressed, display text and graphic panels
     */
    else if(!P0_3_bit) {
      SPI_T6963C_graphics(1);
      SPI_T6963C_text(1);
      Delay_ms(300);
    }
    /*
     * If P0.4 is pressed, change cursor
     */
    else if(!P0_4_bit) {
      curs++;
      if(curs == 3) curs = 0;
      switch(curs) {
        case 0:
          // no cursor
          SPI_T6963C_cursor(0);
          break;
        case 1:
          // blinking cursor
          SPI_T6963C_cursor(1);
          SPI_T6963C_cursor_blink(1);
          break;
        case 2:
          // non blinking cursor
          SPI_T6963C_cursor(1);
          SPI_T6963C_cursor_blink(0);
          break;
      }
      Delay_ms(300);
    }

    /*
     * Move cursor, even if not visible
     */
    cposx++;
    if(cposx == SPI_T6963C_txtCols) {
      cposx = 0;
      cposy++;
      if(cposy == SPI_T6963C_grHeight / SPI_T6963C_CHARACTER_HEIGHT) {
        cposy = 0;
        }
      }
    SPI_T6963C_set_cursor(cposx, cposy);

    Delay_ms(100);
    }
}