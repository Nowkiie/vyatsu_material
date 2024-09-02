/*
 * Project Name:
     Time_Demo (simplified c-like time library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20080930:
       - initial release; Author: Bruno Gavand.
 * Description  :
     Just run it in watch window and watch appropriate variables.
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

#include        "timelib.h"

TimeStruct ts1, ts2;
long epoch;
long diff;


void main() {

  ts1.ss = 0;
  ts1.mn = 7;
  ts1.hh = 17;
  ts1.md = 23;
  ts1.mo = 5;
  ts1.yy = 2006;

  /*
   * What is the epoch of the date in ts ?
   */
  epoch = Time_dateToEpoch(&ts1);      //  1148404020

  /*
   * What date is epoch 1234567890 ?
   */
  epoch = 1234567890;
  Time_epochToDate(epoch, &ts2);       //  {30, 31, 23, 13, 4, 2, 2009}

  /*
   * How much seconds between this two dates ?
   */
  diff = Time_dateDiff(&ts1, &ts2);    //  86163870
}