/*
 * Project name:
     Timer0_Interrupt (Using Timer 0 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This code demonstrates how to use Timer1 and it's interrupt. 
     Program toggles LEDs on PORT0 on each Timer0 interrupt.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 24.5MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Turn on PORT0 LEDs.
*/

//-------------- Interrupt handler routine
void Timer0InterruptHandler() org IVT_ADDR_ET0{

  P0 = ~P0;          // Toggle PORT0

  EA_bit = 1;        // Set global interrupt enable flag
  TR1_bit = 1;       // Run Timer1
}

void main() {
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                // disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC = 0x04;                  // Enable missing clock detector

  // Consult datasheet for more details about starting External oscillator
  // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                  // External Oscillator is an external
                                  // crystal (no divide by 2 stage)
  OSCXCN |= 7;

  // Step 2. Wait at least 1 ms.
  Delay_ms(5);

  // Step 3. Poll for XTLVLD => ‘1’.
  while ((OSCXCN & 0x80) != 0x80);


  // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;//

  XBR2      = 0x40;
 
  P0MDOUT = 0xFF;    // Port 0 as output

  P0 = 0;            // Clear Port 0

  TF0_bit = 0;       // Ensure that Timer0 interrupt flag is cleared
  ET0_bit = 1;       // Enable Timer0 interrupt
  EA_bit  = 1;       // Set global interrupt enable

  GATE0_bit = 0;     // Clear this flag to enable Timer0 whenever TR0 bit is set.
  C_T0_bit  = 0;     // Set Timer operation: Timer0 counts the divided-down systam clock.
  T0M1_bit  = 1;     // Set Timer Mode 2
  T0M0_bit  = 0;
  
  SCA0_bit = 0;      // System clock divided by 48
  SCA1_bit = 1;

  TR0_bit = 0;       // Turn off Timer0
  TH0 = 0x00;        // Set Timer0 high byte
  TL0 = 0x00;        // Set Timer0 low byte
  TR0_bit = 1;       // Run Timer0
}