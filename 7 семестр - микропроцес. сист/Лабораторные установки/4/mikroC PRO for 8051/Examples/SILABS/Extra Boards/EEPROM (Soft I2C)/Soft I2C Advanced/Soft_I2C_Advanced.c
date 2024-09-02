/*
 * Project name:
     I2C_Advanced (Advanced I2C Example)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This example features the advanced communication with the 24C02 EEPROM chip
     by introducing its own library of functions for this task: init, single
     write, single and sequential read. It performs write of a sequence of bytes
     (characters) into the EEPROM and writes this out at the first row on Lcd.
     Then, data read from EEPROM is performed and the result is sent to UART.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 24.5MHz
     Ext. Modules:    Ext. Modules: ac:EEPROM    mE EEPROM (24C02)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Pull-up I2C communication lines.
*/

#include "EEPROM_24C02.h"

// Software I2C connections
sbit Soft_I2C_Scl at P0_0_bit;
sbit Soft_I2C_Sda at P0_1_bit;
// End Software I2C connections

char someData[] = "I2C mikroE";
char i ,tmpdata;

//  Main
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
  CLKSEL = 0x01;
//


  XBR0      = 0x07;
  XBR2      = 0x44;

  P1MDOUT |= 0x01;                   // Configure P1.0 (TX) pin as push-pull
  UART2_Init(4800);                  // Initialize UART module at 4800 bps
  Delay_ms(100);                     // Wait for UART module to stabilize
   
  P0MDOUT |= 0b00000101;             // Configure P0.3(SDA), P0.2(SCK)
                                     //   and P0.0(TX) pin as push-pull
  P1MDOUT |= 0b00000011;

  UART2_Init(4800);                  // Initialize UART module at 4800 bps
  Delay_ms(100);                     // Wait for UART module to stabilize
  UART2_Write_Text("Start");
  UART2_Write(13); UART2_Write(10);

  EEPROM_24C02_Init();                      // performs I2C initialization

  // Example for single-byte write
  i = 0;
  tmpdata = 1;
  while ((tmpdata = someData[i]) != 0) {
    i++;
    EEPROM_24C02_WrSingle(i, tmpdata);      // writes data, char by char, in the EEPROM
    Delay_ms(20);
    UART2_Write(tmpdata);
  }
  EEPROM_24C02_WrSingle(i+1, 0);            // writes string termination
  Delay_ms(20);
  
  UART2_Write(13); UART2_Write(10);

  // Example for single-byte read
  i = 1;
  tmpdata = 1;
  while ((tmpdata = EEPROM_24C02_RdSingle(i)) != 0) {
    UART2_Write(tmpdata);
    Delay_ms(20);
    i++ ;
  }
  UART2_Write(13); UART2_Write(10);
  
  //  Example for sequential data read
  Delay_ms(1000);
  EEPROM_24C02_RdSeq(1, someData, 13);
  UART2_Write(someData);
  UART2_Write(13); UART2_Write(10);
}