/*
 * Project name:
     Can_Spi_2nd (CAN Network demonstration with mikroE's CAN-SPI module)
 * Copyright:
     (c) Mikroelektronika, 2009.
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
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:CAN_SPI_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Consult the CAN standard about CAN bus termination resistance.
     - Turn on LEDs on PORT0.
 */

unsigned char Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags; // can flags
unsigned char Rx_Data_Len;                                   // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const long ID_1st = 12111, ID_2nd = 3;                       // node IDs
long Rx_ID;

// CANSPI module connections
sbit CanSpi_CS  at P1_0_bit;
sbit CanSpi_Rst at P1_2_bit;
// End CANSPI module connections

void main() {
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

  SPI1_Init();                                                                // initialize SPI1 module
  
  CANSPIInitialize(1,3,3,3,1,Can_Init_Flags);                                 // initialize external CANSPI module
  CANSPISetOperationMode(_CANSPI_MODE_CONFIG,0xFF);                           // set CONFIGURATION mode
  CANSPISetMask(_CANSPI_MASK_B1,-1,_CANSPI_CONFIG_XTD_MSG);                   // set all mask1 bits to ones
  CANSPISetMask(_CANSPI_MASK_B2,-1,_CANSPI_CONFIG_XTD_MSG);                   // set all mask2 bits to ones
  CANSPISetFilter(_CANSPI_FILTER_B2_F3,ID_1st,_CANSPI_CONFIG_XTD_MSG);        // set id of filter B2_F3 to 1st node ID

  CANSPISetOperationMode(_CANSPI_MODE_NORMAL,0xFF);                           // set NORMAL mode

  while (1) {                                                                 // endless loop
    Msg_Rcvd = CANSPIRead(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags); // receive message
    if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                      // if message received check id
      P0 = RxTx_Data[0];                                                      // id correct, output data at PORT0
      RxTx_Data[0]++ ;                                                        // increment received data
      CANSPIWrite(ID_2nd, RxTx_Data, 1, Can_Send_Flags);                      // send incremented data back
    }
  }
}