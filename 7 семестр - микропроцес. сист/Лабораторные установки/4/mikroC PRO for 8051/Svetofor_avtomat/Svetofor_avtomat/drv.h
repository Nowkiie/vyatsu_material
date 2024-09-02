#define RED P0_0_bit
#define YEL P0_1_bit
#define GRN P0_2_bit
//#define BLUE P0_3_bit
#define lcd_led P0_4_bit
#define DB P2
#define E P3_7_bit
#define RS P3_6_bit
#define RW P3_5_bit

//extern int ms=0;      // Счетчик милисекунд

unsigned char ScanKbd(void);  // Сканирование клавиатуры
void init(void);     // Инициализация
unsigned char translate(unsigned char c); // Перевод на язык индикатора
void DelayMs(unsigned int m);             // Задержка в мс
void wr_EEPROM(unsigned int addr,unsigned char eedata); // Запись в EEPROM
unsigned char rd_EEPROM(unsigned int addr);             // Чтение из EEPROM
void clear_lcd(void);        // Очистка LCD
void outcw(unsigned char c); // Вывод упр. слова
void outd(unsigned char c);  // Вывод данных