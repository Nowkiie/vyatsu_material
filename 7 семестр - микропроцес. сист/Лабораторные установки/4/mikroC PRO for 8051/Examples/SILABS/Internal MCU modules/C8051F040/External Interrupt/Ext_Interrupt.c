/* Project name:
     External Interrupt on Port0 (Simple 'Hello World' project)
 * Copyright:
     (c) Mikroelektronika, 2010.
 * Revision History:
     20101007:
      - initial release;
     20110224(TL):
      - adapted for PRO version
 * Description:
     This is a simple 'Hello World' project. It counts presses on PORT3.2 and
     shows result on diodes connected to PORT0.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 24.5MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051 
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Make sure you turn ON the PORT3 LEDs (SW9.4), set PORT3 Pull up jumper in GND position (J4)
       and turn off PORT3.2 Switch (SW4.3)
 */

int tmp = 0, cnt = 0xfF;                    // Global variable cnt and tmp with starting values

void External_ISR()org IVT_ADDR_EX0 {    // Interrupt rutine
   EA_bit = 0; // disable interrupts
   tmp = 1;
   EA_bit = 1; // enable interrupts
}

void main() {                               // Main program
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                // disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC   = 0x04;                // Enable missing clock detector

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
  CLKSEL = 0x01;

  XBR0 = 0x00;
  XBR1 = 0x04;
  XBARE_bit = 1;
  XBR2 = 0x42;
  P3MDOUT = 0xFF;

  IE0_bit = 0;
  IT0_bit = 1;  // edge sensitive, falling edge
  PX0_bit = 1;  // highest priority
  EX0_bit = 1;  // Enable External Interrupt
  EA_bit = 1;

  while(1){                               // Unending loop
    if (tmp) {                            // tmp is temporary variable that enables us to control Interrupt counting
      cnt = cnt - 1;                      // Decreasing cnt variable (negative logic)
      tmp = 0;                            // Deleting tmp variable
    }
    P3 = cnt;                             // Write on Port0 value of varibale cnt
    
    delay_ms(250);                        // This is needed for button debounce
  }
}