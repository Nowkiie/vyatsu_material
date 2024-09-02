/*
 * Project Name:
     T6963C_240x128 (GLCD Library demo for Toshiba's T6963C Controller)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release; Credits to Bruno Gavand.
 * Description:
     This code in intended to work with GLCD's based on TOSHIBA T6963C controller.
     Pressing buttons P1.0 .. P1.4 generates commands for text and graphic displaying.
     This parts may need a -15V power supply on Vee for LCD drive,
     a simple DC/DC converter can be made with a 2N2905, 220 µH self, diode & 47 µF cap,
     transistor base is driven with PWM through a current limiting resistor.
     This parts have a 8 Kb built-in display RAM, this allows 2 graphics panels
     and one text panel.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    ac:GLCD mE GLCD 240x128 (T6963C) Adapter board on PORT2(control) and PORT0(data)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
      None.

 */

#include        "__T6963C.h"
                            
// T6963C module connections
char T6963C_dataPort at P0;                       // DATA port

sbit T6963C_ctrlwr  at P2_2_bit;                  // WR write signal
sbit T6963C_ctrlrd  at P2_1_bit;                  // RD read signal
sbit T6963C_ctrlcd  at P2_0_bit;                  // CD command/data signal
sbit T6963C_ctrlrst at P2_4_bit;                  // RST reset signal

// Signals not used by library, they are set in main function
sbit T6963C_ctrlce at P2_3_bit;                   // CE signal
sbit T6963C_ctrlfs at P2_6_bit;                   // FS signal
sbit T6963C_ctrlmd at P2_5_bit;                   // MD signal
// End T6963C module connections

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
  P0MDOUT  = 0x00;              // Configure PORT0 pins as open drain
  P2MDOUT  = 0xFF;              // Configure PORT2 pins as push-pull outputs

  #define COMPLETE_EXAMPLE      // comment this line to make simpler/smaller example
  
  T6963C_ctrlce = 0;            // Enable T6963C
  T6963C_ctrlfs = 0;            // Font Select 8x8
  T6963C_ctrlmd = 0;            // Column number select


  // Initialize T6963C
  T6963C_init(240, 128, 8);

  /*
   * Enable both graphics and text display at the same time
   */
  T6963C_graphics(1);
  T6963C_text(1);

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;
  /*
   * Text messages
   */
  T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
  T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);

  /*
   * Cursor
   */
  T6963C_cursor_height(8);       // 8 pixel height
  T6963C_set_cursor(0, 0);       // Move cursor to top left
  T6963C_cursor(0);              // Cursor off
  
  /*
   * Draw rectangles
   */
  T6963C_rectangle(0, 0, 239, 127, T6963C_WHITE);
  T6963C_rectangle(20, 20, 219, 107, T6963C_WHITE);
  T6963C_rectangle(40, 40, 199, 87, T6963C_WHITE);
  T6963C_rectangle(60, 60, 179, 67, T6963C_WHITE);

  /*
   * Draw a cross
   */
  T6963C_line(0, 0, 239, 127, T6963C_WHITE);
  T6963C_line(0, 127, 239, 0, T6963C_WHITE);

  /*
   * Draw solid boxes
   */
  T6963C_box(0, 0, 239, 8, T6963C_WHITE);
  T6963C_box(0, 119, 239, 127, T6963C_WHITE);

  #ifdef COMPLETE_EXAMPLE
    /*
     * Draw circles
     */
    T6963C_circle(120, 64, 10, T6963C_WHITE);
    T6963C_circle(120, 64, 30, T6963C_WHITE);
    T6963C_circle(120, 64, 50, T6963C_WHITE);
    T6963C_circle(120, 64, 70, T6963C_WHITE);
    T6963C_circle(120, 64, 90, T6963C_WHITE);
    T6963C_circle(120, 64, 110, T6963C_WHITE);
    T6963C_circle(120, 64, 130, T6963C_WHITE);

    T6963C_sprite(76, 4, einstein, 88, 119);         // Draw a sprite

    T6963C_setGrPanel(1);                            // Select other graphic panel

    T6963C_image(mikroE_240x128_bmp);                // Draw an image

  #endif

  for(;;) {                                          // Endless loop
    /*
     * If P1.0 is pressed, display only graphic panel
     */
    if(!P1_0_bit) {
      T6963C_graphics(1);
      T6963C_text(0);
      Delay_ms(300);
      }
    #ifdef COMPLETE_EXAMPLE
      /*
       * If P1.1 is pressed, toggle the display between graphic panel 0 and graphic panel 1
       */
      else if(!P1_1_bit) {
        panel++;
        panel &= 1;
        T6963C_displayGrPanel(panel);
        Delay_ms(300);
        }
    #endif
    /*
     * If P1.2 is pressed, display only text panel
     */
    else if(!P1_2_bit) {
      T6963C_graphics(0);
      T6963C_text(1);
      Delay_ms(300);
      }

    /*
     * If P1.3 is pressed, display text and graphic panels
     */
    else if(!P1_3_bit) {
      T6963C_graphics(1);
      T6963C_text(1);
      Delay_ms(300);
      }

    /*
     * If P1.4 is pressed, change cursor
     */
    else if(!P1_4_bit) {
      curs++;
      if(curs == 3) curs = 0;
      switch(curs) {
        case 0:
          // no cursor
          T6963C_cursor(0);
          break;
        case 1:
          // blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(1);
          break;
        case 2:
          // non blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(0);
          break;
        }
      Delay_ms(300);
      }

    /*
     * Move cursor, even if not visible
     */
    cposx++;
    if(cposx == T6963C_txtCols) {
      cposx = 0;
      cposy++;
      if(cposy == T6963C_grHeight / T6963C_CHARACTER_HEIGHT) {
        cposy = 0;
        }
      }
    T6963C_set_cursor(cposx, cposy);

    Delay_ms(100);
    }
}