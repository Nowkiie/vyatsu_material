/*
 * Project name:
     RS485_Slave_Example (RS485 Library demo - Slave side)
 * Copyright:
     (c) Mikroelektronika, 2009.
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
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:RS485_Board on PORT3 (remove R1 resistor from RS485 module)
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Initialize the UART module before performing RS485 init.
     - Turn on LEDs on PORT0 and PORT1.
 */

char dat[10];                          // buffer for receving/sending messages
char i,j;

sbit rs485_transceive at P3_2_bit;     // set transcieve pin

// Interrupt routine
void interrupt() org IVT_ADDR_ES {
  EA_bit = 0;                          // Clear global interrupt enable flag
  if(RI_bit) {                         // Test UART receive interrupt flag
    Rs485slave_Receive(dat);           // UART receive interrupt detected,
                                       //   receive data using RS485 communication
    RI_bit = 0;                        // Clear UART interrupt flag
    }
  EA_bit = 1;                          // Set global interrupt enable flag
}

void main(){

  P0 = 0;
  P1 = 0;

  UART1_Init(4800);                    // initialize UART1 module
  Delay_ms(100);
  Rs485slave_Init(160);                // Intialize MCU as slave, address 160

  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that message received flag is 0
  dat[6] = 0;                          // ensure that error flag is 0

  ES_bit = 1;                          // Enable UART interrupt
  RI_bit = 0;                          // Clear UART RX interrupt flag
  EA_bit = 1;                          // Enable interrupts

  while (1) {
    if (dat[5])  {                     // if an error detected, signal it by
      P1 = 0xAA;                       //   setting portd to 0xAA
      dat[5] = 0;
    }
    if (dat[4]) {                      // upon completed valid message receive
      dat[4] = 0;                      //   data[4] is set to 0xFF
      j = dat[3];
      for (i = 1; i <= dat[3]; i++) {  // show data on PORT0
        P0 = dat[i-1];
      }
      dat[0] = dat[0]+1;               // increment received dat[0]
      Delay_ms(1);
      Rs485slave_Send(dat,1);          //   and send it back to master
    }
  }
}