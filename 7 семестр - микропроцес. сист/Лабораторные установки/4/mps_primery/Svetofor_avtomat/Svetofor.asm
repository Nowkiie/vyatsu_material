
_ShiftRight:
;Svetofor.c,25 :: 		unsigned char ShiftRight(unsigned char prev)
;Svetofor.c,27 :: 		if (prev == 1)
	MOV A, FARG_ShiftRight_prev+0
	XRL A, #1
	JNZ L_ShiftRight0
;Svetofor.c,28 :: 		return 128;
	MOV R0, #128
	RET
L_ShiftRight0:
;Svetofor.c,30 :: 		prev >>= 1;
	MOV R1, #1
	MOV A, FARG_ShiftRight_prev+0
	INC R1
	SJMP L__ShiftRight37
L__ShiftRight38:
	CLR C
	RRC A
L__ShiftRight37:
	DJNZ R1, L__ShiftRight38
	MOV R0, A
	MOV FARG_ShiftRight_prev+0, 0
;Svetofor.c,31 :: 		return prev;
;Svetofor.c,32 :: 		}
	RET
; end of _ShiftRight

_init_string:
;Svetofor.c,38 :: 		void init_string()
;Svetofor.c,40 :: 		int i = str_size;
	MOV init_string_i_L0+0, #16
	MOV init_string_i_L0+1, #0
;Svetofor.c,41 :: 		for (i; i <= 16; ++i)
L_init_string2:
	SETB C
	MOV A, init_string_i_L0+0
	SUBB A, #16
	MOV A, #0
	XRL A, #128
	MOV R0, A
	MOV A, init_string_i_L0+1
	XRL A, #128
	SUBB A, R0
	JNC L_init_string3
;Svetofor.c,42 :: 		str[i] = ' ';
	MOV A, #_str+0
	ADD A, init_string_i_L0+0
	MOV R0, A
	MOV @R0, #32
;Svetofor.c,41 :: 		for (i; i <= 16; ++i)
	MOV A, #1
	ADD A, init_string_i_L0+0
	MOV init_string_i_L0+0, A
	MOV A, #0
	ADDC A, init_string_i_L0+1
	MOV init_string_i_L0+1, A
;Svetofor.c,42 :: 		str[i] = ' ';
	SJMP L_init_string2
L_init_string3:
;Svetofor.c,43 :: 		}
	RET
; end of _init_string

_out_str:
;Svetofor.c,47 :: 		void out_str()
;Svetofor.c,49 :: 		int i = 0;
	MOV out_str_i_L0+0, #0
	MOV out_str_i_L0+1, #0
;Svetofor.c,50 :: 		outcw(0x80);
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
;Svetofor.c,51 :: 		for (i; i < 16; ++i)
L_out_str5:
	CLR C
	MOV A, out_str_i_L0+0
	SUBB A, #16
	MOV A, #0
	XRL A, #128
	MOV R0, A
	MOV A, out_str_i_L0+1
	XRL A, #128
	SUBB A, R0
	JNC L_out_str6
;Svetofor.c,52 :: 		outd(str[(i+pos >= 16) ? i+pos-16 : i+pos]);
	MOV A, _pos+0
	ADD A, out_str_i_L0+0
	MOV R1, A
	CLR A
	ADDC A, out_str_i_L0+1
	MOV R2, A
	CLR C
	MOV A, R1
	SUBB A, #16
	MOV A, #0
	XRL A, #128
	MOV R0, A
	MOV A, R2
	XRL A, #128
	SUBB A, R0
	JC L_out_str8
	MOV A, _pos+0
	ADD A, out_str_i_L0+0
	MOV R0, A
	CLR A
	ADDC A, out_str_i_L0+1
	MOV R1, A
	CLR C
	MOV A, R0
	SUBB A, #16
	MOV R0, A
	MOV A, R1
	SUBB A, #0
	MOV R1, A
	MOV R2, 0
	MOV R3, 1
	SJMP L_out_str9
L_out_str8:
	MOV A, _pos+0
	ADD A, out_str_i_L0+0
	MOV R0, A
	CLR A
	ADDC A, out_str_i_L0+1
	MOV R1, A
	MOV R2, 0
	MOV R3, 1
L_out_str9:
	MOV A, #_str+0
	ADD A, R2
	MOV R0, A
	MOV FARG_outd_c+0, @R0
	LCALL _outd+0
;Svetofor.c,51 :: 		for (i; i < 16; ++i)
	MOV A, #1
	ADD A, out_str_i_L0+0
	MOV out_str_i_L0+0, A
	MOV A, #0
	ADDC A, out_str_i_L0+1
	MOV out_str_i_L0+1, A
;Svetofor.c,52 :: 		outd(str[(i+pos >= 16) ? i+pos-16 : i+pos]);
	LJMP L_out_str5
L_out_str6:
;Svetofor.c,53 :: 		if (pos == 0)
	MOV A, _pos+0
	JNZ L_out_str10
;Svetofor.c,54 :: 		pos = 16;
	MOV _pos+0, #16
L_out_str10:
;Svetofor.c,55 :: 		--pos;
	DEC _pos+0
;Svetofor.c,56 :: 		}
	RET
; end of _out_str

_main:
	MOV SP+0, #128
;Svetofor.c,58 :: 		void main (void) {
;Svetofor.c,61 :: 		init();
	LCALL _init+0
;Svetofor.c,62 :: 		RED = 0;      // Красный цвет
	CLR P0_0_bit+0
;Svetofor.c,63 :: 		YEL = 1;      // Желтый цвет
	SETB P0_1_bit+0
;Svetofor.c,64 :: 		GRN = 1;      // Зеленый цвет
	SETB P0_2_bit+0
;Svetofor.c,65 :: 		lcd_led = 0;  // Подсветка индикатора
	CLR P0_4_bit+0
;Svetofor.c,66 :: 		tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
	MOV FARG_rd_EEPROM_addr+0, #0
	MOV FARG_rd_EEPROM_addr+1, #0
	LCALL _rd_EEPROM+0
	MOV _tr+0, 0
	SETB C
	MOV A, R0
	SUBB A, #30
	JNC L__main36
	CLR C
	MOV A, _tr+0
	SUBB A, #5
	JC L__main36
	SJMP L_main13
L__main36:
	MOV _tr+0, #5
L_main13:
;Svetofor.c,67 :: 		ty=rd_EEPROM(2); if((ty>30)||(ty<5)) ty=5;
	MOV FARG_rd_EEPROM_addr+0, #2
	MOV FARG_rd_EEPROM_addr+1, #0
	LCALL _rd_EEPROM+0
	MOV _ty+0, 0
	SETB C
	MOV A, R0
	SUBB A, #30
	JNC L__main35
	CLR C
	MOV A, _ty+0
	SUBB A, #5
	JC L__main35
	SJMP L_main16
L__main35:
	MOV _ty+0, #5
L_main16:
;Svetofor.c,68 :: 		tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;
	MOV FARG_rd_EEPROM_addr+0, #1
	MOV FARG_rd_EEPROM_addr+1, #0
	LCALL _rd_EEPROM+0
	MOV _tg+0, 0
	SETB C
	MOV A, R0
	SUBB A, #30
	JNC L__main34
	CLR C
	MOV A, _tg+0
	SUBB A, #5
	JC L__main34
	SJMP L_main19
L__main34:
	MOV _tg+0, #5
L_main19:
;Svetofor.c,74 :: 		while (1) {
L_main20:
;Svetofor.c,75 :: 		key=ScanKbd();
	LCALL _ScanKbd+0
	MOV _key+0, 0
;Svetofor.c,76 :: 		switch (state) {
	SJMP L_main22
;Svetofor.c,77 :: 		case R: // Красный
L_main24:
;Svetofor.c,79 :: 		clear_lcd(); //outcw(0x81); outd('К'); outd('Л'); //outd('р'); outd('а');
	LCALL _clear_lcd+0
;Svetofor.c,80 :: 		out_str();
	LCALL _out_str+0
;Svetofor.c,82 :: 		if (T_FLAG) { state=Y;  T_FLAG = 0;  YEL=0; RED=1; }
	MOV A, _T_FLAG+0
	JZ L_main25
	MOV _state+0, #5
	MOV _T_FLAG+0, #0
	CLR P0_1_bit+0
	SETB P0_0_bit+0
L_main25:
;Svetofor.c,83 :: 		break;
	SJMP L_main23
;Svetofor.c,84 :: 		case G: // Зеленый
L_main26:
;Svetofor.c,86 :: 		clear_lcd(); //outcw(0x80); outd('З'); //outd('е'); outd('л');
	LCALL _clear_lcd+0
;Svetofor.c,87 :: 		out_str();
	LCALL _out_str+0
;Svetofor.c,89 :: 		if (T_FLAG) { state=R;  T_FLAG = 0; GRN=1; RED=0;}
	MOV A, _T_FLAG+0
	JZ L_main27
	MOV _state+0, #1
	MOV _T_FLAG+0, #0
	SETB P0_2_bit+0
	CLR P0_0_bit+0
L_main27:
;Svetofor.c,90 :: 		break;
	SJMP L_main23
;Svetofor.c,91 :: 		case Y: // Желтый
L_main28:
;Svetofor.c,93 :: 		clear_lcd(); //outcw(0x80); outd('Ж'); //outd('е'); outd('л');
	LCALL _clear_lcd+0
;Svetofor.c,94 :: 		out_str();
	LCALL _out_str+0
;Svetofor.c,96 :: 		if (T_FLAG) { state=G;  T_FLAG = 0; GRN=0; YEL=1; }
	MOV A, _T_FLAG+0
	JZ L_main29
	MOV _state+0, #3
	MOV _T_FLAG+0, #0
	CLR P0_2_bit+0
	SETB P0_1_bit+0
L_main29:
;Svetofor.c,97 :: 		break;
	SJMP L_main23
;Svetofor.c,98 :: 		}
L_main22:
	MOV A, _state+0
	XRL A, #1
	JZ L_main24
	MOV A, _state+0
	XRL A, #3
	JZ L_main26
	MOV A, _state+0
	XRL A, #5
	JZ L_main28
L_main23:
;Svetofor.c,99 :: 		DelayMs(100);            // такт работы автомата
	MOV FARG_DelayMs_m+0, #100
	MOV FARG_DelayMs_m+1, #0
	LCALL _DelayMs+0
;Svetofor.c,100 :: 		if(t==0) T_FLAG=1; else t--;  // счетчик
	MOV A, _t+0
	JNZ L_main30
	MOV _T_FLAG+0, #1
	SJMP L_main31
L_main30:
	DEC _t+0
L_main31:
;Svetofor.c,101 :: 		}
	LJMP L_main20
;Svetofor.c,102 :: 		}
	SJMP #254
; end of _main

_DelayMs:
;Svetofor.c,116 :: 		void DelayMs(unsigned int m){  // задержка по таймеру
;Svetofor.c,119 :: 		ms=0;
	MOV _ms+0, #0
	MOV _ms+1, #0
;Svetofor.c,120 :: 		WMCON.WDTRST=1; // сброс сторожевого таймера
	SETB C
	MOV A, WMCON+0
	MOV #224, C
	MOV WMCON+0, A
;Svetofor.c,121 :: 		while(ms!=m) continue;
L_DelayMs32:
	MOV A, _ms+0
	XRL A, FARG_DelayMs_m+0
	JNZ L__DelayMs39
	MOV A, _ms+1
	XRL A, FARG_DelayMs_m+1
L__DelayMs39:
	JZ L_DelayMs33
	SJMP L_DelayMs32
L_DelayMs33:
;Svetofor.c,122 :: 		}
	RET
; end of _DelayMs

_Timer1InterruptHandler:
	PUSH PSW+0
	PUSH 224
	PUSH B+0
	PUSH 130
	PUSH 131
;Svetofor.c,124 :: 		void Timer1InterruptHandler() org IVT_ADDR_ET1{
;Svetofor.c,126 :: 		EA_bit = 0;        // Clear global interrupt enable flag
	CLR EA_bit+0
;Svetofor.c,127 :: 		TF1_bit = 0;       // Ensure that Timer1 interrupt flag is cleared
	CLR TF1_bit+0
;Svetofor.c,129 :: 		TR1_bit = 0;       // Stop Timer1
	CLR TR1_bit+0
;Svetofor.c,130 :: 		TH1 = 0xFC;        // Reset Timer1 high byte  65536-1000
	MOV TH1+0, #252
;Svetofor.c,131 :: 		TL1 = 0x18;        // Reset Timer1 low byte
	MOV TL1+0, #24
;Svetofor.c,134 :: 		ms++;
	MOV A, #1
	ADD A, _ms+0
	MOV _ms+0, A
	MOV A, #0
	ADDC A, _ms+1
	MOV _ms+1, A
;Svetofor.c,136 :: 		EA_bit = 1;        // Set global interrupt enable flag
	SETB EA_bit+0
;Svetofor.c,137 :: 		TR1_bit = 1;       // Run Timer1
	SETB TR1_bit+0
;Svetofor.c,138 :: 		}
	POP 131
	POP 130
	POP B+0
	POP 224
	POP PSW+0
	RETI
; end of _Timer1InterruptHandler

_INT0_Interrupt:
	PUSH PSW+0
	PUSH 224
	PUSH B+0
	PUSH 130
	PUSH 131
;Svetofor.c,140 :: 		void INT0_Interrupt() org IVT_ADDR_EX0 {
;Svetofor.c,141 :: 		EA_bit = 0;
	CLR EA_bit+0
;Svetofor.c,142 :: 		lcd_led=~lcd_led;
	MOV C, P0_4_bit+0
	CPL C
	MOV P0_4_bit+0, C
;Svetofor.c,143 :: 		EA_bit = 1;
	SETB EA_bit+0
;Svetofor.c,144 :: 		}
	POP 131
	POP 130
	POP B+0
	POP 224
	POP PSW+0
	RETI
; end of _INT0_Interrupt
