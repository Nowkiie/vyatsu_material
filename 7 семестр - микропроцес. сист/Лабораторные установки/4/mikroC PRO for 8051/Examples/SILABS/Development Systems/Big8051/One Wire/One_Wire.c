/*
 * Project name:
     OneWire (Interfacing the DS1820 temperature sensor - all versions)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     This code demonstrates one-wire communication with temperature sensor
     DS18x20 connected to P2.7 pin.
     MCU reads temperature from the sensor and sends it on the UART.
     The display format of the temperature is 'xxx.xxxx°C'. To obtain correct
     results, the 18x20's temperature resolution has to be adjusted (constant
     TEMP_RESOLUTION).
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:ds1820
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - SW15.8 - ON (also, pull-up P2.7)
     - UART: SW11.1 and SW11.3 - ON
*/

// OneWire pinout
sbit OW_Bit at P2.B7;
// end OneWire definition


//  Set TEMP_RESOLUTION to the corresponding resolution of used DS18x20 sensor:
//  18S20: 9  (default setting; can be 9,10,11,or 12)
//  18B20: 12
const unsigned short TEMP_RESOLUTION = 9;

char *text = "000.0000";
unsigned temp;

void Display_Temperature(unsigned int temp2write) {
  const unsigned short RES_SHIFT = TEMP_RESOLUTION - 8;
  char temp_whole;
  unsigned int temp_fraction;

  // check if temperature is negative
  if (temp2write & 0x8000) {
    text[0] = '-';
    temp2write = ~temp2write + 1;
  }

  // extract temp_whole
  temp_whole = temp2write >> RES_SHIFT ;

  // convert temp_whole to characters
  if (temp_whole/100)
     text[0] = temp_whole/100  + 48;
  else
     text[0] = '0';

  text[1] = (temp_whole/10)%10 + 48;             // Extract tens digit
  text[2] =  temp_whole%10     + 48;             // Extract ones digit

  // extract temp_fraction and convert it to unsigned int
  temp_fraction  = temp2write << (4-RES_SHIFT);
  temp_fraction &= 0x000F;
  temp_fraction *= 625;

  // convert temp_fraction to characters
  text[4] =  temp_fraction/1000    + 48;         // Extract thousands digit
  text[5] = (temp_fraction/100)%10 + 48;         // Extract hundreds digit
  text[6] = (temp_fraction/10)%10  + 48;         // Extract tens digit
  text[7] =  temp_fraction%10      + 48;         // Extract ones digit

  // send temperature to UART
  UART1_Write_Text(text);
  UART1_Write(176);                              // degree sign
  UART1_Write('C');                              // celsius
  UART1_Write(13);                               // CR
  UART1_Write(10);                               // LF
}

unsigned int i;

void main() {



  WDTCN    = 0xDE;                               // Sequence for
  WDTCN    = 0xAD;                               // disabling the watchdog timer



  OSCICN = 0x83;                                 // Configure internal oscillator for
                                                 // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                 // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                // External Oscillator is an external
                                                 // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//

   XBR0      = 0x04;
   XBR1      = 0x00;
   XBR2 = 0x40;                                  // Enable crossbar and weak pull-ups


  P0MDOUT |= 0x01;                               // Configure P0.0 (TX) pin as push-pull

  UART1_Init(4800);                              // Initialize UART module at 4800 bps
  Delay_ms(100);                                 // Wait for UART module to stabilize
  UART1_Write_Text("Start");
  //--- main loop
  do {
    //--- perform temperature reading
    Ow_Reset();                                  // Onewire reset signal
    Ow_Write(0xCC);                              // Issue command SKIP_ROM
    Ow_Write(0x44);                              // Issue command CONVERT_T
    Delay_us(120);

    Ow_Reset();
    Ow_Write(0xCC);                              // Issue command SKIP_ROM
    Ow_Write(0xBE);                              // Issue command READ_SCRATCHPAD

    temp =  Ow_Read();
    temp = (Ow_Read() << 8) + temp;

    //--- Format and display result on Lcd
    Display_Temperature(temp);

    Delay_ms(500);
  } while (1);
}