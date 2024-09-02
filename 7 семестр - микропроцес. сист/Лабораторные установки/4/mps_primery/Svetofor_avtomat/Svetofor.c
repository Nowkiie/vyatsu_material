//#include "89xs8252.h"
//#include "temperature.h"
#include "drv.h"
#include "1wire.h"


#define R      1 // Код состояния
#define RY     2
#define G      3
#define GG     4
#define Y      5
#define SR     6
#define SG     7


char key=0;      // Идентификатор нажатой кнопки
char state=R;    // Идентификатор управляющего состояния
char t;          // Значение счетчика
char tr;         // Время красного сигнала, с
char tg;         // Время зеленого сигнала, с
char ty;         // Время зеленого сигнала, с
char T_FLAG = 0; // Сигнал счетчика "время истекло"
int ms = 0;      // Счетчик милисекунд

unsigned char ShiftRight(unsigned char prev)
{
     if (prev == 1)
          return 128;
     else
          prev >>= 1;
     return prev;
}

#define str_size 16

char str[17] = "привет как дела)";

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

// Инициализация
     init();
     RED = 0;      // Красный цвет
     YEL = 1;      // Желтый цвет
     GRN = 1;      // Зеленый цвет
     lcd_led = 0;  // Подсветка индикатора
     tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
     ty=rd_EEPROM(2); if((ty>30)||(ty<5)) ty=5;
     tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;

     /*for(t=0;t!=0;t++); // тест задержки
     t = 10*tr;*/

// Реализация управляющего автомата
        while (1) {
              key=ScanKbd();
              switch (state) {
                case R: // Красный
                        //PrintOut(outd,"Красный         ");
                        clear_lcd(); //outcw(0x81); outd('К'); outd('Л'); //outd('р'); outd('а');
                        out_str();
                        //outd('с'); outd('н'); outd('ы'); outd('й');
                        if (T_FLAG) { state=Y;  T_FLAG = 0;  YEL=0; RED=1; }
                        break;
                case G: // Зеленый
                        //PrintOut(outd,"Зеленый         ");
                        clear_lcd(); //outcw(0x80); outd('З'); //outd('е'); outd('л');
                        out_str();
                        //outd('е'); outd('н'); outd('ы'); outd('й');
                        if (T_FLAG) { state=R;  T_FLAG = 0; GRN=1; RED=0;}
                        break;
                case Y: // Желтый
                        //PrintOut(outd,"Желтый          ");
                        clear_lcd(); //outcw(0x80); outd('Ж'); //outd('е'); outd('л');
                        out_str();
                        //outd('т'); outd('ы'); outd('й');
                        if (T_FLAG) { state=G;  T_FLAG = 0; GRN=0; YEL=1; }
                        break;
              }
              DelayMs(100);            // такт работы автомата
              if(t==0) T_FLAG=1; else t--;  // счетчик
        }
}

/*

void DelayMs(unsigned int m){  // задержка пустым циклом
  unsigned char a; //счетчик милисекундного цикла
  //unsigned int ms; //счетчик милисекунд
  for(ms=0;ms!=m;ms++) {
    for(a=0;a!=120;a++); // пустой цикл 1мс
    //WMCON.WDTRST=1; // сброс сторожевого таймера
  }
}
*/

void DelayMs(unsigned int m){  // задержка по таймеру
  //unsigned char a;
  //a = ms+(m<<1);
  ms=0;
  WMCON.WDTRST=1; // сброс сторожевого таймера
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