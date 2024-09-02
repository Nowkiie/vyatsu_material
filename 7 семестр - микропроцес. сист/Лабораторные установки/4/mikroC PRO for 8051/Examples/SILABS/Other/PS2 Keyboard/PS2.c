/*
 * Project name:
     PS2_Example (Demonstration on using PS/2 keyboard library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     In this example, key(s) pressed on the PS/2 keyboard are read and transferred
     to PC through UART. Various basic keyboard activities are tested:
     "normal" keys, keys with <Shift> pressed, keys with <Caps Lock>
     pressed, numerical keypad ON/OFF and keys. The result is visible on PC, on
     USART Terminal tool.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Keyboard should be powered with 5V !!!
     - Pins used for PS/2 communication should be connected to pull-up resistors.
     - Some keyboards with various multimedia attachments on them 
       tend to "choke" the communication by constantly sending
       requests on various multimedia objects' status (volume, mouse pos. etc.).
       This may slow down the communication pace with the MCU.
 */

unsigned short keydata = 0, special = 0, down = 0;
 
// PS2 module connections
sbit PS2_DATA  at P0_2_bit;
sbit PS2_CLOCK at P0_3_bit;
// End PS2 module connections

void main() {

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
  P0MDOUT |= 0b00000001;             // Configure P0.0(TX) pin as push-pull

  UART1_Init(4800);                  // Initialize UART module at 4800 bps
  Ps2_Config();                      // Initialize PS/2 Keyboard
  Delay_ms(100);                     // Wait for keyboard to finish
  
  UART1_Write_Text("Ready");
  UART1_Write(10);                   // Line Feed
  UART1_Write(13);                   // Carriage return

  do {
    if (Ps2_Key_Read(&keydata, &special, &down)) {
      if (down && (keydata == 16)) {// Backspace
         UART1_Write(0x08);
      }
      else if (down && (keydata == 13)) {// Enter
        UART1_Write('\r');               // send carriage return to usart terminal
        //UART1_Write('\n');             // uncomment this line if usart terminal also expects line feed
                                         // for new line transition
      }
      else if (down && !special && keydata) {
        UART1_Write(keydata);
      }
    }
    Delay_ms(10);            // debounce
  } while (1);
}