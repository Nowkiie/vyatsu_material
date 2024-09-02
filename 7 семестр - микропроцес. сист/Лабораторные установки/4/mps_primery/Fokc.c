#include <89xs8252.h>
#include <intrpt.h>

#define DB P2		//Данные для ЖК
#define E P37		 //Разрешение ЖК
#define RS P36		//Команда/данные ЖК
#define RW P35		 //Запись/Чтение ЖК

unsigned char t1,t11,	 //Позиция в первой строке 
 		t2,	//Позиция во второй строке
		edit, 	//Режим редактирования 
		key, 	// нажатая клавиша
		kr, kp, // почти то же самое :) kr вроде не используется 
		op1[9],op2[9],index1,index2,razr_op1,razr_op2,tmp[9],one[9],ms;
char rez[10],rom[10],rezdiv[9];
unsigned char romflag;


  unsigned char calcstr[16];		// массив введенных значений число[7] знак[+-*/] число[7] =

void outcw(unsigned char c)	// Процедура записи команды в ЖКИ
{
unsigned char i;
unsigned int j;
  RS = 0;			 //Передаем команду
  DB = c;			 //Передаем код
  E = 1;			// строб
  E = 0;
  for (i=0; i<20; i++);		//Задержка не менее 40 мкс
  if (c==1||c==2||c==3)		 //если команда 1, 2 или 3
    for (j=0; j<500; j++);	//задержка не менее 1,5 мс
}

void outd(unsigned char c)	//Процедура записи данных в ЖКИ
{
unsigned char i;
  RS = 1;			 //Передаем данные
  DB = c;			 //данные
  E = 1;			//Строб 
  E = 0;
  for (i=0; i<21; i++);		 //Задержка 40 мкс
}
 
void type1(unsigned char c){	//Вывод символа на 1ю строку

  outcw(t1|0x80);
  outd(c);
}

void type2(unsigned char c){	//Вывод символа на 2ю строку
 outcw(t2|0xC0);
 outd(c); 
}

void t12_5ms(){
unsigned char i;	
  kp = 0;			//Кнопка не нажата
  P0 = P0&0x1F|0xC0;		//Выдаем бегущий ноль на столбцы клавиатуры
  for(i=0;i<10;i++);		//Небольшая задержка, чтобы не влияла паразитная емкость и индуктивность
  kr = !P13;			//Определяем, нажата ли решетка
  if (!P10) kp = '7';		//Определяем код нажатой клавиши
  else if (!P11) kp = '4';
  else if (!P12) kp = '1';
  else if (!P13) kp = '#';
  P0 = P0&0x1F|0xA0;		//Задержка
  for(i=0;i<10;i++);		//Выдаем бегущий ноль на столбцы клавиатуры
  if (!P10) kp = '8';
  else if (!P11) kp = '5';
  else if (!P12) kp = '2';
  else if (!P13) kp = '0';
  P0 = P0&0x1F|0x60;		//Выдаем бегущий ноль на столбцы клавиатуры
  for(i=0;i<10;i++);
  if (!P10) kp = '9';		//Задержка
  else if (!P11) kp = '6';
  else if (!P12) kp = '3';
  else if (!P13) kp = 13;
  if (kp) key = kp;		//Записываем код кнопки
}

void reset() {
unsigned char i;
for (i=0;i<16;i++){		
  calcstr[i]=' ';
  }
  for (i=0;i<9;i++){		
  op1[i]=0;
  op2[i]=0;
  rez[i]=0;
  tmp[i]=0;
  rezdiv[i]=0;
  one[i]=0;
  }
  one[0]=1;
  P00=1;
  outcw(0x01);//очистка дисплея
  edit=0;
  t1=t11=0;
  type1('0');
}

void wr_EEPROM(unsigned int addr,unsigned char data)
{
  while(!(WMCON&2));
  DP0L=addr;  //addr1.byte_.l_byte;
  DP0H=addr>>8;
  WMCON|=0x10;
  ACC =data;
  #asm
  movx @DPTR,A
  #endasm
  WMCON&=0xef;
}

unsigned char rd_EEPROM(unsigned int addr)
{
  while(!(WMCON&2));
  DP0L=addr;
  DP0H=addr>>8;
  #asm
  movx A,@DPTR
  #endasm
  return ACC;
}
   
void init()			// инициализация
{	
  ROM_VECTOR(TM0, int_timer0);	//Установка векторов прерываний
  ROM_VECTOR(XT0, int_XT0);
  ROM_VECTOR(XT1, int_XT1);
  ROM_VECTOR(S0, int_UART);
  ms=0;
  t1=0;
//Memory
  romflag=0;
  WMCON|=0x08;	// internal EEPROM enable
  WMCON&=0xfb;  // DPTR = DP0
  WMCON|=0xE1;
  reset();
  edit=0;
 PCON |= 0x80;			 //SMOD=1 - частота в 2 раза больше, чем если бы SMOD=0
 SCON = 0x72;			 //mode 1, прием разрешен
 TMOD = 0x21;			//Таймер 0 -16-разрядный; Таймер 1 -8-разрядный с автоперез.
 TH1  =0xF5; 		
 TR1  = 1;	 		//Запуск таймера 1
 ES   = 1;			//Разрешение прерывания от UART
 ET1  = 0;			//Разрешение прерывания от таймера 1	
 TL0 = 0x99; 
 TH0 = 0x05; 
 TR0 = 1;			//Запуск таймера 0
 ET0 = 1;			//Разрешение прерывания от таймера 0
 EX0 = 1;			//Разрешение внешних прерываний
 EX1 = 1;
 IT0 = 1;		//По умолчанию (IT0=0) прерывание INT0 по низкому уровню
 PT0 = 1;		//Прерыванию от таймера даем высокий приоритет, чтобы он не замерз
 EA = 1;		//Разрешаем прерывания
 RW = 0;		//Устанавл. сигнал в 0,т.к. читать ЖКИ не собираемся вообще
  outcw(0x3C);		//Команды инициализации ЖКИ
  outcw(0x0C);// dis on cur on blink on
  outcw(0x01);
  outcw(0x06); 
}

void waitms(unsigned char m){
  unsigned char a;
  a = ms+(m<<1);
  while(ms!=a);
}

void getops ()
{unsigned char k;
 char i;
for (i=0;i<16;i++){
if ((calcstr[i]=='+')||(calcstr[i]=='-')||(calcstr[i]=='*')||(calcstr[i]==':')) {index1=i;}
if (calcstr[i]==' ') {index2=i;i=16;}
}
 k=0;
index1--;
for (i=index1;i>-1;i--){
op1[k]=(calcstr[i]-0x30);
k++;
}
k=0;
index1++;
index2--;
for (i=index2;i>index1;i--){
op2[k]=(calcstr[i]-0x30);
k++;
}
index2++;
}

void calculate ()
{char i,j,cr,flag; 
//счетаем числа
cr=0;
razr_op1=index1;
razr_op2=index2-index1-1;
switch (calcstr[index1]){
case '+':{
		  for (i=0;i<9;i++){
		  rez[i]=rez[i]+op1[i]+op2[i];
		  if (rez[i]>9) {rez[i+1]=rez[i+1]+1;rez[i]=rez[i]-10;
              }
              }
          break;
		 }
case '-':{
          for (i=0;i<9;i++){
		  rez[i]=op1[i]-op2[i];
		  if (rez[i]<0) {rez[i]=rez[i]+10;
			   op1[i+1]--;
              }
              }
          break;
		 }
case '*':{
		  razr_op1++;
		  razr_op2++;	
       for (i=0;i<razr_op2;i++){
			for (j=0;j<i+razr_op1;j++){
			tmp[j+i]=op1[j]*op2[i]+tmp[j+i];
			if (tmp[j+i]>9) {
                          while (tmp[j+i]>9){
                                tmp[j+i]=tmp[j+i]-10;
                                tmp[j+1+i]++;
                                if (tmp[j+1+i]>9) {
                                                tmp[j+1+i]=tmp[j+1]-10;
                                                tmp[j+2+i]++;
                                                }
                                }
                          }
			}
          for (j=0;j<9;j++){
		  rez[j]=rez[j]+tmp[j];
		  if (rez[j]>9) {rez[j+1]=rez[j+1]+1;rez[j]=rez[j]-10;
              }   
		  }
		  for (j=0;j<9;j++){
         tmp[j]=0;}
    }
		
		  
          break;
		 }
case ':':{
		   cr=0;
           flag=0; 
   for (i=0;i<9;i++){
       if(op2[i]>0) cr++;
   } 
   if (cr==0) {flag=1;P00=0;}
   else cr=0;
   cr=0;
      for (i=0;i<9;i++){
       if(op1[i]>0) {cr++;}
   } 
   if (cr==0) {flag=1;}
   else cr=0;
   cr=0;
   for (j=8;j>-1;j--){
    if (op1[j]>op2[j]) {j=-1;cr++;}   
   }
   if (cr==0) {flag=1;}
 while (flag==0){
 for (i=0;i<9;i++){
		  rezdiv[i]=op1[i]-op2[i];
		  if (rezdiv[i]<0) {rezdiv[i]=rezdiv[i]+10;
			   op1[i+1]--;
              }
              }
          for (i=0;i<9;i++){
              op1[i]=rezdiv[i];
          }
          for (j=8;j>-1;j--){
          if (op1[j]<op2[j]) {flag=1;j=-1;
                             for (i=0;i<9;i++){
                             rez[i]=rez[i]+one[i];
		                     if (rez[i]>9) {rez[i+1]=rez[i+1]+1;rez[i]=rez[i]-10;
              }
              }
              }
          if ((op1[j]>=op2[j])&&((op1[j]!=0)||(op2[j])!=0)) {
                             for (i=0;i<9;i++){
                             rez[i]=rez[i]+one[i];
		                     if (rez[i]>9) {rez[i+1]=rez[i+1]+1;rez[i]=rez[i]-10;
              }
              j=-1;
              } 
                             }
          }
              
} 
          break;
		 }
}
t2=8;
for (i=0;i<9;i++){
type2(rez[i]+0x30);
t2--;
}
}

void main()			
{unsigned char i;
  init();
  type1('0');
  if (rd_EEPROM(0x200)==0) P03=1;
  else P03=0;
  while (1)
  {
  if (key) {
 if (romflag==1) {
 switch (key){
 case '1':{//очистка памяти
		   for (i=0;i==10;i++){
		   wr_EEPROM(0x200+i,0);
		   }
		   P03=1;
		   romflag=0;
           break;
		  }
 case '2':{//сохр результата
		   for (i=0;i<11;i++){
		   wr_EEPROM(0x200+i,rez[i]);
		   }
		   P03=0;
		   romflag=0;
           break;
		  }
 case '3':{//выборка
		   for (i=0;i<11;i++){
		   rez[i]=rd_EEPROM(0x200+i);
		   }
		   t2=8;
			for (i=0;i<9;i++){
			type2(rez[i]+0x30);
			t2--;
			
		   }romflag=0;
           break;
		  }
 case '4':{//доб тек знач к памяти
		   for (i=0;i<9;i++){
		   op1[i]=rd_EEPROM(0x200+i);
		   op2[i]=0;
		   }
		   for (i=0;i<9;i++){
		  op2[i]=rez[i]+op1[i]+op2[i];
		  if (op2[i]>9) {op2[i+1]=op2[i+1]+1;op2[i]=op2[i]-10;
              }
              }
			t2=8;
			for (i=0;i<9;i++){
			type2(op2[i]+0x30);
			t2--;
			romflag=0;
           break;
		  }
 }
 }}  else {
 if (key=='#') {reset();}
 if (key==13) edit++;
 if (edit==3) {type1('='); getops(); calculate();}
 if (t1!=16) {
 if (((edit==0)||(edit==2))&&(key!='#')&&(key!=13)) {
 calcstr[t1]=key;
	type1(key);
	t1++;
}
 if (edit==1) {
switch (key) {
case '1':{
	calcstr[t1]='+';
	type1('+');
	t1++;
	break;
	}
case '2':{
	calcstr[t1]='-';
	type1('-');
	t1++;
	break;
	}
case '3':{
	calcstr[t1]='*';
	type1('*');
	t1++;
	break;
	}
case '4':{
	calcstr[t1]=':';
	type1(':');
	t1++;
	break;
	}
} 
 }
  }
   }	
	while(kp);		//Ждем, пока кнопку не отпустят
      key = 0;			//Обнуляем код кнопки
	}
	 
	}
}

static interrupt void int_timer0()
{ 
 ms++;
 t12_5ms();
 WMCON=0xE3;
}
 

static interrupt void int_XT0()
{	
EA=0;
while (1);
}

static interrupt void int_XT1()
{
if (romflag==0) romflag=1;
}

static interrupt void int_UART(){
if (RI) {
	if (SBUF!='='){
	if (t1!=16){
	calcstr[t1]=SBUF;
	type1(SBUF);
	t1++;
	}
	
	}else {type1('='); getops(); calculate();}
	RI=0;}	//Если прерывание по приему символа - сбрасываем флаг
if (TI) TI=0;	//Если прерывание по окончании передачи - сбрасываем флаг
}
