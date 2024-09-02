/*
 * Project name:
     PrintOutExample (Sample usage of PrintOut() function)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     Simple demonstration on usage of the PrintOut() function.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

void PrintHandler(char c) {
  UART1_Write(c);
}

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

  XBR2      = 0x44;
  P0MDOUT.B0 = 1;                 // Configure P0.0 (TX) pin as push-pull

  UART1_Init(4800);
  Delay_ms(100);
  UART1_Write_Text("Start");

  PrintOut(PrintHandler, "/*\r\n"
                         " * Project name:\r\n"
                         "     PrintOutExample (Sample usage of PrintOut() function)\r\n"
                         " * Copyright:\r\n"
                         "     (c) MikroElektronika, 2009.\r\n"
                         " * Revision History:\r\n"
                         "     20090601:\r\n"
                         "       - Initial release\r\n"
                         " * Description:\r\n"
                         "     Simple demonstration on usage of the PrintOut() function.\r\n"
                         " * Test configuration:\r\n"
                         "     MCU:             C8051F120\r\n"
                         "     Dev.Board:       C8051Fx20-TB\r\n"
                         "     Oscillator:      Internal oscillator, %6.3fMHz\r\n"
                         "     Ext. Modules:    -\r\n"
                         "     SW:              mikroC PRO for 8051\r\n"
                         " * NOTES:\r\n"
                         "     None.\r\n"
                         " */\r\n", Get_Fosc_kHz()/1000.);

}