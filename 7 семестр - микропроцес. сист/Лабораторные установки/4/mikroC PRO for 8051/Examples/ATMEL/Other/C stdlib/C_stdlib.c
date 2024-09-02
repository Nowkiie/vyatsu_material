/*
 * Project name:
     C_Stdlib
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This program demonstrates usage of standard C stdlib library routines. 
     Compile and run the code through software simulator.
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - This code is compiled in segments due to ram memory limitations.
*/

typedef struct divstruct {
  int quot;
  int rem;
} div_t;

typedef struct ldivstruct {
  long quot;
  long rem;
} ldiv_t;

typedef struct uldivstruct {
  unsigned long quot;
  unsigned long rem;
} uldiv_t;   

int res;
double doub;
long res_l;

div_t dt;
ldiv_t dl;
uldiv_t dul;

/*uncomment appropriate define in order to compile wanted code segment*/
#define CODE_SEGMENT1
//#define CODE_SEGMENT2
//#define CODE_SEGMENT3

void main() {

  #ifdef CODE_SEGMENT1
     res = abs(12);
     res = abs(-12);
     res = abs(32767);
     res = abs(-32767);


     doub = atof("0.");
     doub = atof("-1.23");
     doub = atof("23.45e6");
     doub = atof("3E+10");
     doub = atof(".09E34");
  #endif
     
  #ifdef CODE_SEGMENT2
     res = atoi("1");
     res = atoi("-1");
     res = atoi("1222");
     res = atoi("32000");
     res = atoi("-32560");

     res_l = atol("1");
     res_l = atol("-1");
     res_l = atol("1222");
     res_l = atol("32000");
     res_l = atol("-32560");

     res_l = atol("-2147483647");
     res_l = atol(" 2147483647");
  #endif

  #ifdef CODE_SEGMENT3
     dt = div(1234,100);
     dl = ldiv(-123456, 1000);
     dul = uldiv(123456,1000);

     res_l = labs(-2147483647);
     res_l = labs(2147483647);
     res = min(123,67);
     res = max(12333,67);
     res = xtoi("-1F");
     res = xtoi("1FF");
     srand(9);
     while(1)
       res =  rand();
  #endif
     
}