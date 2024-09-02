/*
 * Project name:
     PS2_Example (Demonstration on using PS/2 keyboard library)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     In this example, key(s) pressed on the PS/2 keyboard are read and transferred
     to PC through UART. Various basic keyboard activities are tested:
     "normal" keys, keys with <Shift> pressed, keys with <Caps Lock>
     pressed, numerical keypad ON/OFF and keys. The result is visible on PC, on
     USART Terminal tool.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    mE PS/2 Connector Board
                      http://www.mikroe.com/add-on-boards/various/ps2-connector/
                      Standard PS2 keyboard
                      http://en.wikipedia.org/wiki/Keyboard_(computing)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Pins used for PS/2 communication should be connected to pull-up resistors.
     - Turn ON RX and TX UART switches (SW8.5 and SW8.6).
     - Some keyboards with various multimedia attachments on them 
       tend to "choke" the communication by constantly sending
       requests on various multimedia objects' status (volume, mouse pos. etc.).
       This may slow down the communication pace with the MCU.
 */


unsigned short keydata = 0, special = 0, down = 0;
 
// PS2 module connections
sbit PS2_DATA  at P0_0_bit;
sbit PS2_CLOCK at P0_1_bit;
// End PS2 module connections

void main() {

  UART1_Init(4800);         // Initialize UART module at 4800 bps
  Ps2_Config();             // Initialize PS/2 Keyboard
  Delay_ms(100);            // Wait for keyboard to finish
  
  UART1_Write_Text("Ready");
  UART1_Write(10);          // Line Feed
  UART1_Write(13);          // Carriage return

  do {
    if (Ps2_Key_Read(&keydata, &special, &down)) {
      if (down && (keydata == 16)) {     // Backspace
         UART1_Write(0x08);
      }
      else if (down && (keydata == 13)) {// Enter
        UART1_Write('\r');               // send carriage return to usart terminal
        //Usart_Write('\n');             // uncomment this line if usart terminal also expects line feed
                                         // for new line transition
      }
      else if (down && !special && keydata) {
        UART1_Write(keydata);
      }
    }
    Delay_ms(10);            // debounce
  } while (1);
}