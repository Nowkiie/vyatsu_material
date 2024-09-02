#line 1 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR_NORMALNIY.c"
#line 1 "d:/mikroc pro for 8051/svetofor_avtomat/svetofor_avtomat/drv.h"
#line 13 "d:/mikroc pro for 8051/svetofor_avtomat/svetofor_avtomat/drv.h"
unsigned char ScanKbd(void);
void init(void);
unsigned char translate(unsigned char c);
void DelayMs(unsigned int m);
void wr_EEPROM(unsigned int addr,unsigned char eedata);
unsigned char rd_EEPROM(unsigned int addr);
void clear_lcd(void);
void outcw(unsigned char c);
void outd(unsigned char c);
#line 1 "d:/mikroc pro for 8051/svetofor_avtomat/svetofor_avtomat/1wire.h"
#line 13 "d:/mikroc pro for 8051/svetofor_avtomat/svetofor_avtomat/1wire.h"
unsigned char read_OW (void);
void OW_write_bit (unsigned char write_data);
unsigned char OW_read_bit (void);
unsigned char OW_reset_pulse(void);
void OW_write_byte (unsigned char write_data);
unsigned char OW_read_byte (void);
#line 14 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR_NORMALNIY.c"
char key=0;
char state= 1 ;
char t;
char tr;
char tg;
char T_FLAG = 0;
int ms = 0;

void main (void) {


 init();
  P0_0_bit  = 0;
  P0_1_bit  = 1;
  P0_2_bit  = 1;
  P0_4_bit  = 0;
 tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
 tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;

 for(t=0;t!=0;t++);
 t = 10*tr;


 while (1) {
 key=ScanKbd();
 if (key == 1){
 clear_lcd(); outcw(0x80); outd('D');




 } else{
 clear_lcd(); outcw(0x80); outd('X');

 }


 }
}
#line 66 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR_NORMALNIY.c"
void DelayMs(unsigned int m){


 ms=0;
 WMCON.WDTRST=1;
 while(ms!=m) continue;
}

void Timer1InterruptHandler() org IVT_ADDR_ET1{

 EA_bit = 0;
 TF1_bit = 0;

 TR1_bit = 0;
 TH1 = 0xFC;
 TL1 = 0x18;


 ms++;

 EA_bit = 1;
 TR1_bit = 1;
}

void INT0_Interrupt() org IVT_ADDR_EX0 {
 EA_bit = 0;
  P0_4_bit =~ P0_4_bit ;
 EA_bit = 1;
}
