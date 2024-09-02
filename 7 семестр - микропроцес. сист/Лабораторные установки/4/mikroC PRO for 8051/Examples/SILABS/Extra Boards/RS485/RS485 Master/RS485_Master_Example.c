/*
 * Project name:
     RS485_Master_Example (RS485 Library demo - Master side)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a simple demonstration on how to use the RS485 library.
     It is being used in pair with the RS485_Slave_Example project. Master (this
     machine) initiates communication with slave by sending 1 byte of data to
     the slave with designated slave address (160). The slave accepts data,
     increments it and sends it back to the master.
     The data received is shown on PORT0, Error on receive on PORT1 and number of
     consecutive unsuccessful retries on PORT2.
     Several situations are shown here:
       - RS485 Master Init sequence;
       - Data sending master-to-slave with designated slave address;
       - Data sending master-to-slave with broadcast slave address (50);
       - Handling of unsuccessful master-slave communication (connection reset);
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
    Rs485master_Receive(dat);          // UART receive interrupt detected,
                                       //   receive data using RS485 communication
    RI0_bit = 0;                       // Clear UART interrupt flag
    }
  EA_bit = 1;                          // Set global interrupt enable flag
}

void main(){
  long cnt = 0;

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

  Rs485master_Init();                  // initialize MCU as Master
  dat[0] = 0xAA;
  dat[1] = 0xF0;
  dat[2] = 0x0F;
  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that error flag is 0
  dat[6] = 0;

  Rs485master_Send(dat,1,160);

  ES0_bit = 1;                         // Enable UART interrupt
  RI0_bit = 0;                         // Clear UART RX interrupt flag
  EA_bit = 1;                          // Enable interrupts

  while (1){
                                       // upon completed valid message receiving
                                       //   data[4] is set to 255
    cnt++;
    if (dat[5])  {                     // if an error detected, signal it
      P1 = 0xAA;                       //   by setting PORT1 to 0xAA
    }
    if (dat[4]) {                      // if message received successfully
      cnt = 0;
      dat[4] = 0;                      // clear message received flag
      j = dat[3];
      for (i = 1; i <= dat[3]; i++) {  // show data on PORT0
        P0 = dat[i-1];
      }
      dat[0] = dat[0]+1;               // increment received dat[0]
      Delay_ms(1);
      Rs485master_Send(dat,1,160);     // send back to slave

    }
    if (cnt > 100000) {
      P2++;
      cnt = 0;
      Rs485master_Send(dat,1,160);
      if (P2 > 10)                     // if sending failed 10 times
        Rs485master_Send(dat,1,50);    //   send message on broadcast address
    }
  }
}