#line 1 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
#line 1 "d:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/svetofor_avtomat/1wire.h"
#line 13 "d:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/svetofor_avtomat/1wire.h"
unsigned char read_OW (void);
void OW_write_bit (unsigned char write_data);
unsigned char OW_read_bit (void);
unsigned char OW_reset_pulse(void);
void OW_write_byte (unsigned char write_data);
unsigned char OW_read_byte (void);
#line 12 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
unsigned char read_OW (void)
{
 unsigned char read_data=0;

  P1_4_bit  = 1;

 if ( P1_4_bit ==1)
 read_data = 1;
 else
 read_data = 0;

 return read_data;
}
#line 35 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
unsigned char OW_reset_pulse(void)

{
 unsigned char presence_detect;

  P1_4_bit =0;

 Delay_us(240);
 Delay_us(240);

  P1_4_bit =1;

 Delay_us(70);

 presence_detect = read_OW();

 Delay_us(205);
 Delay_us(205);

  P1_4_bit =1;

 return presence_detect;
}
#line 67 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
void OW_write_bit (unsigned char write_bit)
{
 if (write_bit)
 {

  P1_4_bit =0;
 Delay_us(6);
  P1_4_bit =1;
 Delay_us(6);
 }
 else
 {

  P1_4_bit =0;
 Delay_us(60);
  P1_4_bit =1;
 Delay_us(10);
 }
}
#line 96 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
unsigned char OW_read_bit (void)
{
 unsigned char read_data;

  P1_4_bit =0;
 Delay_us(6);
  P1_4_bit =1;
 Delay_us(9);

 read_data = read_OW();

 Delay_us(55);
 return read_data;
}
#line 119 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
void OW_write_byte (unsigned char write_data)
{
 unsigned char loop;

 for (loop = 0; loop < 8; loop++)
 {
 OW_write_bit(write_data & 0x01);
 write_data >>= 1;
 }
}
#line 138 "D:/alex/копия флешки/ЭВМ/МПС/МПС_2ч/Лаб/3-МК/Svetofor_avtomat/1wire.c"
unsigned char OW_read_byte (void)
{
 unsigned char loop, result=0;

 for (loop = 0; loop < 8; loop++)
 {

 result >>= 1;
 if (OW_read_bit())
 result |= 0x80;
 }
 return result;
}
