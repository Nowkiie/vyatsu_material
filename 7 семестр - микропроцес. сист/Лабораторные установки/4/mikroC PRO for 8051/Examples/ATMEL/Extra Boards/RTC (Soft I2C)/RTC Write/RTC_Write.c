/*
 * Project name:
     RTC_Write (Demonstration on working with the RTC Module and Software I2C routines)
 * Copyright:
     (c) Mikroelektronika, 2012.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is simple demonstration how to set date and time on PCF8583
     RTC (real-time clock).
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:RTC_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Pull-up I2C communication lines (P1.0 and P1.1)
     - Turn off I2C communication lines (PORT1) LEDs at SW7.1.
     - In order to use the example, address pin A0 of PCF8583 must be set to 0V.
       (on mikroElektronika's RTC extra board this is done by default)
*/

// Software I2C connections
sbit Soft_I2C_Scl at P1_0_bit;
sbit Soft_I2C_Sda at P1_1_bit;
// End Software I2C connections

void main() {
   Soft_I2C_Init();       // Initialize full master mode
   Soft_I2C_Start();      // Issue start signal
   Soft_I2C_Write(0xA0);  // Address PCF8583, see PCF8583 datasheet
   Soft_I2C_Write(0);     // Start from address 0 (configuration memory location)
   Soft_I2C_Write(0x80);  // Write 0x80 to configuration memory location (pause counter...)
   Soft_I2C_Write(0);     // Write 0 to cents memory location
   Soft_I2C_Write(0);     // Write 0 to seconds memory location
   Soft_I2C_Write(0x30);  // Write 0x30 to minutes memory location
   Soft_I2C_Write(0x12);  // Write 0x12 to hours memory location
   Soft_I2C_Write(0x52);  // Write 0x52 to year/date memory location
   Soft_I2C_Write(0x10);  // Write 0x10 to weekday/month memory location
   Soft_I2C_Stop();       // Issue stop signal

   Soft_I2C_Start();      // Issue start signal
   Soft_I2C_Write(0xA0);  // Address PCF8530
   Soft_I2C_Write(0);     // Start from address 0
   Soft_I2C_Write(0);     // Write 0 to configuration memory location (enable counting)
   Soft_I2C_Stop();       // Issue stop signal
}