/*
 * Project name:
     RS485_Slave_Example (RS485 Library demo - Slave side)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a simple demonstration on how to use the RS485 library.
     It is being used in pair with the RS485_Master_Example project. Slave (this
     machine) initializes itself (on address 160) and waits to receive data from
     the master. Then it increments the first byte of received data and sends it
     back to the master. The data received is shown on PORT0 and Error on
     receive on PORT1.
     Several situations are shown here:
       - RS485 Slave Init sequence;
       - Data sending slave-to-master;
     Also shown here, but not strictly related to RS485 library, is:
       - Function calling from the interrupt routine - which data is to be saved,
         and how.
     For further explanations on RS485 library, please consult Help.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    ac:RS485  RS485 on PORT0
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Initialize the UART module before performing RS485 init.
 */

char dat[10];                          // buffer for receving/sending messages
char i,j;

sbit rs485_transceive at P0_2_bit;     // set transcieve pin

// Interrupt routine
void interrupt() org IVT_ADDR_ES0 {
  EA_bit = 0;                          // Clear global interrupt enable flag
  if(RI0_bit) {                        // Test UART receive interrupt flag
    Rs485slave_Receive(dat);           // UART receive interrupt detected,
                                       //   receive data using RS485 communication
    RI0_bit = 0;                       // Clear UART interrupt flag
    }
  EA_bit = 1;                          // Set global interrupt enable flag
}

void main(){

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
//


  XBR2     = 0x40;             // Enable crossbar, enable weak pull-ups
  P0MDOUT |= 0b00000101;               // Configure P0.0 (TX) and P0.2 (R/T) pin as push-pull

  UART1_Init(4800);                    // initialize UART1 module
  Delay_ms(100);
  Rs485slave_Init(160);                // Intialize MCU as slave, address 160

  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that message received flag is 0
  dat[6] = 0;                          // ensure that error flag is 0

  ES0_bit = 1;                         // Enable UART interrupt
  RI0_bit = 0;                         // Clear UART RX interrupt flag
  EA_bit = 1;                          // Enable interrupts

  while (1) {
    if (dat[5])  {                     // if an error detected, signal it by
      P1 = 0xAA;                       //   setting portd to 0xAA
      dat[5] = 0;
    }
    if (dat[4]) {                      // upon completed valid message receive
      dat[4] = 0;                      //   data[4] is set to 0xFF
      j = dat[3];
      for (i = 1; i <= dat[3];i++) {   // show data on PORT0
        P0 = dat[i-1];
      }
      dat[0] = dat[0]+1;               // increment received dat[0]
      Delay_ms(1);
      Rs485slave_Send(dat,1);          //   and send it back to master
    }
  }
}