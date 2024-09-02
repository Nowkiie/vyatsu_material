/*
 * file         : T6963C.h
 * project      : T6963C GRAPHIC LCD LIBRARY
 * author       : Bruno Gavand
 * ctime        : Jun 06 2005
 * mtime        : Jan 27 2006
 * description  :
 */

/***********************************************
 * T6963C CONSTANT DEFINITIONS
 ***********************************************/
#define T6963C_CHARACTER_HEIGHT                 8       // character height in pixel

/*
 * command set
 * see T6963C datasheet
 */
#define T6963C_CURSOR_POINTER_SET               0b00100001
#define T6963C_OFFSET_REGISTER_SET              0b00100010
#define T6963C_ADDRESS_POINTER_SET              0b00100100

#define T6963C_TEXT_HOME_ADDRESS_SET            0b01000000
#define T6963C_TEXT_AREA_SET                    0b01000001
#define T6963C_GRAPHIC_HOME_ADDRESS_SET         0b01000010
#define T6963C_GRAPHIC_AREA_SET                 0b01000011

#define T6963C_ROM_MODE_OR                      0b10000000
#define T6963C_ROM_MODE_XOR                     0b10000001
#define T6963C_ROM_MODE_AND                     0b10000011
#define T6963C_ROM_MODE_TEXT                    0b10000100

#define T6963C_RAM_MODE_OR                      0b10001000
#define T6963C_RAM_MODE_XOR                     0b10001001
#define T6963C_RAM_MODE_AND                     0b10001011
#define T6963C_RAM_MODE_TEXT                    0b10001100

#define T6963C_DISPLAY_MASK                     0b10010000
#define T6963C_DISPLAY_GRAPHICS_BIT             F3
#define T6963C_DISPLAY_TEXT_BIT                 F2
#define T6963C_DISPLAY_CURSOR_BIT               F1
#define T6963C_DISPLAY_CURSOR_BLINK_BIT         F0

#define T6963C_CURSOR_PATTERN_MASK              0b10100111

#define T6963C_DATA_AUTO_WRITE_SET              0b10110000
#define T6963C_DATA_AUTO_READ_SET               0b10110001
#define T6963C_DATA_AUTO_RESET                  0b10110010

#define T6963C_DATA_WRITE_AUTO_INCREMENT        0b11000000
#define T6963C_DATA_READ_AUTO_INCREMENT         0b11000001
#define T6963C_DATA_WRITE_NO_INCREMENT          0b11000100
#define T6963C_DATA_READ_NO_INCREMENT           0b11000101

#define T6963C_DATA_BIT                         0b11110000

/*
 * status byte
 */
#define T6963C_STATUS_BUSY1    0x01
#define T6963C_STATUS_BUSY2    0x02
#define T6963C_STATUS_DARRDY   0x04
#define T6963C_STATUS_DAWRDY   0x08
#define T6963C_STATUS_CLR      0x20
#define T6963C_STATUS_ERR      0x40
#define T6963C_STATUS_BLINK    0x80

/*
 * color masks
 */
#define T6963C_WHITE            0b1000
#define T6963C_BLACK            0

/*******************************************
 * MACRO DEFINITIONS
 *******************************************/
/*
 * clear control bit
 */
#define T6963C_clearBit(b)     b = 0

/*
 * set control bit
 */
#define T6963C_setBit(b)        b = 1

/*
 * neg control bit
 */
#define T6963C_negBit(b)        b = !b

/*
 * total panel memory size is one graphic panel plus one text panel size
 */
#define T6963C_panelMemSize     (T6963C_grMemSize + T6963C_txtMemSize)

/*
 * display graphic panel number n
 */
#define T6963C_displayGrPanel(n)        T6963C_setPtr(T6963C_panelMemSize * n, T6963C_GRAPHIC_HOME_ADDRESS_SET)

/*
 * display text panel number n
 */
#define T6963C_displayTxtPanel(n)       T6963C_setPtr(T6963C_panelMemSize * n + T6963C_grMemSize, T6963C_TEXT_HOME_ADDRESS_SET)

/*
 * compute graphic start address for panel number n
 */
#define  T6963C_setGrPanel(n)           T6963C_grHomeAddr = T6963C_panelMemSize * n

/*
 * compute text start address for panel number n
 */
#define  T6963C_setTxtPanel(n)          T6963C_textHomeAddr = T6963C_panelMemSize * n + T6963C_grMemSize

/*
 * fill full #n panel with v bitmap (0 to clear)
 */
#define T6963C_panelFill(v)             T6963C_fill(v, 0, T6963C_panelMemSize)

/*
 * fill graphic #n panel with v bitmap (0 to clear)
 */
#define T6963C_grFill(v)                T6963C_fill(v, 0, T6963C_grMemSize)

/*
 * fill text #n panel with char v + 32 (0 to clear)
 */
#define T6963C_txtFill(v)               T6963C_fill(v, T6963C_grMemsize, T6963C_txtMemSize)

/*
 * set cursor size
 */
#define T6963C_cursor_height(n)         T6963C_writeCommand(T6963C_CURSOR_PATTERN_MASK | (n & 0b00000111))

/*
 * set cursor on
 */
#define T6963C_cursor_on()              T6963C_display.T6963C_CURSOR_BIT = 1; T6963C_writeCommand(T6963C_display)

/*
 * set graphics on/off
 */
#define T6963C_graphics(n)              T6963C_display.T6963C_DISPLAY_GRAPHICS_BIT = n; T6963C_writeCommand(T6963C_display)

/*
 * set text on/off
 */
#define T6963C_text(n)                  T6963C_display.T6963C_DISPLAY_TEXT_BIT = n; T6963C_writeCommand(T6963C_display)

/*
 * set cursor on/off
 */
#define T6963C_cursor(n)                T6963C_display.T6963C_DISPLAY_CURSOR_BIT = n; T6963C_writeCommand(T6963C_display)

/*
 * cursor blink on/off
 */
#define T6963C_cursor_blink(n)         T6963C_display.T6963C_DISPLAY_CURSOR_BLINK_BIT = n; T6963C_writeCommand(T6963C_display)

/************************************
 * LIBRARY PROTOTYPES
 ************************************/
void            T6963C_init(unsigned int w, unsigned char h, unsigned char fntW);
void            T6963C_writeData(unsigned char mydata);
void            T6963C_writeCommand(unsigned char mydata);
void            T6963C_setPtr(unsigned int addr, unsigned char t);
void            T6963C_waitReady(void);
void            T6963C_fill(unsigned char mydata, unsigned int start, unsigned int len);
void            T6963C_dot(int x, int y, unsigned char color);
void            T6963C_write_char(unsigned char c, unsigned char x, unsigned char y, unsigned char mode);
void            T6963C_write_text(unsigned char *str, unsigned char x, unsigned char y, unsigned char mode);
void            T6963C_line(int px0, int py0, int px1, int py1, unsigned char pcolor);
void            T6963C_rectangle(int x0, int y0, int x1, int y1, unsigned char pcolor);
void            T6963C_box(int x0, int y0, int x1, int y1, unsigned char pcolor);
void            T6963C_circle(int x, int y, long r, unsigned char pcolor);
void            T6963C_image(const char *pic);
void            T6963C_sprite(unsigned char px, unsigned char py, const char *pic, unsigned char sx, unsigned char sy);
void            T6963C_set_cursor(unsigned char x, unsigned char y);

/****************************
 * GLOBAL VARIABLES
 ****************************/
extern  sfr char T6963C_dataPort;             // pointer to DATA BUS port
extern  sfr char T6963C_cntlPort;             // pointer to CONTROL port

extern  unsigned int    T6963C_grWidth;       // graphic width
extern  unsigned int    T6963C_grHeight;      // graphic height
extern  unsigned int    T6963C_txtCols;       // number of text columns in a row

extern  unsigned int    T6963C_fontWidth;     // font width
extern  unsigned int    T6963C_grHomeAddr;    // graphic home address
extern  unsigned int    T6963C_textHomeAddr;  // text home address
extern  unsigned int    T6963C_grMemSize;     // graphic panel memory size
extern  unsigned int    T6963C_txtMemSize;    // text panel memory size

extern  sfr sbit   T6963C_cntlwr;             // WR write bit mask
extern  sfr sbit   T6963C_cntlrd;             // RD read bit mask
extern  sfr sbit   T6963C_cntlcd;             // CD command/data bit mask
extern  sfr sbit   T6963C_cntlrst;            // RST reset bit mask

extern  unsigned char   T6963C_display;       // display control byte


