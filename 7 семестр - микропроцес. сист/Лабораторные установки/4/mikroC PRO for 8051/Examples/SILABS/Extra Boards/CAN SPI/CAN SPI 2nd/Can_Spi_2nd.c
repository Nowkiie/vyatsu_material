/*
 * Project name:
     Can_Spi_2nd (CAN Network demonstration with mikroE's CAN-SPI module)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is a simple demonstration of using CAN-SPI module; with minor
     adjustments, it should work with any other MCU that has a SPI module.
     This code demonstrates how to use CANSPI library functions and procedures.
     It is used together with the CanSpi_1st example (on second MCU), and it can
     be used to test the connection of MCU to the CAN network.
     This node receives data, increments it by 1 and send it back to the 1st node.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 24.5MHz
     Ext. Modules:    ac:CAN_SPI_Board on PORT0
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Consult the CAN standard about CAN bus termination resistance.
     - Turn on LEDs on PORT1.
 */

unsigned char Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags; // can flags
unsigned char Rx_Data_Len;                                   // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const long ID_1st = 12111, ID_2nd = 3;                       // node IDs
long Rx_ID;

// CANSPI module connections
sbit CanSpi_CS  at P0_5_bit;
sbit CanSpi_Rst at P0_4_bit;
// End CANSPI module connections

void main() {
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                //   disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC = 0x04;                      // Enable missing clock detector


 // Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                     // External Oscillator is an external
                                      // crystal (no divide by 2 stage)
  OSCXCN |= 7;

  // Step 2. Wait at least 1 ms.
  Delay_ms(5);

  // Step 3. Poll for XTLVLD => �1�.
  while ((OSCXCN & 0x80) != 0x80);


  // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;//

  XBR2 = 0x40;                        // Enable crossbar and weak pull-ups

  P0MDOUT |= 0b00110101;              // P0.2(MOSI) and P0.0(SCK) pin as push-pull outputs
                                      // P0.4(SCK) and P0.5(RST) pin as push-pull outputs
  P1MDOUT |= 0xFF;
  
  P1 = 0;

  Can_Init_Flags = 0;                                         //
  Can_Send_Flags = 0;                                         // clear flags
  Can_Rcv_Flags  = 0;                                         //

  Can_Send_Flags = _CANSPI_TX_PRIORITY_0 &                    // form value to be used
                   _CANSPI_TX_XTD_FRAME &                     //   with CANSPIWrite
                   _CANSPI_TX_NO_RTR_FRAME;

  Can_Init_Flags = _CANSPI_CONFIG_SAMPLE_THRICE &             // Form value to be used
                   _CANSPI_CONFIG_PHSEG2_PRG_ON &             //  with CANSPIInit
                   _CANSPI_CONFIG_XTD_MSG &
                   _CANSPI_CONFIG_DBL_BUFFER_ON &
                   _CANSPI_CONFIG_VALID_XTD_MSG &
                   _CANSPI_CONFIG_LINE_FILTER_OFF;

  SPI1_Init(100000);                                                              // initialize SPI1 module
  
  CANSPIInitialize(1,3,3,3,1,Can_Init_Flags);                                 // initialize external CANSPI module
  CANSPISetOperationMode(_CANSPI_MODE_CONFIG,0xFF);                           // set CONFIGURATION mode
  CANSPISetMask(_CANSPI_MASK_B1,-1,_CANSPI_CONFIG_XTD_MSG);                   // set all mask1 bits to ones
  CANSPISetMask(_CANSPI_MASK_B2,-1,_CANSPI_CONFIG_XTD_MSG);                   // set all mask2 bits to ones
  CANSPISetFilter(_CANSPI_FILTER_B2_F3,ID_1st,_CANSPI_CONFIG_XTD_MSG);        // set id of filter B2_F3 to 1st node ID

  CANSPISetOperationMode(_CANSPI_MODE_NORMAL,0xFF);                           // set NORMAL mode

  while (1) {                                                                 // endless loop
    Msg_Rcvd = CANSPIRead(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags); // receive message
    if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                      // if message received check id
      P1 = RxTx_Data[0];                                                      // id correct, output data at PORT0
      RxTx_Data[0]++ ;                                                        // increment received data
      CANSPIWrite(ID_2nd, RxTx_Data, 1, Can_Send_Flags);                      // send incremented data back
    }
  }
}