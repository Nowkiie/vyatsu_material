/******************************************************************************/
/*                                                                            */
/* FILENAME   : Delays.c                                                      */
/* PROJECT    : MikroC delays                                                 */
/* CPU TYPE   : 8051 family                                                   */
/* COMPILER   : microC compiler for 8051 v. 1.0.0.0 (071207)                  */
/*                                                                            */
/*                                                                            */
/**************************** CHANGE AND RELEASE LOG **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created file                                     | 071207 | ST   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*  Function:     unsigned long Get_Fosc_kHz()                                */
/*                                                                            */
/*  Purpose:      Obtaining the project clock value.                          */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: Project clock value in kHz.                                 */
/*                                                                            */
/*  Requires :    Nothing.                                                    */
/*                                                                            */
/*  Example  :    Proj_Clk = Get_Fosc_kHz();                                  */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
unsigned long Get_Fosc_kHz() {
  return Clock_kHz();
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_1us()                                            */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 1us               */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_1us();                                                */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_1us() {
  Delay_us(1);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_10us()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 10us              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_10us();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_10us() {
  Delay_us(10);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_22us()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 22us              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_22us();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_22us() {
  Delay_us(22);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_50us()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 50us              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_50us();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_50us() {
  Delay_us(50);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_80us()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 80us              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_80us();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_80us() {
  Delay_us(78);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_500us()                                          */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 500us             */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_500us();                                              */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_500us() {
  Delay_us(498);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_5500us()                                         */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 5500us            */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_us function.                                 */
/*                                                                            */
/*  Example  :    Delay_5500us();                                             */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_5500us() {
  Delay_us(5500);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_8ms()                                            */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 8ms               */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_ms function.                                 */
/*                                                                            */
/*  Example  :    Delay_8ms();                                                */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_8ms() {
  Delay_ms(8);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_10ms()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 10ms              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_ms function.                                 */
/*                                                                            */
/*  Example  :    Delay_10ms();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
void Delay_10ms() {
  Delay_ms(10);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_100ms()                                          */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 100ms             */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_ms function.                                 */
/*                                                                            */
/*  Example  :    Delay_100ms();                                              */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_100ms() {
  Delay_ms(100);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_1sec()                                           */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of 1sec              */
/*                                                                            */
/*  CallParams:   None.                                                       */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Built in Delay_ms function.                                 */
/*                                                                            */
/*  Example  :    Delay_1sec();                                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
 void Delay_1sec()
{
  Delay_ms(1000);
}

/******************************************************************************/
/*                                                                            */
/*  Function:     void Delay_Cyc(char cycles_div_by_10)                       */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of                   */
/*                cycles_div_by_10 * 10 cycles,                               */
/*                                                                            */
/*  CallParams:   cycles_div_by_10 - Number of cycles divided by 10.          */
/*                                   Valid values: 3..255                     */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Nothing.                                                    */
/*                                                                            */
/*  Example  :    Delay_Cyc(10); // a hundred cycles delay                    */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
void Delay_Cyc(char cycles_div_by_10)  { // Cycles_div_by_10: min 2, max 257

  --cycles_div_by_10;
  --cycles_div_by_10;

  while (cycles_div_by_10 != 0) {   //  while loop takes 10 cycles
    --cycles_div_by_10;             //
    asm nop;                        //
  }                                 //

}

/******************************************************************************/
/*                                                                            */
/*  Function:     void VDelay_ms(unsigned Time_ms)                            */
/*                                                                            */
/*  Purpose:      Causes a blocking, interruptable delay of                   */
/*                Time_ms miliseconds                                         */
/*                                                                            */
/*  CallParams:   Time_ms - time to delay in ms                               */
/*                                                                            */
/*  ReturnValues: None.                                                       */
/*                                                                            */
/*  Requires :    Delay_Cyc routine.                                          */
/*                                                                            */
/*  Note :        - if input parameter is a literal constant, this delay will */
/*                  be 100% accurate.                                         */
/*                - if input parameter is a variable, this delay will have    */
/*                  one cycle error.                                          */
/*                                                                            */
/*  Example  :    VDelay_ms(3);  // a 3ms delay                               */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created function                                 | 071207 | ST   */
/*         |                                                  |        |      */
/******************************************************************************/
void VDelay_ms(unsigned Time_ms) {
  unsigned long NumberOfCyc;
  
  NumberOfCyc = Clock_kHz()/__FOSC_PER_CYC; // this will be done by compiler, no asm will be genereated except that for assignment;
  NumberOfCyc = NumberOfCyc *  Time_ms;
  NumberOfCyc = NumberOfCyc >> 6;           // Dec and While below take around 64 instructions

  if (NumberOfCyc > 5)                      // correction for code outside the while loop
    NumberOfCyc -= 5;
  else
    NumberOfCyc = 0;
    
  while (NumberOfCyc)                              //  while loop takes 64 cycles
    {                                              //
      --NumberOfCyc;                               //
      asm nop; asm nop;                            //
      asm nop; asm nop; asm nop; asm nop; asm nop; //
      asm nop; asm nop; asm nop; asm nop; asm nop; //
      asm nop; asm nop; asm nop; asm nop; asm nop; //
      asm nop; asm nop; asm nop; asm nop; asm nop; //
      asm nop; asm nop; asm nop; asm nop;          //
    }
}
