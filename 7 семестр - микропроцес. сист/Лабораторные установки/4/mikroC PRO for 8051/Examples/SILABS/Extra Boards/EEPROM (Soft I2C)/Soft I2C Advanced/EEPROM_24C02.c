// EEPROM 24C02 read/write library


//--------------- Performs 24C02 Init
void EEPROM_24C02_Init() {
  Soft_I2C_Init();
}

//--------------- Writes data to 24C02 EEPROM - single location
void EEPROM_24C02_WrSingle(unsigned short wAddr, unsigned short wData) {
    Soft_I2C_Start();                // issue Soft_I2C start signal
    Soft_I2C_Write(0xA2);            // send byte via Soft_I2C  (command to 24cO2)
    Soft_I2C_Write(wAddr);           // send byte (address of EEPROM location)
    Soft_I2C_Write(wData);           // send data (data to be written)
    Soft_I2C_Stop();
}

//--------------- Reads data from 24C02 EEPROM - single location (random)
unsigned short EEPROM_24C02_RdSingle(unsigned short rAddr) {
    unsigned short reslt;

    Soft_I2C_Start();                // issue Soft_I2C start signal
    Soft_I2C_Write(0xA2);            // send byte via Soft_I2C  (device address + W)
    Soft_I2C_Write(rAddr);           // send byte (data address)
    Soft_I2C_Start();                // issue Soft_I2C signal repeated start
    Soft_I2C_Write(0xA3);            // send byte (device address + R)
    reslt = Soft_I2C_Read(0u);       // Read the data (NO acknowledge)
    Delay_1us();                     // Wait for the read cycle to finish
    Soft_I2C_Stop();
    return reslt;
}

//--------------- Reads data from 24C02 EEPROM - sequential read
void EEPROM_24C02_RdSeq(unsigned short rAddr,
                        unsigned char *rdData,
                        unsigned short rLen) {
  unsigned short i;
  Soft_I2C_Start();                  // issue Soft_I2C start signal
  Soft_I2C_Write(0xA2);              // send byte via Soft_I2C  (device address + W)
  Soft_I2C_Write(rAddr);             // send byte (address of EEPROM location)
  Soft_I2C_Start();                  // issue Soft_I2C signal repeated start
  Soft_I2C_Write(0xA3);              // send byte (device address + R)
  i = 0;
  while (i < rLen) {
    rdData[i] = Soft_I2C_Read(1u);   // read data (acknowledge)
    Delay_ms(20);
    i++ ;
  }
  rdData[i] = Soft_I2C_Read(0u);     // last data is read (no acknowledge)
  Soft_I2C_Stop();
}
