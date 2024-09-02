/*
 * Project name:
     Soft_SPI (Demonstration of the Software SPI library routines)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20090601:
       - initial release;
 * Description:
     This project is simple demonstration how to use Software Spi Library
     functions to communicate with Port Expander.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:Port_Expander_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn ON the PORT2 LEDs.
 */

// Port Expander module connections
sbit  SPExpanderRST at P1_0_bit;
sbit  SPExpanderCS  at P1_1_bit;
// End Port Expander module connections

// Software SPI connections
sbit SoftSpi_CLK at P1_7_bit;
sbit SoftSpi_SDI at P1_6_bit;
sbit SoftSpi_SDO at P1_5_bit;
// End Software SPI connections

char (*SPI_Rd_Ptr)(char);                // Pointer to SPI_Read function
                                         //   used by Port Expander Library
unsigned char i = 0;

void main() {

  SPI_Rd_Ptr = Soft_SPI_Read;            // Link Port Expander Library to Software SPI library

  Expander_Init(0);                      // Initialize Port Expander

  Expander_Set_DirectionPortA(0, 0x00);  // Set Expander's PORTA to be output

  Expander_Set_DirectionPortB(0,0xFF);   // Set Expander's PORTB to be input
  Expander_Set_PullUpsPortB(0,0xFF);     // Set pull-ups to all of the Expander's PORTB pins

  while(1) {                             // Endless loop
    Expander_Write_PortA(0, i++);        // Write i to expander's PORTA
    P2 = Expander_Read_PortB(0);         // Read expander's PORTB and write it to PORT2 LEDs
    Delay_ms(100);
  }
  
}