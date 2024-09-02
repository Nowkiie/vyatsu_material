/*
 * Project name:
     Serial_Flash (Demonstration of usage of the on-board SerialFlash)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
      Demonstration of basic reading/writing techniques from/to SerialFlash.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:Flash
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - SW10(1,3,5 - ON)
     - SW15.7 - ON
     - SW12.7 - ON
*/

#define _DATA_ARRAY_SIZE 16
#include <built_in.h>
#include "Serial_Flash_driver.h"

sbit CS_Serial_Flash_bit at P2_3_bit;

// LCD module connections
sbit LCD_RS at P3_0_bit;
sbit LCD_EN at P3_1_bit;

sbit LCD_D4 at P3_2_bit;
sbit LCD_D5 at P3_3_bit;
sbit LCD_D6 at P3_4_bit;
sbit LCD_D7 at P3_5_bit;
// End LCD module connections


void main() {

 unsigned char temp, txt[12];
 unsigned char i, to_write, success;
 unsigned long address;
 unsigned int half_address;

  WDTCN    = 0xDE;                    // Sequence for
  WDTCN    = 0xAD;                    // disabling the watchdog timer



  OSCICN = 0x83;                      // Configure internal oscillator for
                                      // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                      // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                      // External Oscillator is an external
                                      // crystal (no divide by 2 stage)
  OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
  Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
  while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;
//


  XBR0 = 0x02;
  XBR1 = 0x00;                        // Don't Route /SYSCLK to a port pin
  XBR2 = 0x40;                        // Enable crossbar and weak pull-ups
  P0MDOUT |= 0b00000101;              // P0.2(MOSI) and P0.0(SCK) pin as push-pull outputs
  P3MDOUT  = 0xFF;                    // LCD: Configure PORT3 pins as push-pull outputs
  P2MDOUT |= 0b00001000;              // Configure P2.3(CS) pin as push-pull output

  SPI1_Init(100000);                  // Initialize SPI module

  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1, 1, "  SerialFlash   ");
  Lcd_Out(2, 1, "***BIG8051***");
  Delay_ms(1000);

  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1, 1, "Initializing... ");
  SerialFlash_init();
  SerialFlash_WriteEnable();
  Delay_ms(500);
  SerialFlash_ChipErase();

  Lcd_Cmd(_LCD_CLEAR);
  temp = 221;
  Lcd_Out(1, 1, "Writting:");
  ByteToStr(temp, txt);
  Lcd_out(1, 13, txt);
  SerialFlash_WriteByte(temp, 0x123456);

  Lcd_Out(2, 1, "Reading: ");
  temp = SerialFlash_ReadByte(0x123456);
  ByteToStr(temp, txt);
  Lcd_out(2, 13, txt);
  Delay_ms(1000);
}