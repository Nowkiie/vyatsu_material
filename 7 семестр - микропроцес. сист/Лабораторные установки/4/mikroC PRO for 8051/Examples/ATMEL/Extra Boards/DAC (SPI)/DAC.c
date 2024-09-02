/*
 * Project name:
      SPI (Driving external Digital-to-Analog converter)
 * Copyright:
     (c) MikroElektronika, 2012
 * Revision History:
     20080930:
       - initial release;
     20111011;
       - revision (JK);
 * Description:
     This is a sample program which demonstrates the use of the Microchip's
     MCP4921 12-bit D/A converter. This device accepts digital
     input (number from 0..4095) and transforms it to the output voltage,
     ranging from 0..Vref. In this example the DAC communicates with MCU
     through the SPI communication.
     Buttons P0.0 and P0.1 are used to change value sent to DAC.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    ac:DAC_Board on PORT1
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
      - Put button jumper into VCC position and pull-down PORT0.
 */

// DAC module connections
sbit Chip_Select at P1_1_bit;
// End DAC module connections

unsigned int value;

void InitMain() {
  Chip_Select = 1;                       // Deselect DAC
  SPI1_Init();                           // Initialize SPI module
}

// DAC increments (0..4095) --> output voltage (0..Vref)
void DAC_Output(unsigned int valueDAC) {
  char temp;

  Chip_Select = 0;                       // Select DAC chip

  // Send High Byte
  temp = (valueDAC >> 8) & 0x0F;         // Store valueDAC[11..8] to temp[3..0]
  temp |= 0x30;                          // Define DAC setting, see MCP4921 datasheet
  SPI1_Write(temp);                      // Send high byte via SPI

  // Send Low Byte
  temp = valueDAC;                       // Store valueDAC[7..0] to temp[7..0]
  SPI1_Write(temp);                      // Send low byte via SPI

  Chip_Select = 1;                       // Deselect DAC chip
}

void main() {
  InitMain();                            // Perform main initialization

  value = 2048;                          // When program starts, DAC gives
                                         //   the output in the mid-range

 while (1) {                             // Endless loop

    if ((P0_0_bit) && (value < 4095)) {   // If P0.0 button is pressed
      value++;                           //   increment value
      }
    else {
      if ((P0_1_bit) && (value > 0)) {    // If P0.1 button is pressed
        value--;                         //   decrement value
        }
      }
    DAC_Output(value);                   // Send value to DAC chip
    Delay_ms(1);                         // Slow down key repeat pace
  }
}