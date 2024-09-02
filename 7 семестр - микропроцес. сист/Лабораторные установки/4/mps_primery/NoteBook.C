#include <89xs8252.h>			//SFR-регистры 8252
#include <intrpt.h>				//Здесь макрос для организации прерываний

#define lcd_led P04				//Подсветка Ж/К дисплея
#define DB P2					//Данные для ЖК
#define E P37					//Разрешение ЖК
#define RS P36					//Команда/данные ЖК
#define RW P35					//Запись/Чтение ЖК

//Объявления глобалных переменных
unsigned char 
	ms, 			//Увеличивается каждые 1 ms
	t1, 			//Позиция в первой строке
	n_zap,			//Номер записи
	k_zap,			//Количесвто записей
	INTen,			//Разрешено воспринимать клавиши INT
	INSen,			//Разрешено нажимать Insert
	
	need_refresh, 	//Команда обновления данных дисплея
	kill_zap,		//Команда удалить записи
	enter,			//Команда Enter
	delete,			//Команда delete
	backspace,		//Команда bakcpace
	insert,			//Команда insert
	edit,			//Команда edit
	right,			//Команда вправо курсор
	left;			//Команда влево курсор

//Этот массив немного сглаживает нарастание яркости (логарифмичность восприятия)
unsigned char	nom_zap[5] = {"N = "},	
				kol_zap[8] = {"Всего: "},
				no_zap[12] = {"Нет записей"};
		
//Буфер для первой строки
char buf1[16];

unsigned  char trans[64]=
{'A', 0xA0, 'B', 0xA1, 0xE0, 'E', 0xA3, 0xA4, 0xA5, 0xA6, 'K', 0xA7, 'M', 'H', 'O',
 0xA8,'P', 'C', 'T', 0xA9, 0xAA, 'X', 0xE1, 0xAB, 0xAC, 0xE2, 0xAD, 0xAE, 'b', 0xAF, 0xB0,
 0xB1, 'a', 0xB2, 0xB3, 0xB4, 0xE3, 'e', 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC,
 0xBD, 'o', 0xBE, 'p', 'c', 0xBF, 'y', 0xE4, 'x', 0xE5, 0xC0, 0xC1, 0xE6, 0xC2, 0xC3, 0xC4,
 0xC5, 0xC6, 0xC7
};

//Процедура записи в EEPROM
void wr_EEPROM(unsigned int addr,unsigned char data)
{
  while(!(WMCON&2));			//Ждем, если память занята (не закончена предыдущая ЗП)
  DP0L=addr;  //addr1.byte_.l_byte;
  DP0H=addr>>8;				//Заносим адрес в регистр DP0
  WMCON|=0x10;				//Разрешаем запись в EEPROM
  ACC =data;				//Данные в аккумулятор
  #asm
  movx @DPTR,A				//Запись
  #endasm
  WMCON&=0xef;				//Запрещаем запись в EEPROM
}

//Процедура чтения EEPROM
unsigned char rd_EEPROM(unsigned int addr)
{
  while(!(WMCON&2));		//Ждем, если память занята (не закончена предыдущая ЗП)
  DP0L=addr;
  DP0H=addr>>8;				//Заносим адрес в регистр DP0
  #asm
  movx A,@DPTR				//Запись
  #endasm
  return ACC;				//Возвращаем содержимое аккумулятора
}

//Процедура задержки на m миллисекунд
void waitms(unsigned char m){
  unsigned char a;
  a = ms + m;
  while(ms!=a);
}


//Процедура записи команды в ЖКИ
void outcw(unsigned char c){
unsigned char i;
unsigned int j;
  RS = 0;			//Передаем команду
  DB = c;			//код
  E = 1;			//строб
  E = 0;
  for (i=0; i<20; i++);		//задержка не менее 40 мкс
  if (c==1||c==2||c==3)		//если команда 1, 2 или 3
    for (j=0; j<500; j++);	//задержка не менее 1,5 мс
}
  
//Процедура записи данных в ЖКИ
void outd(unsigned char c){
unsigned char i;
  RS = 1;			//Передаем данные
  DB = c;			//данные
  E = 1;			//строб
  E = 0;
  for (i=0; i<21; i++);		//задержка не менее 43 мкс
}

//Процедура сохраняет буфер в EEPROM
void SaveBuf(){
  char i;
  for(i=0;i<16;i++)
  wr_EEPROM(n_zap * 16 + i, buf1[i]); 	//Далее записываем символы
}

//Процедура сохраняет переменные в EEPROM
void SaveVar(){
  wr_EEPROM(0,n_zap);					//По адресу 0 записываем номер записи
  wr_EEPROM(1,k_zap);					//По адресу 1 записываем количество записей
}

//Перевод кода символа из кодировки win1251 в кодировку ЖКИ
unsigned char translate(unsigned char c)
{
 if (c>191) return (trans[c-192]);
 else return c;
}

//Очистка буфера первой строки
void clearbuf1(){
unsigned char i;
for (i = 0; i < 16; i++) buf1[i] = ' ';
}

//очищаем очередь команд
void ClearOrderCommamd(){
	need_refresh = 0; 	//Команда обновления данных дисплея
	kill_zap = 0;		//Команда удалить записи
	enter = 0;			//Команда Enter
	delete = 0;			//Команда delete
	backspace = 0;		//Команда bakcpace
	insert = 0;			//Команда insert
	edit = 0;			//Команда edit
	left = 0;			//Команда влево курсор
	right = 0;			//Команда вправо курсор
}

//Процедура очистки первой строки
void clear1(){
  unsigned char i;
  outcw(0x80);			//Адрес DDRAM = 0 (начало первой строки)
  for(i=0;i<16;i++)
    outd(' ');			//16 пробелов
  t1 = 0;				//Позиция = 0, очищать строку не нужно
}

//Очистка второй строки
void clear2(){
  unsigned char i;
  outcw(0xC0);			//Адрес DDRAM = 0x40 (начало второй строки)
  for(i=0;i<16;i++)		
    outd(' ');			//16 пробелов
}

//Вывод символа на 2 строку
void type2(){
unsigned char i;
for (i = 0; i < 4; i++) {
    outcw(i|0xC0);						//Адрес DDRAM = 0x40+i
    outd(translate(nom_zap[i]));}		//Выводим '№ = '
	
	outcw(4|0xC0);
    outd((n_zap/10) + 0x30);
	
	outcw(5|0xC0);
    outd(n_zap%10 + 0x30);
	
for (i = 7; i < 14; i++) {
    outcw(i|0xC0);						//Адрес DDRAM = 0x40+i
    outd(translate(kol_zap[i-7]));}		//Выводим 'Всего:'

	outcw(14|0xC0);
    outd(k_zap/10 + 0x30);
	
	outcw(15|0xC0);
    outd(k_zap%10 + 0x30);
}

//Вывод символа на 1 строку
void type1(unsigned char c){
 EA = 0;
 if (!INSen){						//Находимся в режиме редактирования, можно выводить символы на ЖКИ
			outcw(t1|0x80);			//Адрес DDRAM = 0x40+t1
			outd(translate(c));		//Вывод символа
			buf1[t1] = c;			//Запись символа в буфер
			++t1;		
			}

 if(t1 > 14){
			t1 = 15;
			outcw(0x8F);			//Адрес DDRAM = 0x40+t1
			outd(' ');		
			buf1[t1] = ' ';	
			outcw(0x0F);			
			outcw(0x8F);			
			}		//Если дошли до конца - очистка строки	
 EA = 1;			
}


//Подпрограмма инициализации
void init(){
//ROM_VECTORS - установка векторов прерываний
  ROM_VECTOR(TM0, int_timer0);
  ROM_VECTOR(XT0, int_XT0);
  ROM_VECTOR(XT1, int_XT1);
  ROM_VECTOR(S0, int_UART);
//Memory
  WMCON|=0x08;	// internal EEPROM enable - movx будет работать с EEPROM
  WMCON&=0xfb;  // DPTR = DP0 - установка текущего указателя данных
//Сторожевой Watch Dog Timer
  WMCON|=0xD1;  //разрешение сторожевого таймера
  
//var - инициализация переменных
  t1=0;		//Начальная позиция верхней и нижней строк
//UART
  PCON |= 0x80;	//SMOD=1 - частота в 2 раза больше, чем если бы SMOD=0
  SCON = 0x72;	//mode 1, прием разрешен
  TMOD = 0x22;	//Таймеры 0 и 1 - 8-разрядные таймеры с автоперезагрузкой
  TH1   = 0xFA;	//9600 бит/с для кварца 11,059 MHz
  TR1   = 1;	//Запуск таймера 1
  ES = 1;	//Разрешение прерывания от UART
//Timer 0
  TH0 = 0x8D;	//Прерывание каждые 0,125 миллисекунды
  TR0 = 1;	//Запуск таймера
  ET0 = 1;	//Разрешение прерывания от таймера
  EX0 = 1;	//Разрешение внешнего прерывания INT0
  EX1 = 1;	//Разрешение внешнего прерывания INT1
  PT0 = 1;	//Прерыванию от таймера даем высокий приоритет, чтобы он не замерз, пока нажаты INT0 или INT1
  EA = 1;	//Разрешаем прерывания

//LCD
  waitms(30);	//Ждем 30 мс после включения питания (см. PDF)
  RW = 0;	//Заранее устанавливаем сигнал в 0, поскольку читать ЖКИ не собираемся вообще
  outcw(0x3C);  //Команды инициализации ЖКИ, установка режима работы... см. PDF
  outcw(0x0C);
  outcw(0x01);
  outcw(0x06);
}

//Основная программа
void main(){
unsigned char i;
  init();		//Инициализация
  
  lcd_led = 0;	//Включаем подсветку ЖКИ
  
  if (rd_EEPROM(0) > 100) {
  wr_EEPROM(0,0);					//По адресу 0 записываем номер записи
  wr_EEPROM(1,0);					//По адресу 1 записываем количество записей
						  }

  n_zap = rd_EEPROM(0);
  k_zap = rd_EEPROM(1);		  
   
  INTen = 1;
  INSen = 1;
  
  need_refresh = 1;
 
 
while(1){	//Бесконечный цикл
 if (need_refresh) {				//Если нужно обновить показания  ЖКИ
			EA = 0;
			ClearOrderCommamd();
			t1 = 0;
			clear1();
			if (n_zap == 0)	for (i=0; i < 11; i++) {outcw(i|0x80); outd(translate(no_zap[i]));}		//Выводим сообщение 'Записей нет'
				else for (i=0; i<16; i++) {outcw(i|0x80); outd(translate(rd_EEPROM(n_zap * 16 + i)));}	//Иначе читаем из EEPROM первую строку
			type2();				//Обноляем вторую строку
			EA = 1;
					}
					
 if (kill_zap){				//Если 'D' удаляем все строки
			if (INSen){		//Если находимся не в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						INTen = 1;
						INSen = 1;
						n_zap = 0;
						k_zap = 0;
						wr_EEPROM(0,n_zap);		//По адресу 0 записываем номер записи
						wr_EEPROM(1,k_zap);		//По адресу 1 записываем количество записей.
						clear1(); 
						for (i=0; i < 11; i++) {outcw(i|0x80); outd(translate(no_zap[i]));}		//Выводим сообщение 'Записей нет'
						type2();
						EA = 1;
					  }
			}
			
 if (enter){						//Если Enter - сохраняем массив в EEPROM
			EA = 0;
			ClearOrderCommamd();
			SaveBuf();	
			SaveVar();
			INTen = 1;
			INSen = 1;
			outcw(0x0C);			//Выключаем курсор
			EA = 1;
			}
			
  if (delete){						//Если Delete - удаление строки
			if (INSen){				//Если находимся не в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						clear1();
						clearbuf1();
						SaveBuf();
						EA = 1;
					  }
			}			
			
  if (backspace){					//Если BackSpace - уменьшаем позицию и затираем символ
			if (!INSen){			//Если находимся в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						if (t1)	t1--;
						outcw(t1|0x80);
						outd(' ');	
						buf1[t1] = ' ';
						outcw(0x0F);			//Включаем курсор на ЖКИ
						outcw(t1|0x80);
						EA = 1;
						}
			}			

  if (left){					//Если BackSpace - уменьшаем позицию и затираем символ
			if (!INSen){			//Если находимся в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						if (t1)	t1--;
						outcw(0x0F);			//Включаем курсор на ЖКИ
						outcw(t1|0x80);
						EA = 1;
						}
			}

  if (right){					//Если BackSpace - уменьшаем позицию и затираем символ
			if (!INSen){			//Если находимся в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						if (t1 < 16)	t1++;
						outcw(0x0F);			//Включаем курсор на ЖКИ
						outcw(t1|0x80);
						EA = 1;
						}
			}

			
   if (insert){						//Если Insert - режим добавления
			if (INSen){		//Если еще находимся не в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						INTen = 0;
						INSen = 0;
						n_zap = ++k_zap;
						clear1();
						clearbuf1();
						t1 = 0;
						type2();
						outcw(0x0F);			//Включаем курсор на ЖКИ
						outcw(0x80);			//Адрес DDRAM=0x80 - в начало первой строки			
						EA = 1;
						}
			  }		

   if (edit){						//Если Insert - режим добавления
			if (INSen){		//Если еще находимся не в режиме добавления
						EA = 0;
						ClearOrderCommamd();
						INTen = 0;
						INSen = 0;
						for (i=0; i<16; i++) buf1[i] = rd_EEPROM(n_zap * 16 + i);
						t1 = 15;
						while (buf1[--t1] == ' '); 		//Ищем первый непустой символ с конца строки
						t1++;
						outcw(0x0F);					//Включаем курсор на ЖКИ
						outcw(t1|0x80);
						EA = 1;
						}
			  }				  
			
		}
}


//Прерывание от таймера 0 - каждые 0,125 мс
static interrupt void int_timer0(){
  static unsigned char st1;
  if (++st1>7) st1 = 0; else return; 	//Делим частоту вызова прерывания на 8
  WMCON|=0x02;							//сброс сторожевого таймера
  ms++;									//Увеличиваем счетчик интервалов по 1ms
}

//Прерывание ~INT0
static interrupt void int_XT0(){
if (!P33){ 				//Если нажат и INT1
	EA = 0;				//Запрещаем прерывания, чтобы не сбрасывался WDT	
	while(1);}			//Весим прогу
	
if ((n_zap == k_zap) || (!INTen) ) return;

n_zap++;
need_refresh = 1;		//Нужно обновить данные на ЖКИ
SaveVar();
while(!P32);	
}

//Прерывание ~INT1 - см. комментарии выше
static interrupt void int_XT1(){
if (!P32){ 				//Если нажат и INT0
	EA = 0;				//Запрещаем прерывания, чтобы не сбрасывался WDT	
	while(1);}			//Весим прогу
	
if ((n_zap < 2) || (!INTen)) return;

n_zap--;
need_refresh = 1;		//Нужно обновить данные на ЖКИ
SaveVar();
while(!P33);
}


//Прерывание от UART
static interrupt void int_UART(){
if (RI){
	RI=0;							//Сбрасываем флаг, вызвавший прерывание
	switch (SBUF){
	case 68: kill_zap = 1; return;	//Если 'D' удаляем все строки
	case 13: enter = 1; return;	 	//Если Enter - сохраняем массив в EEPROM
	case 46: delete = 1; return;	//Если Delete - удаление строки
	case 90: delete = 1; return;	//Если 'Z' - удаление строки
	case 8 : backspace = 1; return;	//Backspace
	case 65: insert  = 1; return;	//Если 'A'  то добавляем (ADD)
	case 45: insert  = 1; return;	//Если insert  то добавляем
	case 69: edit  = 1; return;		//Если 'E'  то режим редактирования
	case 37: left  = 1; return;		//Если 'влево'  то двигаем курсор влево
	case 39: right  = 1; return;	//Если 'вправо'  то двигаем курсор вправо
				 }

    type1(SBUF);				
	}
}

