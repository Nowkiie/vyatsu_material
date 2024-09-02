/*
 * Project name:
     Sprinti
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a demonstration of the standard C library sprinti routine usage.
     Two different representations of the same integer number obtained
     by using the sprintf routine are sent via UART.
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
     - Turn ON RX and TX UART switches  (SW11.1 and SW11.3).
*/

unsigned int int_no = 30000;
char  buffer[15], msg[25];

// store strings to CODE space to save DATA space (Memory Type Specifiers, code)
const char code msg1[] = "Integer representation";
const char code msg2[] = "\r\nd format:";
const char code msg3[] = "\r\nx format:";

void CopyCodeStrToRam(const char *source, char *dest) {
  while(*source) {
    *dest++ = *source++ ;
  }
  *dest = 0;
}

void main(){

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

  XBR2      = 0x40;
  P0MDOUT.B0 = 1;                 // Configure P0.0 (TX) pin as push-pull


  UART1_Init(4800);                        // Initialize UART module at 4800 bps
  Delay_ms(100);
  
  CopyCodeStrToRam(msg1, msg);             // copy message1 to RAM
  UART1_Write_Text(msg);                   // Write message on UART

  sprinti(buffer, "%10d", int_no);         // Format int_no and store it to buffer
  CopyCodeStrToRam(msg2, msg);             // copy message2 to RAM
  UART1_Write_Text(msg);                   // Write message on UART
  UART1_Write_Text(buffer);                // Write buffer on UART

  sprinti(buffer, "%10x", int_no);         // Format int_no and store it to buffer
  CopyCodeStrToRam(msg3, msg);             // copy message3 to RAM
  UART1_Write_Text(msg);                   // Write message on UART
  UART1_Write_Text(buffer);                // Write buffer on UART
  
}