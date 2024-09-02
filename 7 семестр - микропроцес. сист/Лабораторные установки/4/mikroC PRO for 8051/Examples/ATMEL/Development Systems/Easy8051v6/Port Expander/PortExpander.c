/*
 * Project name:
     PortExpander (Demonstration of the Port Expander library routines)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is simple demonstration how to use Port Expander Library functions.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6 - ac:PortExpander
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    none
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn on Port Expander switches SW6.2, SW6.3, SW6.4, SW6.5, SW6.6, SW6.7, SW6.8
     - Turn on PORT2 (SW7.3).
 */

// Port Expander module connections
sbit  SPExpanderRST at P3_7_bit;
sbit  SPExpanderCS  at P3_4_bit;
// End Port Expander module connections

unsigned char i = 0;

void main() {

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                           // Initialize SPI module used with PortExpander

  Expander_Init(0);                      // Initialize Port Expander

  Expander_Set_DirectionPortA(0, 0x00);  // Set Expander's PORTA to be output

  Expander_Set_DirectionPortB(0,0xFF);   // Set Expander's PORTB to be input
  Expander_Set_PullUpsPortB(0,0xFF);     // Set pull-ups to all of the Expander's PORTB pins

  while(1) {                             // Endless loop
    Expander_Write_PortA(0, i++);        // Write i to expander's PORTA
    P2 = ~Expander_Read_PortB(0);        // Read expander's PORTB and write it to LEDs
    Delay_ms(100);
  }
}