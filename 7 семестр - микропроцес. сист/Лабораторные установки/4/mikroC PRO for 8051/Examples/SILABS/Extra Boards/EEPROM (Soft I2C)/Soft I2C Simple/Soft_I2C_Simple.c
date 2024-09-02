/*
 * Project name:
     I2C_Simple (Simple test of I2C library routines)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This program demonstrates usage of the I2C library routines. It
     establishes I2C bus communication with 24C02 EEPROM chip, writes one byte
     of data on some location, then reads it and sends it to UART.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 24.5MHz
     Ext. Modules:    Ext. Modules: ac:EEPROM   mE EEPROM (24C02)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Pull-up I2C communication lines.
*/

// Software I2C connections
sbit Soft_I2C_Scl at P0_2_bit;
sbit Soft_I2C_Sda at P0_3_bit;
// End Software I2C connections

unsigned char received_data;

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

  Soft_I2C_Init();                   // initialize I2C communication
  Soft_I2C_Start();                  // issue I2C start signal
  Soft_I2C_Write(0xA2);              // send byte via I2C  (device address + W)
  Soft_I2C_Write(2);                 // send byte (address of EEPROM location)
  Soft_I2C_Write(0xF0);              // send data (data to be written)
  Soft_I2C_Stop();                   // issue I2C stop signal

  Delay_100ms();

  Soft_I2C_Start();                  // issue I2C start signal
  Soft_I2C_Write(0xA2);              // send byte via I2C  (device address + W)
  Soft_I2C_Write(2);                 // send byte (data address)
  Soft_I2C_Start();                  // issue I2C signal repeated start
  Soft_I2C_Write(0xA3);              // send byte (device address + R)
  received_data = Soft_I2C_Read(0u); // Read the data (NO acknowledge)
  UART2_Write(received_data);        //   and send it to UART
  Soft_I2C_Stop();                   // issue I2C stop signal
}