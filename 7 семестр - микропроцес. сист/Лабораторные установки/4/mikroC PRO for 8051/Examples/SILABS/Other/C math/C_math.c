/*
 * Project name:
     C_math (Demonstration of using C Math Library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This program demonstrates usage of standard C math library routines. 
     Compile and run the code through software simulator.          
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
 */

const double PI = 3.14159;
double doub;
char temp_char;

static union both
{
  struct flt
  {
    unsigned char   mant[2];
    unsigned        hmant:7;
    unsigned        exp:8;
    unsigned        sign:1;
  } flt;
  double        fl;
};
union both uv;



void main(){
  doub = fabs(-1.3);        // 1.3
  doub = fabs(-1.3e-5);     // 1.3e-5
  doub = fabs(1241.3e+15);  // 1.2413e18

  doub = acos(0.);          // 1.570796
  doub = acos(0.5);         // 1.047198
  doub = acos(1.0);         // 0.000000
  doub = acos(-0.5);        // 2.094395

  doub = asin(0.);          // 0.000000
  doub = asin(0.5);         // 5.235987e-1
  doub = asin(1.0);         // 1.570796
  doub = asin(-0.5);        //-5.235987e-1

  doub = atan(0.);          // 0.000000
  doub = atan(0.5);         // 4.636475e-1
  doub = atan(1.0);         // 7.853982e-1
  doub = atan(-1.0);        //-7.853982e-1

  doub = atan2( 5., 0.);    // 0.000000
  doub = atan2(2., 1.);     // 4.636475e-1
  doub = atan2(10., 10.);   // 7.853982e-1
  doub = atan2(10., -10.);  //-7.853982e-1

  doub = ceil(0.5);         // 1.000000
  doub = ceil(-0.5);        // 0.000000
  doub = ceil(15.258);      // 16.000000
  doub = ceil(-15.258);     //-15.000000

  doub = floor(0.5);        // 0.000000
  doub = floor(-0.5);       //-1.000000
  doub = floor(15.258);     // 15.000000
  doub = floor(-15.258);    //-16.000000

  doub =  cos(0.);          // 1.000000
  doub =  cos(PI/2.);       // 0.000000 (1.310775e-6)
  doub =  cos(PI/3.);       // 0.500007
  doub =  cos(-PI/3.);      // 0.500007

  doub =  cosh(0.);         // 1.000000
  doub =  cosh(PI/2.);      // 2.509176
  doub =  cosh(PI/3.);      // 1.600286
  doub =  cosh(-PI/3.);     // 1.600286

  doub =  exp(10.25);       // 2.828255e+4
  doub =  exp(0.5);         // 1.648721
  doub =  exp(-0.5);        // 0.606530

  doub = log10(100.);       // 2.000000
  doub = log10(500.);       // 2.698970
  doub = log10(-10.);       // invalid (0.00)

  doub = pow(10.,5.);       // 1.000001e+5
  doub = pow(10.,-0.5);     // 0.316227

  doub =  sin(0.);          // 0.000000
  doub =  sin(PI/2.);       // 1.000000
  doub =  sin(PI/6.);       // 0.499999
  doub =  sin(-PI/6.);      //-0.499999

  doub =  sinh(0.);         // 0.000000
  doub =  sinh(PI/2.);      // 2.301296
  doub =  sinh(PI/6.);      // 0.547853
  doub =  sinh(-PI/6.);     //-0.547853

  doub = sqrt(10000.);      // 100.0000
  doub = sqrt(500.);        // 22.36068
  doub = sqrt(-100.);       // invalid (0.00)

  doub = tan(-PI/2.);       // infinite (-7.626009e+05)
  doub = tan(0.);           // 0.000000
  doub = tan(PI/4.);        // 0.999998
  doub = tan(-PI/4.);       //-0.999998

  doub = tanh(PI/2.);       // 0.917152
  doub = tanh(0.);          // 0.000000
  doub = tanh(PI/4.);       // 0.655793
  doub = tanh(-PI/4.);      //-0.655793
}