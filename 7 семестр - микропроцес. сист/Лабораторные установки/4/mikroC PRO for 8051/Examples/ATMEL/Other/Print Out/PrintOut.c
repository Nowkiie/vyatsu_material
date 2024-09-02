/*
 * Project name:
     PrintOutExample (Sample usage of PrintOut() function)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     Simple demonstration on usage of the PrintOut() function.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn ON RX and TX UART switches (SW8.5 and SW8.6).
*/

void PrintHandler(char c) {
  UART1_Write(c);
}

void main() {

  UART1_Init(4800);
  Delay_ms(100);

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
                         "     MCU:             AT89S8253\r\n"
                         "     Dev.Board:       Easy8051v6\r\n"
                         "     Oscillator:      External Clock, %6.3fMHz\r\n"
                         "     Ext. Modules:    -\r\n"
                         "     SW:              mikroC PRO for 8051\r\n"
                         " * NOTES:\r\n"
                         "     None.\r\n"
                         " */\r\n", Get_Fosc_kHz()/1000.);

}