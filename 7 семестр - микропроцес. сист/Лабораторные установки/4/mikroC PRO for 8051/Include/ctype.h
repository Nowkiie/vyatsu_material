#ifndef __CTYPE_H__
#define __CTYPE_H__

// In order to use Ctype library, select and check C_Type library in library manager
 
int islower(char character);
unsigned short isupper(char character);
unsigned short isalpha(char character);
unsigned short iscntrl(char character);
unsigned short isdigit(char character);
unsigned short isalnum(char character);
unsigned short isspace(char character);
unsigned short ispunct(char character);
unsigned short isgraph(char character);
unsigned short isxdigit(char character);
unsigned short tolower(char character);
unsigned short toupper(char character);
 
#endif