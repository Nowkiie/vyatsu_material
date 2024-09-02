/*
 * Project name:
     Soft_SPI (Demonstration of the Software SPI library routines)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This project is simple demonstration how to use Software Spi Library
     functions to communicate with Port Expander.
 * Test configuration:
     MCU:             C8051F040
                      https://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F12x-13x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    ac:Port_Expander
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
 */

// Port Expander module connections
sbit SPExpanderRST at P0_6_bit;
sbit SPExpanderCS  at P0_7_bit;
// End Port Expander module connections

// Software SPI connections
sbit SoftSpi_CLK at P0_2_bit;
sbit SoftSpi_SDI at P0_3_bit;
sbit SoftSpi_SDO at P0_4_bit;
// End Software SPI connections

unsigned char received_data, i = 0;

void main() {
  WDTCN    = 0xDE;             // Sequence for
  WDTCN    = 0xAD;             // disabling the watchdog timer

  OSCICN = 0x83;               // Configure internal oscillator for
                               // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;               // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;              // External Oscillator is an external
                               // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;

  XBR2      = 0x40;             // Enable crossbar, enable weak pull-ups
  P0MDOUT |= 0b11010101;           // Configure P0.7(CS), P0.6(RST), P0.4(MOSI), P0.2(SCK)
                                   //   and P0.0(TX) pin as push-pull

  UART1_Init(4800);               // Initialize UART module at 4800 bps
  Delay_ms(100);                  // Wait for UART module to stabilize
  UART1_Write_Text("Start");
  SPI_Rd_Ptr = Soft_SPI_Read;            // Link Port Expander Library to Software SPI library

  Expander_Init(0);                      // Initialize Port Expander

  Expander_Set_DirectionPortA(0, 0x00);  // Set Expander's PORTA to be output

  Expander_Set_DirectionPortB(0,0xFF);   // Set Expander's PORTB to be input
  Expander_Set_PullUpsPortB(0,0xFF);     // Set pull-ups to all of the Expander's PORTB pins

  while(1) {                             // Endless loop
    Expander_Write_PortA(0, i++);        // Write i to expander's PORTA
    received_data = Expander_Read_PortB(0); // Read expander's PORTB
    UART1_Write(received_data);             //   and send it to UART
    
    Delay_ms(100);
  }
  
}