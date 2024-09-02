/*
 * Project name:
     Lcd (Demonstration of the LCD library routines)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This code demonstrates how to use LCD 4-bit library. LCD is first
     initialized, then some text is written, then the text is being moved.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:LCD
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - SW12.7 - ON (LCD Backlight)
*/

// LCD module connections
sbit LCD_RS at P3_0_bit;
sbit LCD_EN at P3_1_bit;

sbit LCD_D4 at P3_2_bit;
sbit LCD_D5 at P3_3_bit;
sbit LCD_D6 at P3_4_bit;
sbit LCD_D7 at P3_5_bit;
// End LCD module connections

char txt1[] = "mikroElektronika";
char txt2[] = "BIG8051";
char txt3[] = "Lcd4bit";
char txt4[] = "example";

char i;                        // Loop variable

void Move_Delay() {            // Function used for text moving
  Delay_ms(500);               // You can change the moving speed here
}



void main(){

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
  P3MDOUT  = 0xFF;             // Configure PORT3 pins as push-pull outputs

  Lcd_Init();                  // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);         // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);    // Cursor off
  LCD_Out(1,6,txt3);           // Write text in first row

  LCD_Out(2,6,txt4);           // Write text in second row
  Delay_ms(2000);
  Lcd_Cmd(_LCD_CLEAR);         // Clear display

  LCD_Out(1,1,txt1);           // Write text in first row
  LCD_Out(2,5,txt2);           // Write text in second row

  Delay_ms(2000);

  // Moving text
  for(i=0; i<4; i++) {         // Move text to the right 4 times
    Lcd_Cmd(_LCD_SHIFT_RIGHT);
    Move_Delay();
  }

  while(1) {                   // Endless loop
    for(i=0; i<8; i++) {       // Move text to the left 7 times
      Lcd_Cmd(_LCD_SHIFT_LEFT);
      Move_Delay();
    }

    for(i=0; i<8; i++) {       // Move text to the right 7 times
      Lcd_Cmd(_LCD_SHIFT_RIGHT);
      Move_Delay();
    }
  }
}