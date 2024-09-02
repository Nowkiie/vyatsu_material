/*
 * Project name:
     Timer1_Interrupt (Using Timer 1 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code demonstrates how to use Timer1 and it's interrupt. 
     Program toggles LEDs on PORT0 on each Timer1 interrupt.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn on PORT0 LEDs.
*/

//-------------- Interrupt handler routine
void Timer1InterruptHandler() org IVT_ADDR_ET1{

  EA_bit = 0;        // Clear global interrupt enable flag

  TR1_bit = 0;       // Stop Timer1
  TH1 = 0x00;        // Reset Timer1 high byte
  TL1 = 0x00;        // Reset Timer1 low byte
   
  P0 = ~P0;          // Toggle PORT0

  EA_bit = 1;        // Set global interrupt enable flag
  TR1_bit = 1;       // Run Timer1
}

void main() {
 
  P0  = 0;           // Initialize PORT0

  TF1_bit = 0;       // Ensure that Timer1 interrupt flag is cleared
  ET1_bit = 1;       // Enable Timer1 interrupt
  EA_bit  = 1;       // Set global interrupt enable

  GATE1_bit = 0;     // Clear this flag to enable Timer1 whenever TR1 bit is set.
  C_T1_bit  = 0;     // Set Timer operation: Timer1 counts the divided-down systam clock.
  M11_bit   = 0;     // M11_M01 = 01    =>   Mode 1(16-bit Timer/Counter)
  M01_bit   = 1;

  TR1_bit = 0;       // Turn off Timer1
  TH1 = 0x00;        // Set Timer1 high byte
  TL1 = 0x00;        // Set Timer1 low byte
  TR1_bit = 1;       // Run Timer1

}
