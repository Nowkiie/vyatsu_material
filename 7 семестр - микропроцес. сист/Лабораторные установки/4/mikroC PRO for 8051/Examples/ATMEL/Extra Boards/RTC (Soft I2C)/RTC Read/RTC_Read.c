/*
 * Project name:
     RTC_Read (Demonstration on working with the RTC Module and Software I2C routines)
 * Copyright:
     (c) Mikroelektronika, 2012.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is simple demonstration how to read date and time from
     PCF8583 RTC (real-time clock).
     Date and time are read from the RTC every 1 second and printed on LCD.
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
     - Turn on LCD backlight switch on development board at SW7.6.
     - In order to use the example, address pin A0 of PCF8583 must be set to 0V.
       (on mikroElektronika's RTC extra board this is done by default)
*/

char seconds, minutes, hours, day, month;    // Global date/time variables
char year;

// Software I2C connections
sbit Soft_I2C_Scl at P1_0_bit;
sbit Soft_I2C_Sda at P1_1_bit;
// End Software I2C connections

// LCD module connections
sbit LCD_RS at P2_0_bit;
sbit LCD_EN at P2_1_bit;

sbit LCD_D4 at P2_2_bit;
sbit LCD_D5 at P2_3_bit;
sbit LCD_D6 at P2_4_bit;
sbit LCD_D7 at P2_5_bit;
// End LCD module connections

//------------------ Performs project-wide init
void Init_Main() {
  Soft_I2C_Init();           // Initialize Soft I2C communication
  Lcd_Init();                // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);       // Clear LCD display
  Lcd_Cmd(_LCD_CURSOR_OFF);  // Turn cursor off

  Lcd_Out(1,1,"Date:");      // Prepare and output static text on LCD
  Lcd_Chr(1,8,'.');
  Lcd_Chr(1,11,'.');
  Lcd_Chr(1,16,'.');
  Lcd_Out(2,1,"Time:");
  Lcd_Chr(2,8,':');
  Lcd_Chr(2,11,':');
  Lcd_Out(1,12,"201");       // start from year 2010
}

//--------------------- Reads time and date information from RTC (PCF8583)
void Read_Time() {

  Soft_I2C_Start();               // Issue start signal
  Soft_I2C_Write(0xA0);           // Address PCF8583, see PCF8583 datasheet
  Soft_I2C_Write(2);              // Start from address 2
  Soft_I2C_Start();               // Issue repeated start signal
  Soft_I2C_Write(0xA1);           // Address PCF8583 for reading R/W=1

  seconds = Soft_I2C_Read(1);     // Read seconds byte
  minutes = Soft_I2C_Read(1);     // Read minutes byte
  hours = Soft_I2C_Read(1);       // Read hours byte
  day = Soft_I2C_Read(1);         // Read year/day byte
  month = Soft_I2C_Read(0);       // Read weekday/month byte
  Soft_I2C_Stop();                // Issue stop signal

}

//-------------------- Formats date and time
void Transform_Time() {
  seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // Transform seconds
  minutes  =  ((minutes & 0xF0) >> 4)*10 + (minutes & 0x0F);  // Transform months
  hours    =  ((hours & 0xF0)  >> 4)*10  + (hours & 0x0F);    // Transform hours
  year     =   (day & 0xC0) >> 6;                             // Transform year
  day      =  ((day & 0x30) >> 4)*10    + (day & 0x0F);       // Transform day
  month    =  ((month & 0x10)  >> 4)*10 + (month & 0x0F);     // Transform month
}

//-------------------- Output values to LCD
void Display_Time() {

   Lcd_Chr(1, 6, (day / 10)   + 48);    // Print tens digit of day variable
   Lcd_Chr(1, 7, (day % 10)   + 48);    // Print oness digit of day variable
   Lcd_Chr(1, 9, (month / 10) + 48);
   Lcd_Chr(1,10, (month % 10) + 48);
   Lcd_Chr(1,15,  year        + 48);    // Print year variable  (start from year 2010)


   Lcd_Chr(2, 6, (hours / 10)   + 48);
   Lcd_Chr(2, 7, (hours % 10)   + 48);
   Lcd_Chr(2, 9, (minutes / 10) + 48);
   Lcd_Chr(2,10, (minutes % 10) + 48);
   Lcd_Chr(2,12, (seconds / 10) + 48);
   Lcd_Chr(2,13, (seconds % 10) + 48);
}

//----------------- Main procedure
void main() {
  Delay_ms(500);

  Init_Main();               // Perform initialization

  while (1) {                // Endless loop
    Read_Time();             // Read time from RTC(PCF8583)
    Transform_Time();        // Format date and time
    Display_Time();          // Prepare and display on LCD
  }
}