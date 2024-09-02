/*
 * Project name:
     SerialRAM;
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * Description:
     Many embedded systems needs some amount of volatile storage for temporary
     data. Serial SRAMs are popular choice for volatile storage because of their
     small footprint, low I/O pin requirement, low-power consumption and low cost.
     This example writes and reads data from 23K640 Serial RAM device in byte
     read/write operation mode using standard SPI communication. For more
     information about available operating modes consult 23K640 datasheet:
     http://ww1.microchip.com/downloads/en/DeviceDoc/22126C.pdf
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:RAM
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
   - SW10(1,3,5,7,8) - ON
   - SW9.1 - ON
*/

// SerialRAM connections
sbit Chip_Select at P2_3_bit;
sbit HOLD at P2_2_bit;
// End SerialRAM connections

unsigned int i;
unsigned short tmp;

// Write one byte of data to specified address
void Write_Data(unsigned int address, unsigned short dat){
  Chip_Select = 0;                                    // Select SerialRAM
  SPI1_Write(2);                                      // Write instruction
  SPI1_Write(address >> 8);                           // Sending 16 bits address
  SPI1_Write(address);
  SPI1_Write(dat);                                    // Writing one byte of data
  Chip_Select = 1;                                    // Deselect SerialRAM
 }

// Read one byte of data from specified address
unsigned short Read_Data(unsigned int address){
  Chip_Select = 0;                                    // Select Serial RAM
  SPI1_Write(3);                                      // Read instruction
  SPI1_Write(address >> 8);                           // Sending 16 bits address
  SPI1_Write(address);
  tmp = SPI1_Read(0);                                 // Read one byte of data
  Chip_Select = 1;                                    // Deselect SerialRAM
  return tmp;
}

void main() {

  WDTCN    = 0xDE;                                    // Sequence for
  WDTCN    = 0xAD;                                    // disabling the watchdog timer



  OSCICN = 0x83;                                      // Configure internal oscillator for
                                                      // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                      // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                     // External Oscillator is an external
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
   XBR1 = 0x00;                                       // Don't Route /SYSCLK to a port pin
   XBR2 = 0x40;                                       // Enable crossbar and weak pull-ups


  P0MDOUT |= 0b00000101;                              // P0.2(MOSI) and P0.0(SCK) pin as push-pull outputs
  P1MDOUT  = 0xFF;                                    // Configure PORT1 pins as push-pull outputs
  P2MDOUT |= 0b00001100;                              // Configure P2.3(CS), P2.2(HOLD) pins as push-pull outputs


  Chip_Select = 1;                                    // Deselect SerialRAM
  SPI1_Init(100000);                                  // Initialize SPI module
  HOLD = 1;                                           // Hold high when this function is not used

  for (i = 0; i < 256 ; i++){                         // Write 256 bytes of data starting from address 0x0A00
    Write_Data(i+0x0A00, i);                          // Write data to specified address
    P1 = ~Read_Data(i+0x0A00);                        // Read data and display it on port PORT1
    delay_ms(100);
  }

}