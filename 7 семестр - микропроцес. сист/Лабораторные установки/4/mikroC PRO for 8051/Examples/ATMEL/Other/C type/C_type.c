/*
 * Project name:
     C_type
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This program demonstrates usage of standard C_type library routines. 
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
     - None.
*/

char res;

void main(){

//-------------- Returns 1 if the given character is a lowercase letter
 res = islower('o');
 res = islower('A');
 res = islower('1');

//-------------- Returns 1 if the given character is an UPPERCASE letter
 res = isupper('o');
 res = isupper('A');
 res = isupper('1');

//-------------- Returns 1 if the given character is a letter
 res = isalpha('o');
 res = isalpha('A');
 res = isalpha('1');

//-------------- Returns 1 if the given character is a control character
 res = iscntrl('o');
 res = iscntrl('\r');
 res = iscntrl('1');

//-------------- Returns 1 if the given character is a cipher (digit)
 res = isdigit('o');
 res = isdigit('\r');
 res = isdigit('1');

//-------------- Returns 1 if the given character is alphanumeric (cipher or letter)
 res = isalnum('o');
 res = isalnum('\r');
 res = isalnum('1');

//-------------- Returns 1 if the given character is space or tab
 res = isspace('o');
 res = isspace(' ');
 res = isspace('\t');

//-------------- Returns 1 if the given character is a punctuation mark
 res = ispunct('o');
 res = ispunct(',');
 res = ispunct('.');
 res = ispunct('1');
 res = ispunct(':');

//-------------- Returns 1 if the given character is a graphical character
 res = isgraph('o');
 res = isgraph(' ');
 res = isgraph('\t');

//-------------- Returns 1 if given character is a hex digit
 res = isxdigit('o');
 res = isxdigit('a');
 res = isxdigit('B');
 

//-------------- Transposes uppercase letter to lowercase
 res = tolower('o');
 res = tolower('a');
 res = tolower('B');

//-------------- Transposes lowercase letter to uppercase
 res = toupper('o');
 res = toupper('a');
 res = toupper('B');

}
