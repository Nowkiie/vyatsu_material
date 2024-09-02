//EEPROM_24C02 library header file

void EEPROM_24C02_Init();
void EEPROM_24C02_WrSingle(unsigned short wAddr, unsigned short wData);
unsigned short EEPROM_24C02_RdSingle(unsigned short rAddr);
void EEPROM_24C02_RdSeq(unsigned short rAddr,
                        unsigned char *rdData,
                        unsigned short rLen);
