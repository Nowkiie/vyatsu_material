#ifndef __stdlib_h
#define __stdlib_h

// In order to use stdlib, select and check C_Stdlib library in library manager

#define RAND_MAX 0x7fff

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

int abs(int a);
float atof(char * s);
int atoi(char * s); 
long atol(char * s);
div_t div(int number, int denom);
ldiv_t ldiv(long number, long denom);
uldiv_t uldiv(unsigned long number, unsigned long denom);
long labs(long x);
int max(int a, int b);
int min(int a, int b);
void srand(unsigned x);
int rand();
int xtoi(char * s);
 
#endif
// end of stdlib.h
