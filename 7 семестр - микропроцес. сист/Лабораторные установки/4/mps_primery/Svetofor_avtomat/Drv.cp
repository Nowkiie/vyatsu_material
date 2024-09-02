#line 1 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Drv.c"
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
#line 5 "C:/Documents and Settings/student/Рабочий стол/mps_primery/Svetofor_avtomat/Drv.c"
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
 case 'А': return 'A';
 case 'Б': return 0xA0;
 case 'В': return 'B';
 case 'Г': return 0xA1;
 case 'Д': return 0xE0;
 case 'Е': return 'E';
 case 'Ё': return 0xA2;
 case 'Ж': return 0xA3;
 case 'З': return 0xA4;
 case 'И': return 0xA5;
 case 'Й': return 0xA6;
 case 'К': return 'K';
 case 'Л': return 0xA7;
 case 'М': return 'M';
 case 'Н': return 'H';
 case 'О': return 'O';
 case 'П': return 0xA8;
 case 'Р': return 'P';
 case 'С': return 'C';
 case 'Т': return 'T';
 case 'У': return 0xA9;
 case 'Ф': return 0xAA;
 case 'Х': return 'X';
 case 'Ц': return 0xE1;
 case 'Ч': return 0xAB;
 case 'Ш': return 0xAC;
 case 'Щ': return 0xE2;
 case 'Ъ': return 0xAD;
 case 'Ы': return 0xAE;
 case 'Ь': return 'b';
 case 'Э': return 0xAF;
 case 'Ю': return 0xB0;
 case 'Я': return 0xB1;
 case 'а': return 'a';
 case 'б': return 0xB2;
 case 'в': return 0xB3;
 case 'г': return 0xB4;
 case 'д': return 0xE3;
 case 'е': return 'e';
 case 'ё': return 0xB5;
 case 'ж': return 0xB6;
 case 'з': return 0xB7;
 case 'и': return 0xB8;
 case 'й': return 0xB9;
 case 'к': return 0xBA;
 case 'л': return 0xBB;
 case 'м': return 0xBC;
 case 'н': return 0xBD;
 case 'о': return 'o';
 case 'п': return 0xBE;
 case 'р': return 'p';
 case 'с': return 'c';
 case 'т': return 0xBF;
 case 'у': return 'y';
 case 'ф': return 0xE4;
 case 'х': return 'x';
 case 'ц': return 0xE5;
 case 'ч': return 0xC0;
 case 'ш': return 0xC1;
 case 'щ': return 0xE6;
 case 'ъ': return 0xC2;
 case 'ы': return 0xC3;
 case 'ь': return 0xC4;
 case 'э': return 0xC5;
 case 'ю': return 0xC6;
 case 'я': return 0xC7;
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
