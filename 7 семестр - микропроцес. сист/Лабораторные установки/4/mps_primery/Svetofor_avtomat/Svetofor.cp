#line 1 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Svetofor.c"
#line 1 "c:/documents and settings/student/Рабочий стол/mps_primery/svetofor_avtomat/drv.h"
#line 13 "c:/documents and settings/student/Рабочий стол/mps_primery/svetofor_avtomat/drv.h"
unsigned char ScanKbd(void);
void init(void);
unsigned char translate(unsigned char c);
void DelayMs(unsigned int m);
void wr_EEPROM(unsigned int addr,unsigned char eedata);
unsigned char rd_EEPROM(unsigned int addr);
void clear_lcd(void);
void outcw(unsigned char c);
void outd(unsigned char c);
#line 1 "c:/documents and settings/student/Рабочий стол/mps_primery/svetofor_avtomat/1wire.h"
#line 13 "c:/documents and settings/student/Рабочий стол/mps_primery/svetofor_avtomat/1wire.h"
unsigned char read_OW (void);
void OW_write_bit (unsigned char write_data);
unsigned char OW_read_bit (void);
unsigned char OW_reset_pulse(void);
void OW_write_byte (unsigned char write_data);
unsigned char OW_read_byte (void);
#line 16 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Svetofor.c"
char key=0;
char state= 1 ;
char t;
char tr;
char tg;
char ty;
char T_FLAG = 0;
int ms = 0;

unsigned char ShiftRight(unsigned char prev)
{
 if (prev == 1)
 return 128;
 else
 prev >>= 1;
 return prev;
}



char str[17] = "привет как дела)";

void init_string()
{
 int i =  16 ;
 for (i; i <= 16; ++i)
 str[i] = ' ';
}

char pos = 16;

void out_str()
{
 int i = 0;
 outcw(0x80);
 for (i; i < 16; ++i)
 outd(str[(i+pos >= 16) ? i+pos-16 : i+pos]);
 if (pos == 0)
 pos = 16;
 --pos;
}

void main (void) {


 init();
  P0_0_bit  = 0;
  P0_1_bit  = 1;
  P0_2_bit  = 1;
  P0_4_bit  = 0;
 tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
 ty=rd_EEPROM(2); if((ty>30)||(ty<5)) ty=5;
 tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;
#line 74 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Svetofor.c"
 while (1) {
 key=ScanKbd();
 switch (state) {
 case  1 :

 clear_lcd();
 out_str();

 if (T_FLAG) { state= 5 ; T_FLAG = 0;  P0_1_bit =0;  P0_0_bit =1; }
 break;
 case  3 :

 clear_lcd();
 out_str();

 if (T_FLAG) { state= 1 ; T_FLAG = 0;  P0_2_bit =1;  P0_0_bit =0;}
 break;
 case  5 :

 clear_lcd();
 out_str();

 if (T_FLAG) { state= 3 ; T_FLAG = 0;  P0_2_bit =0;  P0_1_bit =1; }
 break;
 }
 DelayMs(100);
 if(t==0) T_FLAG=1; else t--;
 }
}
#line 116 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Svetofor.c"
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
