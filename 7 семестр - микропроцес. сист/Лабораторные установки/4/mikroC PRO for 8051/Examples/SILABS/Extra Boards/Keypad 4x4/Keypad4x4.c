/*
 * Project name:
     Keypad_Test (Demonstration of the Keypad library routines)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
      A simple example of using the keypad library.
      It supports keypads with 1..4 rows and 1..4 columns. The code being 
      returned by the Keypad_Key_Press() and Keypad_Key_Click() functions is
      in range from 1..16. In this example, the code returned by the keypad 
      library functions is transformed into ASCII codes [0..9,A..F]. 
      In addition, a small single-byte counter displays the number of
      key presses.
 * Test configuration:
     MCU:             C8051F040
                      https://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F12x-13x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    ac:Keypad4x4 Keypad 4x3 or 4x4 module at PORT2
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Port connected to keypad should be connected to pull-up resistors.
       http://www.mikroe.com/pdf/easy8051b_manual.pdf#page=9&zoom=100
     - Since sampling lines for 8051 MCUs are activated by logical zero
       Keypad Library can not be used with hardwares that have protective diodes
       connected with anode to MCU side, such as mikroElektronika's 
       Keypad extra board HW.Rev v1.20.
 */

unsigned short kp, cnt, oldstate = 0;
char txt[6];

// Keypad module connections
char keypadPort at P2;
// End Keypad module connections

void main() {
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                //   disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC = 0x04;                      // Enable missing clock detector


 // Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                     // External Oscillator is an external
                                      // crystal (no divide by 2 stage)
  OSCXCN |= 7;

  // Step 2. Wait at least 1 ms.
  Delay_ms(5);

  // Step 3. Poll for XTLVLD => ‘1’.
  while ((OSCXCN & 0x80) != 0x80);


  // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;//

  XBR0      = 0x07;
  XBR2      = 0x44;

  P0MDOUT |= 0b00000011;
  
  UART1_Init(4800);                        // Initialize UART module at 4800 bps
  Delay_ms(100);                           // Wait for UART module to stabilize
  UART1_Write_Text("Start");

  cnt = 0;                                 // Reset counter
  Keypad_Init();                           // Initialize Keypad                              

  do {
    kp = 0;                                // Reset key code variable

    // Wait for key to be pressed and released
    do {
      // kp = Keypad_Key_Press();          // Store key code in kp variable
      kp = Keypad_Key_Click();             // Store key code in kp variable
    } while (!kp);
    
   // Prepare value for output, transform key to it's ASCII value
    switch (kp) {
      //case 10: kp = 42; break;  // '*'   // Uncomment this block for keypad4x3
      //case 11: kp = 48; break;  // '0'   
      //case 12: kp = 35; break;  // '#'
      //default: kp += 48;

      case  1: kp = 49; break; // 1        // Uncomment this block for keypad4x4
      case  2: kp = 50; break; // 2
      case  3: kp = 51; break; // 3
      case  4: kp = 65; break; // A
      case  5: kp = 52; break; // 4
      case  6: kp = 53; break; // 5
      case  7: kp = 54; break; // 6
      case  8: kp = 66; break; // B        
      case  9: kp = 55; break; // 7
      case 10: kp = 56; break; // 8
      case 11: kp = 57; break; // 9
      case 12: kp = 67; break; // C
      case 13: kp = 42; break; // *
      case 14: kp = 48; break; // 0
      case 15: kp = 35; break; // #
      case 16: kp = 68; break; // D

    }

    if (kp != oldstate) {                  // Pressed key differs from previous
      cnt = 1;
      oldstate = kp;
      }
    else {                                 // Pressed key is same as previous
      cnt++;
      }

    UART1_Write_Text("Key = ");            // Write Key to UART
    UART1_Write(kp);

    WordToStr(cnt, txt);                   // Transform counter value to string
    UART1_Write_Text(" Count = ");         // Write counter to UART
    UART1_Write_Text(txt);
    
    UART1_Write(13); UART1_Write(10);      // Write new line
  } while (1);
} 