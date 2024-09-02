/*
 * Project name:
     Eeprom (Demonstration of using EEPROM Library) 
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a demonstration of using library functions for handling of the
     MCU's internal EEPROM module. First, some data is written to EEPROM
     in byte and block mode; then the data is read from the same locations and 
     displayed on P0, P1 and P2.
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
     - Turn ON the PORT LEDs.
*/

char buffer[32], ii;                   // Data buffer, loop variable

void main(){

  P0 = 0;
  P1 = 0;
  P2 = 0;

   for(ii = 31; buffer[ii] = ii; ii--) // Fill data buffer
     ;

   EEPROM_Write(2,    0xAA);           // Write some data at address 2
   EEPROM_Write(0x732,0x55);           // Write some data at address 0x732
   EEPROM_Write_Block(0x100, buffer);  // Write 32 bytes block at address 0x100

   Delay_ms(1000);                     // Blink P0 and P1 diodes
   P0 = 0xFF;                          //   to indicate reading start 
   P1 = 0xFF;
   Delay_ms(1000);
   P0 = 0x00;
   P1 = 0x00;
   Delay_ms(1000);

   P0 = EEPROM_Read(2);                // Read data from address 2 and display it on PORT0
   P1 = EEPROM_Read(0x732);            // Read data from address 0x732 and display it on PORT1

   Delay_ms(1000);
   for(ii = 0; ii < 32; ii++) {        // Read 32 bytes block from address 0x100
     P2 = EEPROM_Read(0x100+ii);       //   and display data on PORT2
     Delay_ms(100);
  }
}