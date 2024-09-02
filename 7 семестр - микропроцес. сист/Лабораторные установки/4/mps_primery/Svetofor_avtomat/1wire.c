#include "1wire.h"

//unsigned char d;  // счетчик задержки

/**********************************************************************
* Function:        unsigned char read_OW (void)
* PreCondition:    None
* Input:		   None
* Output:		   Return the status of OW pin.
* Overview:		   Configure as Input pin and Read the status of OW_PIN
***********************************************************************/
unsigned char read_OW (void)
{
	unsigned char read_data=0;

	WIRE1_PIN = 1;

	 if (WIRE1_PIN==1)
	 	read_data = 1;
	 else
		read_data = 0;

	return read_data;
}  

/**********************************************************************
* Function:        unsigned char OW_reset_pulse(void)
* PreCondition:    None
* Input:                   None        
* Output:                   Return the Presense Pulse from the slave.        
* Overview:                   Initialization sequence start with reset pulse.
*                                   This code generates reset sequence as per the protocol
***********************************************************************/

unsigned char OW_reset_pulse(void)

{
        unsigned char presence_detect;
        
        WIRE1_PIN=0;                                 // Drive the bus low
         
        Delay_us(240);                                  // delay 480 microsecond (us)
        Delay_us(240);

        WIRE1_PIN=1;                                   // Release the bus
        
        Delay_us(70);                                // delay 70 microsecond (us)
        
        presence_detect = read_OW();        //Sample for presence pulse from slave

        Delay_us(205);                                  // delay 410 microsecond (us)
        Delay_us(205);
        
        WIRE1_PIN=1;                            // Release the bus
        
        return presence_detect;
}        

/**********************************************************************
* Function:        void OW_write_bit (unsigned char write_data)
* PreCondition:    None
* Input:                   Write a bit to 1-wire slave device.
* Output:                   None
* Overview:                   This function used to transmit a single bit to slave device.
***********************************************************************/

void OW_write_bit (unsigned char write_bit)
{
        if (write_bit)
        {
                //writing a bit '1'
                WIRE1_PIN=0;                                 // Drive the bus low
                Delay_us(6);                                // delay 6 microsecond (us)
                WIRE1_PIN=1;                                  // Release the bus
                Delay_us(6);                                // delay 64 microsecond (us)
        }
        else
        {
                //writing a bit '0'
                WIRE1_PIN=0;                                 // Drive the bus low
                Delay_us(60);                                // delay 60 microsecond (us)
                WIRE1_PIN=1;                                  // Release the bus
                Delay_us(10);                                // delay 10 microsecond for recovery (us)
        }
}        


/**********************************************************************
* Function:        unsigned char OW_read_bit (void)
* PreCondition:    None
* Input:                   None
* Output:                   Return the status of the OW PIN
* Overview:                   This function used to read a single bit from the slave device.
***********************************************************************/

unsigned char OW_read_bit (void)
{
        unsigned char read_data; 
        //reading a bit 
        WIRE1_PIN=0;                                                 // Drive the bus low
        Delay_us(6);                                                // delay 6 microsecond (us)
        WIRE1_PIN=1;                                                  // Release the bus
        Delay_us(9);                                                // delay 9 microsecond (us)

        read_data = read_OW();                                       //Read the status of OW_PIN

        Delay_us(55);                                                // delay 55 microsecond (us)
        return read_data;
}

/**********************************************************************
* Function:        void OW_write_byte (unsigned char write_data)
* PreCondition:    None
* Input:                   Send byte to 1-wire slave device
* Output:                   None
* Overview:                   This function used to transmit a complete byte to slave device.
***********************************************************************/

void OW_write_byte (unsigned char write_data)
{
        unsigned char loop;
        
        for (loop = 0; loop < 8; loop++)
        {
                OW_write_bit(write_data & 0x01);         //Sending LS-bit first
                write_data >>= 1;                                        // shift the data byte for the next bit to send
        }        
}        

/**********************************************************************
* Function:        unsigned char OW_read_byte (void)
* PreCondition:    None
* Input:                   None
* Output:                   Return the read byte from slave device
* Overview:                   This function used to read a complete byte from the slave device.
***********************************************************************/

unsigned char OW_read_byte (void)
{
        unsigned char loop, result=0;
        
        for (loop = 0; loop < 8; loop++)
        {
                
                result >>= 1;                                 // shift the result to get it ready for the next bit to receive
                if (OW_read_bit())
                result |= 0x80;                                // if result is one, then set MS-bit
        }
        return result;                                        
}        