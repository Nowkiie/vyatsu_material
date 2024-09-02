
_Get_Fosc_kHz:
;__Lib_Delays.c,38 :: 		unsigned long Get_Fosc_kHz() {
;__Lib_Delays.c,39 :: 		return Clock_kHz();
	MOV R0, #224
	MOV R1, #46
	MOV A, R1
	RLC A
	CLR A
	SUBB A, 224
	MOV R2, A
	MOV R3, A
;__Lib_Delays.c,40 :: 		}
	RET
; end of _Get_Fosc_kHz

_Delay_1us:
;__Lib_Delays.c,63 :: 		void Delay_1us() {
;__Lib_Delays.c,64 :: 		Delay_us(1);
	NOP
;__Lib_Delays.c,65 :: 		}
	RET
; end of _Delay_1us

_Delay_10us:
;__Lib_Delays.c,88 :: 		void Delay_10us() {
;__Lib_Delays.c,89 :: 		Delay_us(10);
	MOV R7, 4
	DJNZ R7, 
	NOP
;__Lib_Delays.c,90 :: 		}
	RET
; end of _Delay_10us

_Delay_22us:
;__Lib_Delays.c,113 :: 		void Delay_22us() {
;__Lib_Delays.c,114 :: 		Delay_us(22);
	MOV R7, 10
	DJNZ R7, 
	NOP
;__Lib_Delays.c,115 :: 		}
	RET
; end of _Delay_22us

_Delay_50us:
;__Lib_Delays.c,138 :: 		void Delay_50us() {
;__Lib_Delays.c,139 :: 		Delay_us(50);
	MOV R7, 24
	DJNZ R7, 
	NOP
;__Lib_Delays.c,140 :: 		}
	RET
; end of _Delay_50us

_Delay_80us:
;__Lib_Delays.c,163 :: 		void Delay_80us() {
;__Lib_Delays.c,164 :: 		Delay_us(78);
	MOV R7, 38
	DJNZ R7, 
	NOP
;__Lib_Delays.c,165 :: 		}
	RET
; end of _Delay_80us

_Delay_500us:
;__Lib_Delays.c,188 :: 		void Delay_500us() {
;__Lib_Delays.c,189 :: 		Delay_us(498);
	MOV R7, 248
	DJNZ R7, 
	NOP
;__Lib_Delays.c,190 :: 		}
	RET
; end of _Delay_500us

_Delay_5500us:
;__Lib_Delays.c,213 :: 		void Delay_5500us() {
;__Lib_Delays.c,214 :: 		Delay_us(5500);
	MOV R6, 11
	MOV R7, 178
	DJNZ R7, 
	DJNZ R6, 
;__Lib_Delays.c,215 :: 		}
	RET
; end of _Delay_5500us

_Delay_8ms:
;__Lib_Delays.c,238 :: 		void Delay_8ms() {
;__Lib_Delays.c,239 :: 		Delay_ms(8);
	MOV R6, 16
	MOV R7, 143
	DJNZ R7, 
	DJNZ R6, 
;__Lib_Delays.c,240 :: 		}
	RET
; end of _Delay_8ms

_Delay_10ms:
;__Lib_Delays.c,263 :: 		void Delay_10ms() {
;__Lib_Delays.c,264 :: 		Delay_ms(10);
	MOV R6, 20
	MOV R7, 115
	DJNZ R7, 
	DJNZ R6, 
;__Lib_Delays.c,265 :: 		}
	RET
; end of _Delay_10ms

_Delay_100ms:
;__Lib_Delays.c,288 :: 		void Delay_100ms() {
;__Lib_Delays.c,289 :: 		Delay_ms(100);
	MOV R6, 195
	MOV R7, 140
	DJNZ R7, 
	DJNZ R6, 
;__Lib_Delays.c,290 :: 		}
	RET
; end of _Delay_100ms

_Delay_1sec:
;__Lib_Delays.c,313 :: 		void Delay_1sec()
;__Lib_Delays.c,315 :: 		Delay_ms(1000);
	MOV R5, 8
	MOV R6, 154
	MOV R7, 124
	DJNZ R7, 
	DJNZ R6, 
	DJNZ R5, 
	NOP
;__Lib_Delays.c,316 :: 		}
	RET
; end of _Delay_1sec

_Delay_Cyc:
;__Lib_Delays.c,341 :: 		void Delay_Cyc(char cycles_div_by_10)  { // Cycles_div_by_10: min 2, max 257
;__Lib_Delays.c,343 :: 		--cycles_div_by_10;
	DEC FARG_Delay_Cyc_cycles_div_by_10+0
;__Lib_Delays.c,344 :: 		--cycles_div_by_10;
	DEC FARG_Delay_Cyc_cycles_div_by_10+0
;__Lib_Delays.c,346 :: 		while (cycles_div_by_10 > 0) {    //  while loop takes 10 cycles
L_Delay_Cyc0:
	SETB C
	MOV A, FARG_Delay_Cyc_cycles_div_by_10+0
	SUBB A, #0
	JC L_Delay_Cyc1
;__Lib_Delays.c,347 :: 		--cycles_div_by_10;             //
	DEC FARG_Delay_Cyc_cycles_div_by_10+0
;__Lib_Delays.c,348 :: 		asm nop;                        //
	NOP
;__Lib_Delays.c,349 :: 		asm nop;                        //
	NOP
;__Lib_Delays.c,350 :: 		}                                 //
	SJMP L_Delay_Cyc0
L_Delay_Cyc1:
;__Lib_Delays.c,352 :: 		asm nop;
	NOP
;__Lib_Delays.c,353 :: 		asm nop;
	NOP
;__Lib_Delays.c,354 :: 		asm nop;
	NOP
;__Lib_Delays.c,355 :: 		asm nop;
	NOP
;__Lib_Delays.c,356 :: 		asm nop;
	NOP
;__Lib_Delays.c,357 :: 		asm nop;
	NOP
;__Lib_Delays.c,358 :: 		asm nop;
	NOP
;__Lib_Delays.c,359 :: 		}
	RET
; end of _Delay_Cyc

_VDelay_ms:
;__Lib_Delays.c,388 :: 		void VDelay_ms(unsigned Time_ms) {
;__Lib_Delays.c,391 :: 		NumberOfCyc = Clock_kHz()/12; // this will be done by compiler, no asm will be genereated except that for assignment;
	MOV VDelay_ms_NumberOfCyc_L0+0, #232
	MOV VDelay_ms_NumberOfCyc_L0+1, #3
	MOV VDelay_ms_NumberOfCyc_L0+2, #0
	MOV VDelay_ms_NumberOfCyc_L0+3, #0
;__Lib_Delays.c,392 :: 		NumberOfCyc = NumberOfCyc *  Time_ms;
	MOV R0, #232
	MOV R1, #3
	MOV R2, #0
	MOV R3, #0
	MOV R4, FARG_VDelay_ms_Time_ms+0
	MOV R5, FARG_VDelay_ms_Time_ms+1
	CLR A
	MOV R6, A
	CLR A
	MOV 7, A
	LCALL _Mul_32x32+0
	MOV VDelay_ms_NumberOfCyc_L0+0, 0
	MOV VDelay_ms_NumberOfCyc_L0+1, 1
	MOV VDelay_ms_NumberOfCyc_L0+2, 2
	MOV VDelay_ms_NumberOfCyc_L0+3, 3
;__Lib_Delays.c,393 :: 		NumberOfCyc = NumberOfCyc >> 5; // Dec and While below take around 32 instructions
	MOV R4, #5
	LCALL __shr_longword+0
	MOV VDelay_ms_NumberOfCyc_L0+0, 0
	MOV VDelay_ms_NumberOfCyc_L0+1, 1
	MOV VDelay_ms_NumberOfCyc_L0+2, 2
	MOV VDelay_ms_NumberOfCyc_L0+3, 3
;__Lib_Delays.c,395 :: 		if (NumberOfCyc > 8)
	SETB C
	MOV A, R0
	SUBB A, #8
	MOV A, R1
	SUBB A, #0
	MOV A, R2
	SUBB A, #0
	MOV A, R3
	SUBB A, #0
	JC L_VDelay_ms2
;__Lib_Delays.c,396 :: 		NumberOfCyc -= 8;
	CLR C
	MOV A, VDelay_ms_NumberOfCyc_L0+0
	SUBB A, #8
	MOV VDelay_ms_NumberOfCyc_L0+0, A
	MOV A, VDelay_ms_NumberOfCyc_L0+1
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+1, A
	MOV A, VDelay_ms_NumberOfCyc_L0+2
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+2, A
	MOV A, VDelay_ms_NumberOfCyc_L0+3
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+3, A
	SJMP L_VDelay_ms3
L_VDelay_ms2:
;__Lib_Delays.c,398 :: 		NumberOfCyc = 0;
	MOV VDelay_ms_NumberOfCyc_L0+0, #0
	MOV VDelay_ms_NumberOfCyc_L0+1, #0
	MOV VDelay_ms_NumberOfCyc_L0+2, #0
	MOV VDelay_ms_NumberOfCyc_L0+3, #0
L_VDelay_ms3:
;__Lib_Delays.c,400 :: 		while (NumberOfCyc)             //  while loop takes 32 cycles
L_VDelay_ms4:
	MOV A, VDelay_ms_NumberOfCyc_L0+0
	ORL A, VDelay_ms_NumberOfCyc_L0+1
	ORL A, VDelay_ms_NumberOfCyc_L0+2
	ORL A, VDelay_ms_NumberOfCyc_L0+3
	JZ L_VDelay_ms5
;__Lib_Delays.c,402 :: 		--NumberOfCyc;              //
	CLR C
	MOV A, VDelay_ms_NumberOfCyc_L0+0
	SUBB A, #1
	MOV VDelay_ms_NumberOfCyc_L0+0, A
	MOV A, VDelay_ms_NumberOfCyc_L0+1
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+1, A
	MOV A, VDelay_ms_NumberOfCyc_L0+2
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+2, A
	MOV A, VDelay_ms_NumberOfCyc_L0+3
	SUBB A, #0
	MOV VDelay_ms_NumberOfCyc_L0+3, A
;__Lib_Delays.c,403 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,404 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,405 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,407 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,408 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,409 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,411 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,412 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,413 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,415 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,416 :: 		asm nop;                    //
	NOP
;__Lib_Delays.c,417 :: 		}
	SJMP L_VDelay_ms4
L_VDelay_ms5:
;__Lib_Delays.c,418 :: 		}
	RET
; end of _VDelay_ms
