/*
  Serial Flash driver
*/

#include <built_in.h>

/************************************************************************
* SerialFlash Commands
* -----------------------------------------------------------------------
* Overview: Constants that represent commands
* Input: none
* Output: none
************************************************************************/
const unsigned short _SERIAL_FLASH_CMD_RDID  = 0x9F;  // 25P80
const unsigned short _SERIAL_FLASH_CMD_READ  = 0x03;
const unsigned short _SERIAL_FLASH_CMD_WRITE = 0x02;
const unsigned short _SERIAL_FLASH_CMD_WREN  = 0x06;
const unsigned short _SERIAL_FLASH_CMD_RDSR  = 0x05;
const unsigned short _SERIAL_FLASH_CMD_ERASE = 0xC7;   // 25P80
const unsigned short _SERIAL_FLASH_CMD_EWSR  = 0x06;   // 25P80
const unsigned short _SERIAL_FLASH_CMD_WRSR  = 0x01;
const unsigned short _SERIAL_FLASH_CMD_SER   = 0xD8;    //25P80

extern sfr sbit CS_Serial_Flash_bit;
//extern sfr sbit CS_Serial_Flash_Direction_bit;

/************************************************************************
* Function SerialFlash_init()
* -----------------------------------------------------------------------
* Overview: Function that initializes SerialFlash by setting Chip select
* Input: none
* Output: none
************************************************************************/
void SerialFlash_init(){
  CS_Serial_Flash_bit = 1;
//  CS_Serial_Flash_Direction_bit = 0;
}

void SerialFlash_WriteEnable(){
  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_WREN);
  CS_Serial_Flash_bit = 1;
}


unsigned char SerialFlash_IsWriteBusy(){
  unsigned char temp;

  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_RDSR);
  temp = SPI_Rd_Ptr(0);
  CS_Serial_Flash_bit = 1;

  return (temp&0x01);
}

void SerialFlash_WriteByte(unsigned char _data, unsigned long address){
    SerialFlash_WriteEnable();
    
    CS_Serial_Flash_bit = 0;
    SPI_Wr_Ptr(_SERIAL_FLASH_CMD_WRITE);
    SPI_Wr_Ptr(Higher(address));
    SPI_Wr_Ptr(Hi(address));
    SPI_Wr_Ptr(Lo(address));
    SPI_Wr_Ptr(_data);
    CS_Serial_Flash_bit = 1;

    // Wait for write end
    while(SerialFlash_isWriteBusy());
}

void SerialFlash_WriteWord(unsigned int _data, unsigned long address){
  SerialFlash_WriteByte(Hi(_data),address);
  SerialFlash_WriteByte(Lo(_data),address+1);
}

unsigned char SerialFlash_ReadID(void){
  unsigned char temp;

  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_RDID);
  temp = SPI_Rd_Ptr(0);
  CS_Serial_Flash_bit = 1;
  
  return temp;
}

unsigned char SerialFlash_ReadByte(unsigned long address){
  unsigned char temp;

  CS_Serial_Flash_bit = 0;

  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_READ);
  SPI_Wr_Ptr(Higher(address));
  SPI_Wr_Ptr(Hi(address));
  SPI_Wr_Ptr(Lo(address));
  temp = SPI_Rd_Ptr(0);

  CS_Serial_Flash_bit = 1;
  return temp;
}

unsigned int SerialFlash_ReadWord(unsigned long address){
  unsigned int temp;

  Hi(temp) = SerialFlash_ReadByte(address);
  Lo(temp) = SerialFlash_ReadByte(address+1);

  return temp;
}

unsigned char SerialFlash_WriteArray(unsigned long address, unsigned char* pData, unsigned int nCount){
  unsigned long addr;
  unsigned char* pD;
  unsigned int counter;

  addr = address;
  pD   = pData;

  // WRITE

  for(counter = 0; counter < nCount; counter++){
      SerialFlash_WriteByte(*pD++, addr++);
  }


  // VERIFY

  for (counter=0; counter < nCount; counter++){
    if (*pData != SerialFlash_ReadByte(address))
        return 0;
    pData++;
    address++;
  }

  return 1;
}

void SerialFlash_ReadArray(unsigned long address, unsigned char* pData, unsigned int nCount){
  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_READ);
  SPI_Wr_Ptr(Higher(address));
  SPI_Wr_Ptr(Hi(address));
  SPI_Wr_Ptr(Lo(address));
  
  while(nCount--){
    *pData++ = SPI_Rd_Ptr(0);
  }
  CS_Serial_Flash_bit = 1;
}

void SerialFlash_ChipErase(void){

  SerialFlash_WriteEnable();

  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_ERASE);
  CS_Serial_Flash_bit = 1;

  // Wait for write end
  while(SerialFlash_IsWriteBusy());
}

void SerialFlash_ResetWriteProtection(){

  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_EWSR);
  CS_Serial_Flash_bit = 1;


  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_EWSR);
  SPI_Wr_Ptr(0);
  CS_Serial_Flash_bit = 1;
}

void SerialFlash_SectorErase(unsigned long address){

  SerialFlash_WriteEnable();

  CS_Serial_Flash_bit = 0;
  SPI_Wr_Ptr(_SERIAL_FLASH_CMD_SER);
  SPI_Wr_Ptr(Higher(address));
  SPI_Wr_Ptr(Hi(address));
  SPI_Wr_Ptr(Lo(address));
  CS_Serial_Flash_bit = 1;

  // Wait for write end
  while(SerialFlash_IsWriteBusy());
}
