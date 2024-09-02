/*
 * Project name:
     SMBus_Simple (Simple test of SMBus Library routines))
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This program demonstrates usage of the SMBus Library routines. It
     establishes I2C bus communication with 24C02 EEPROM chip, writes one byte
     of data on some location, then reads it and sends it to PC via UART.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:EEPROM
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - UART: SW11(1,3 - ON)
     - EEPROM: SW12(4,6 - ON)
*/

char ee_data;

void main(){

  WDTCN    = 0xDE;                     // Sequence for
  WDTCN    = 0xAD;                     // disabling the watchdog timer

  OSCICN = 0x83;                       // Configure internal oscillator for
                                       // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                       // Enable missing clock detector


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

  XBR0 = 0x07;
  XBR1 = 0x00;                         // Don't Route /SYSCLK to a port pin
  XBR2 = 0x40;                         // Enable crossbar and weak pull-ups

  P0MDOUT |= 0b11000001;               // Configure P0.7(SCL), P0.6(SDA)
                                       //  and P0.0(TX) pin as push-pull


  UART1_Init(4800);                    // Initialize UART module at 4800 bps
  Delay_ms(100);                       // Wait for UART module to stabilize
  UART1_Write_Text("Start ");


  SMBus1_Init(100000);                 // Initialize I2C communication
  SMBus1_Start();                      // Issue I2C start signal
  SMBus1_Write(0xA2);                  // Send byte via I2C  (device address + W)
  SMBus1_Write(2);                     // Send byte (address of EEPROM location)
  SMBus1_Write(0xFD);                  // Send data (data to be written)
  SMBus1_Stop();                       // Issue I2C stop signal

  Delay_100ms();

  SMBus1_Start();                      // Issue I2C start signal
  SMBus1_Write(0xA2);                  // Send byte via I2C  (device address + W)
  SMBus1_Write(2);                     // Send byte (data address)
  SMBus1_Repeated_Start();             // Issue I2C signal repeated start
  SMBus1_Write(0xA3);                  // Send byte (device address + R)
  ee_data = SMBus1_Read(0u);           // Read the data (NO acknowledge)
  UART1_Write(ee_data);                // In the USART Terminal choose option "Receive data as HEX" and you'll see the 0xFD read from EEPROM
  SMBus1_Stop();                       // issue I2C stop signal

}