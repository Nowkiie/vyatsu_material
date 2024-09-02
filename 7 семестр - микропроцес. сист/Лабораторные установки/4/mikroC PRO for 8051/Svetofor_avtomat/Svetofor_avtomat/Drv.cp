#line 1 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/Drv.c"
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
#line 5 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/Drv.c"
void init(void){
unsigned char i;


 WMCON = 0b11111001;


 WMCON|=0x08;
 WMCON&=0xfb;


 PCON |= 0x80;
 SCON = 0x72;
 TMOD = 0x22;
 TH1 = 0xF5;
 ES_bit = 0;


 TF1_bit = 0;
 ET1_bit = 1;
 EA_bit = 1;

 GATE1_bit = 0;
 C_T1_bit = 0;
 M11_bit = 0;
 M01_bit = 1;

 TR1_bit = 0;
 TH1 = 0xFC;
 TL1 = 0x18;
 TR1_bit = 1;



 P3=0xff;
 EX0_bit = 1;



 DelayMs(30);
  P3_5_bit  = 0;
 outcw(0x3C);
 outcw(0x0C);
 outcw(0x01);
 outcw(0x06);
 outcw(0x40);
 for(i=0;i<8;i++) outd(0);
 for(i=0;i<8;i++) outd(0x10);
 for(i=0;i<8;i++) outd(0x18);
 for(i=0;i<8;i++) outd(0x1C);
 for(i=0;i<8;i++) outd(0x1E);
 for(i=0;i<8;i++) outd(0x1F);
}

unsigned char ScanKbd(void) {
 unsigned char i;
 unsigned char kp = 0;
 P0 = P0&0x1F|0xC0;
 for(i=0;i<10;i++);
 if (!P1_0_bit) kp = '7';



 P0 = P0&0x1F|0xA0;
 for(i=0;i<10;i++);
 if (!P1_0_bit) kp = '8';



 P0 = P0&0x1F|0x60;
 for(i=0;i<10;i++);
 if (!P1_0_bit) kp = '9';



 return kp;
}


unsigned char translate(unsigned char c){
switch (c){







 case 'Æ': return 0xA3;
 case 'Ç': return 0xA4;


 case 'Ê': return 'K';
#line 126 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/Drv.c"
 case 'æ': return 0xB6;
 case 'ç': return 0xB7;








 case 'ð': return 'p';
 case 'ñ': return 'c';
#line 152 "D:/mikroC PRO for 8051/Svetofor_avtomat/Svetofor_avtomat/Drv.c"
 default: return c;
 }
}

void wr_EEPROM(unsigned int addr,unsigned char eedata)
{

 DP0L=addr;
 DP0H=addr>>8;
 WMCON|=0x10;
 ACC = eedata;
 asm movx @DPTR,A;
 WMCON&=0xef;
}

unsigned char rd_EEPROM(unsigned int addr)
{

 DP0L=addr;
 DP0H=addr>>8;
 asm movx A,@DPTR;
 return ACC;
}

void clear_lcd(void){
 unsigned char i;
 outcw(0x80);
 for(i=0;i<16;i++)
 outd(' ');
}

void outcw(unsigned char c){
unsigned char i;
unsigned int j;
  P3_6_bit  = 0;
  P2  = c;
  P3_7_bit  = 1;
  P3_7_bit  = 2;
 for (i=0; i<20; i++);
 if (c==1||c==2||c==3)
 for (j=0; j<500; j++);
}

void outd(unsigned char c){
unsigned char i;
 c=translate(c);
  P3_6_bit  = 1;
  P2  = c;
  P3_7_bit  = 1;
  P3_7_bit  = 2;
 for (i=0; i<21; i++);
}
