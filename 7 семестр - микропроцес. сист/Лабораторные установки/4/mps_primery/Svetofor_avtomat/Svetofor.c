//#include "89xs8252.h"
//#include "temperature.h"
#include "drv.h"
#include "1wire.h"


#define R      1 // ��� ���������
#define RY     2
#define G      3
#define GG     4
#define Y      5
#define SR     6
#define SG     7


char key=0;      // ������������� ������� ������
char state=R;    // ������������� ������������ ���������
char t;          // �������� ��������
char tr;         // ����� �������� �������, �
char tg;         // ����� �������� �������, �
char ty;         // ����� �������� �������, �
char T_FLAG = 0; // ������ �������� "����� �������"
int ms = 0;      // ������� ����������

unsigned char ShiftRight(unsigned char prev)
{
     if (prev == 1)
          return 128;
     else
          prev >>= 1;
     return prev;
}

#define str_size 16

char str[17] = "������ ��� ����)";

void init_string()
{
     int i = str_size;
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

// �������������
     init();
     RED = 0;      // ������� ����
     YEL = 1;      // ������ ����
     GRN = 1;      // ������� ����
     lcd_led = 0;  // ��������� ����������
     tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
     ty=rd_EEPROM(2); if((ty>30)||(ty<5)) ty=5;
     tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;

     /*for(t=0;t!=0;t++); // ���� ��������
     t = 10*tr;*/

// ���������� ������������ ��������
        while (1) {
              key=ScanKbd();
              switch (state) {
                case R: // �������
                        //PrintOut(outd,"�������         ");
                        clear_lcd(); //outcw(0x81); outd('�'); outd('�'); //outd('�'); outd('�');
                        out_str();
                        //outd('�'); outd('�'); outd('�'); outd('�');
                        if (T_FLAG) { state=Y;  T_FLAG = 0;  YEL=0; RED=1; }
                        break;
                case G: // �������
                        //PrintOut(outd,"�������         ");
                        clear_lcd(); //outcw(0x80); outd('�'); //outd('�'); outd('�');
                        out_str();
                        //outd('�'); outd('�'); outd('�'); outd('�');
                        if (T_FLAG) { state=R;  T_FLAG = 0; GRN=1; RED=0;}
                        break;
                case Y: // ������
                        //PrintOut(outd,"������          ");
                        clear_lcd(); //outcw(0x80); outd('�'); //outd('�'); outd('�');
                        out_str();
                        //outd('�'); outd('�'); outd('�');
                        if (T_FLAG) { state=G;  T_FLAG = 0; GRN=0; YEL=1; }
                        break;
              }
              DelayMs(100);            // ���� ������ ��������
              if(t==0) T_FLAG=1; else t--;  // �������
        }
}

/*

void DelayMs(unsigned int m){  // �������� ������ ������
  unsigned char a; //������� �������������� �����
  //unsigned int ms; //������� ����������
  for(ms=0;ms!=m;ms++) {
    for(a=0;a!=120;a++); // ������ ���� 1��
    //WMCON.WDTRST=1; // ����� ����������� �������
  }
}
*/

void DelayMs(unsigned int m){  // �������� �� �������
  //unsigned char a;
  //a = ms+(m<<1);
  ms=0;
  WMCON.WDTRST=1; // ����� ����������� �������
  while(ms!=m) continue;
}

void Timer1InterruptHandler() org IVT_ADDR_ET1{

  EA_bit = 0;        // Clear global interrupt enable flag
  TF1_bit = 0;       // Ensure that Timer1 interrupt flag is cleared

  TR1_bit = 0;       // Stop Timer1
  TH1 = 0xFC;        // Reset Timer1 high byte  65536-1000
  TL1 = 0x18;        // Reset Timer1 low byte

  //P0 = ~P0;          // Toggle PORT0
  ms++;

  EA_bit = 1;        // Set global interrupt enable flag
  TR1_bit = 1;       // Run Timer1
}

void INT0_Interrupt() org IVT_ADDR_EX0 {
  EA_bit = 0;
  lcd_led=~lcd_led;
  EA_bit = 1;
}
/*
void UART_Interrupt() iv IVT_ADDR_ES {
  if (RI_bit){
    if (SBUF==0x13) {state=SR;  RED=1; YEL=1; GRN=1;}
    RI_bit=0;
  }
  if (TI_bit) TI_bit = 0;
}
*/