#line 1 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR.c"
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
#line 16 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR.c"
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
 switch (state) {
 case  1 :

 clear_lcd(); outcw(0x80); outd('Ê');

 if (T_FLAG) { state= 2 ; T_FLAG = 0; t=20;  P0_1_bit =0; }
 else if (key == '8') { state= 6 ;  P0_0_bit =1; }
 break;
 case  2 :

 clear_lcd(); outcw(0x80); outd('Ê'); outd('ð'); outd('.'); outd('-');
 outd('æ'); outd('.');
 if (T_FLAG) { state= 3 ; T_FLAG = 0; t=10*tg;  P0_0_bit =1;  P0_1_bit =1;  P0_2_bit =0; }
 else if (key == '8') { state= 6 ;  P0_0_bit =1;  P0_1_bit =1; }
 break;
 case  3 :

 clear_lcd(); outcw(0x80); outd('Ç');

 if (T_FLAG) { state= 4 ; T_FLAG = 0; t=3; }
 else if (key == '8') { state= 6 ;  P0_2_bit =1; }
 break;
 case  4 :
  P0_2_bit =0; DelayMs(500);
  P0_2_bit =1; DelayMs(400);
 if (T_FLAG) { state= 5 ; T_FLAG = 0; t=20;  P0_1_bit =0; }
 break;
 case  5 :

 clear_lcd(); outcw(0x80); outd('Æ');

 if (T_FLAG) { state= 1 ; T_FLAG = 0; t=10*tr;  P0_1_bit =1;  P0_0_bit =0; }
 else if (key == '8') { state= 6 ;  P0_1_bit =1; }
 break;
 case  6 :

 clear_lcd(); outcw(0x80); outd('t'); outd('ê'); outd('=');
 outd(tr/10+48); outd(tr%10+48); outd('c');
 switch(key) {
 case '7': if (tr>5) tr--; break;
 case '9': if (tr<30) tr++; break;
 case '8': wr_EEPROM(0,tr); state= 7 ; break;
 }
 break;
 case  7 :

 clear_lcd(); outcw(0x80); outd('t'); outd('ç'); outd('=');
 outd(tg/10+48); outd(tg%10+48); outd('c');
 switch(key) {
 case '7': if (tg>5) tg--; break;
 case '9': if (tg<30) tg++; break;
 case '8': wr_EEPROM(1,tg); state= 1 ; T_FLAG = 0; t=10*tr;  P0_0_bit =0; break;
 }
 break;
 }
 DelayMs(100);
 if(t==0) T_FLAG=1; else t--;
 }
}
#line 113 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/SVETOFOR.c"
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
