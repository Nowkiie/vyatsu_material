
_main:
	MOV SP+0, #128
;Svetofor.c,24 :: 		void main (void) {
;Svetofor.c,27 :: 		init();
	LCALL _init+0
;Svetofor.c,28 :: 		RED = 0;      // Красный цвет
	CLR P0_0_bit+0
;Svetofor.c,29 :: 		YEL = 1;      // Желтый цвет
	SETB P0_1_bit+0
;Svetofor.c,30 :: 		GRN = 1;      // Зеленый цвет
	SETB P0_2_bit+0
;Svetofor.c,31 :: 		lcd_led = 0;  // Подсветка индикатора
	CLR P0_4_bit+0
;Svetofor.c,32 :: 		tr=rd_EEPROM(0); if((tr>30)||(tr<5)) tr=5;
	MOV FARG_rd_EEPROM_addr+0, #0
	MOV FARG_rd_EEPROM_addr+1, #0
	LCALL _rd_EEPROM+0
	MOV _tr+0, 0
	SETB C
	MOV A, R0
	SUBB A, #30
	JNC L__main52
	CLR C
	MOV A, _tr+0
	SUBB A, #5
	JC L__main52
	SJMP L_main2
L__main52:
	MOV _tr+0, #5
L_main2:
;Svetofor.c,33 :: 		tg=rd_EEPROM(1); if((tg>30)||(tg<5)) tg=5;
	MOV FARG_rd_EEPROM_addr+0, #1
	MOV FARG_rd_EEPROM_addr+1, #0
	LCALL _rd_EEPROM+0
	MOV _tg+0, 0
	SETB C
	MOV A, R0
	SUBB A, #30
	JNC L__main51
	CLR C
	MOV A, _tg+0
	SUBB A, #5
	JC L__main51
	SJMP L_main5
L__main51:
	MOV _tg+0, #5
L_main5:
;Svetofor.c,35 :: 		for(t=0;t!=0;t++); // тест задержки
	MOV _t+0, #0
L_main6:
	MOV A, _t+0
	JZ L_main7
	INC _t+0
	SJMP L_main6
L_main7:
;Svetofor.c,36 :: 		t = 10*tr;
	MOV B+0, _tr+0
	MOV A, #10
	MUL AB
	MOV R0, A
	MOV _t+0, 0
;Svetofor.c,39 :: 		while (1) {
L_main9:
;Svetofor.c,40 :: 		key=ScanKbd();
	LCALL _ScanKbd+0
	MOV _key+0, 0
;Svetofor.c,41 :: 		switch (state) {
	LJMP L_main11
;Svetofor.c,42 :: 		case R: // Красный
L_main13:
;Svetofor.c,44 :: 		clear_lcd(); outcw(0x80); outd('К'); //outd('р'); outd('а');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #202
	LCALL _outd+0
;Svetofor.c,46 :: 		if (T_FLAG) { state=RY;  T_FLAG = 0;  t=20;  YEL=0; }
	MOV A, _T_FLAG+0
	JZ L_main14
	MOV _state+0, #2
	MOV _T_FLAG+0, #0
	MOV _t+0, #20
	CLR P0_1_bit+0
	SJMP L_main15
L_main14:
;Svetofor.c,47 :: 		else if (key == '8') { state=SR;  RED=1; }
	MOV A, _key+0
	XRL A, #56
	JNZ L_main16
	MOV _state+0, #6
	SETB P0_0_bit+0
L_main16:
L_main15:
;Svetofor.c,48 :: 		break;
	LJMP L_main12
;Svetofor.c,49 :: 		case RY: // Красный-желтый
L_main17:
;Svetofor.c,51 :: 		clear_lcd(); outcw(0x80); outd('К'); outd('р'); outd('.'); outd('-');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #202
	LCALL _outd+0
	MOV FARG_outd_c+0, #240
	LCALL _outd+0
	MOV FARG_outd_c+0, #46
	LCALL _outd+0
	MOV FARG_outd_c+0, #45
	LCALL _outd+0
;Svetofor.c,52 :: 		outd('ж'); outd('.'); //outd('е'); outd('л'); outd('т'); outd('ы'); outd('й');
	MOV FARG_outd_c+0, #230
	LCALL _outd+0
	MOV FARG_outd_c+0, #46
	LCALL _outd+0
;Svetofor.c,53 :: 		if (T_FLAG) { state=G;  T_FLAG = 0;  t=10*tg;  RED=1; YEL=1; GRN=0; }
	MOV A, _T_FLAG+0
	JZ L_main18
	MOV _state+0, #3
	MOV _T_FLAG+0, #0
	MOV B+0, _tg+0
	MOV A, #10
	MUL AB
	MOV R0, A
	MOV _t+0, 0
	SETB P0_0_bit+0
	SETB P0_1_bit+0
	CLR P0_2_bit+0
	SJMP L_main19
L_main18:
;Svetofor.c,54 :: 		else if (key == '8') { state=SR;  RED=1; YEL=1; }
	MOV A, _key+0
	XRL A, #56
	JNZ L_main20
	MOV _state+0, #6
	SETB P0_0_bit+0
	SETB P0_1_bit+0
L_main20:
L_main19:
;Svetofor.c,55 :: 		break;
	LJMP L_main12
;Svetofor.c,56 :: 		case G: // Зеленый
L_main21:
;Svetofor.c,58 :: 		clear_lcd(); outcw(0x80); outd('З'); //outd('е'); outd('л');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #199
	LCALL _outd+0
;Svetofor.c,60 :: 		if (T_FLAG) { state=GG;  T_FLAG = 0;  t=3; }
	MOV A, _T_FLAG+0
	JZ L_main22
	MOV _state+0, #4
	MOV _T_FLAG+0, #0
	MOV _t+0, #3
	SJMP L_main23
L_main22:
;Svetofor.c,61 :: 		else if (key == '8') { state=SR;  GRN=1; }
	MOV A, _key+0
	XRL A, #56
	JNZ L_main24
	MOV _state+0, #6
	SETB P0_2_bit+0
L_main24:
L_main23:
;Svetofor.c,62 :: 		break;
	LJMP L_main12
;Svetofor.c,63 :: 		case GG: // Мигающий зеленый
L_main25:
;Svetofor.c,64 :: 		GRN=0; DelayMs(500);
	CLR P0_2_bit+0
	MOV FARG_DelayMs_m+0, #244
	MOV FARG_DelayMs_m+1, #1
	LCALL _DelayMs+0
;Svetofor.c,65 :: 		GRN=1; DelayMs(400);
	SETB P0_2_bit+0
	MOV FARG_DelayMs_m+0, #144
	MOV FARG_DelayMs_m+1, #1
	LCALL _DelayMs+0
;Svetofor.c,66 :: 		if (T_FLAG) { state=Y;  T_FLAG = 0;  t=20;  YEL=0; }
	MOV A, _T_FLAG+0
	JZ L_main26
	MOV _state+0, #5
	MOV _T_FLAG+0, #0
	MOV _t+0, #20
	CLR P0_1_bit+0
L_main26:
;Svetofor.c,67 :: 		break;
	LJMP L_main12
;Svetofor.c,68 :: 		case Y: // Желтый
L_main27:
;Svetofor.c,70 :: 		clear_lcd(); outcw(0x80); outd('Ж'); //outd('е'); outd('л');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #198
	LCALL _outd+0
;Svetofor.c,72 :: 		if (T_FLAG) { state=R;  T_FLAG = 0;  t=10*tr; YEL=1; RED=0; }
	MOV A, _T_FLAG+0
	JZ L_main28
	MOV _state+0, #1
	MOV _T_FLAG+0, #0
	MOV B+0, _tr+0
	MOV A, #10
	MUL AB
	MOV R0, A
	MOV _t+0, 0
	SETB P0_1_bit+0
	CLR P0_0_bit+0
	SJMP L_main29
L_main28:
;Svetofor.c,73 :: 		else if (key == '8') { state=SR;  YEL=1; }
	MOV A, _key+0
	XRL A, #56
	JNZ L_main30
	MOV _state+0, #6
	SETB P0_1_bit+0
L_main30:
L_main29:
;Svetofor.c,74 :: 		break;
	LJMP L_main12
;Svetofor.c,75 :: 		case SR: // Настройка времени красного сигнала
L_main31:
;Svetofor.c,77 :: 		clear_lcd(); outcw(0x80); outd('t'); outd('к'); outd('=');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #116
	LCALL _outd+0
	MOV FARG_outd_c+0, #234
	LCALL _outd+0
	MOV FARG_outd_c+0, #61
	LCALL _outd+0
;Svetofor.c,78 :: 		outd(tr/10+48); outd(tr%10+48); outd('c');
	MOV B+0, #10
	MOV A, _tr+0
	DIV AB
	MOV R0, A
	ADD A, #48
	MOV FARG_outd_c+0, A
	LCALL _outd+0
	MOV B+0, #10
	MOV A, _tr+0
	DIV AB
	MOV A, B+0
	MOV R0, A
	ADD A, #48
	MOV FARG_outd_c+0, A
	LCALL _outd+0
	MOV FARG_outd_c+0, #99
	LCALL _outd+0
;Svetofor.c,79 :: 		switch(key) {
	SJMP L_main32
;Svetofor.c,80 :: 		case '7': if (tr>5) tr--; break;
L_main34:
	SETB C
	MOV A, _tr+0
	SUBB A, #5
	JC L_main35
	DEC _tr+0
L_main35:
	SJMP L_main33
;Svetofor.c,81 :: 		case '9': if (tr<30) tr++; break;
L_main36:
	CLR C
	MOV A, _tr+0
	SUBB A, #30
	JNC L_main37
	INC _tr+0
L_main37:
	SJMP L_main33
;Svetofor.c,82 :: 		case '8': wr_EEPROM(0,tr); state=SG; break;
L_main38:
	MOV FARG_wr_EEPROM_addr+0, #0
	MOV FARG_wr_EEPROM_addr+1, #0
	MOV FARG_wr_EEPROM_eedata+0, _tr+0
	LCALL _wr_EEPROM+0
	MOV _state+0, #7
	SJMP L_main33
;Svetofor.c,83 :: 		}
L_main32:
	MOV A, _key+0
	XRL A, #55
	JZ L_main34
	MOV A, _key+0
	XRL A, #57
	JZ L_main36
	MOV A, _key+0
	XRL A, #56
	JZ L_main38
L_main33:
;Svetofor.c,84 :: 		break;
	LJMP L_main12
;Svetofor.c,85 :: 		case SG: // Настройка времени зеленого сигнала
L_main39:
;Svetofor.c,87 :: 		clear_lcd(); outcw(0x80); outd('t'); outd('з'); outd('=');
	LCALL _clear_lcd+0
	MOV FARG_outcw_c+0, #128
	LCALL _outcw+0
	MOV FARG_outd_c+0, #116
	LCALL _outd+0
	MOV FARG_outd_c+0, #231
	LCALL _outd+0
	MOV FARG_outd_c+0, #61
	LCALL _outd+0
;Svetofor.c,88 :: 		outd(tg/10+48); outd(tg%10+48); outd('c');
	MOV B+0, #10
	MOV A, _tg+0
	DIV AB
	MOV R0, A
	ADD A, #48
	MOV FARG_outd_c+0, A
	LCALL _outd+0
	MOV B+0, #10
	MOV A, _tg+0
	DIV AB
	MOV A, B+0
	MOV R0, A
	ADD A, #48
	MOV FARG_outd_c+0, A
	LCALL _outd+0
	MOV FARG_outd_c+0, #99
	LCALL _outd+0
;Svetofor.c,89 :: 		switch(key) {
	SJMP L_main40
;Svetofor.c,90 :: 		case '7': if (tg>5) tg--; break;
L_main42:
	SETB C
	MOV A, _tg+0
	SUBB A, #5
	JC L_main43
	DEC _tg+0
L_main43:
	SJMP L_main41
;Svetofor.c,91 :: 		case '9': if (tg<30) tg++; break;
L_main44:
	CLR C
	MOV A, _tg+0
	SUBB A, #30
	JNC L_main45
	INC _tg+0
L_main45:
	SJMP L_main41
;Svetofor.c,92 :: 		case '8': wr_EEPROM(1,tg); state=R; T_FLAG = 0; t=10*tr; RED=0; break;
L_main46:
	MOV FARG_wr_EEPROM_addr+0, #1
	MOV FARG_wr_EEPROM_addr+1, #0
	MOV FARG_wr_EEPROM_eedata+0, _tg+0
	LCALL _wr_EEPROM+0
	MOV _state+0, #1
	MOV _T_FLAG+0, #0
	MOV B+0, _tr+0
	MOV A, #10
	MUL AB
	MOV R0, A
	MOV _t+0, 0
	CLR P0_0_bit+0
	SJMP L_main41
;Svetofor.c,93 :: 		}
L_main40:
	MOV A, _key+0
	XRL A, #55
	JZ L_main42
	MOV A, _key+0
	XRL A, #57
	JZ L_main44
	MOV A, _key+0
	XRL A, #56
	JZ L_main46
L_main41:
;Svetofor.c,94 :: 		break;
	SJMP L_main12
;Svetofor.c,95 :: 		}
L_main11:
	MOV A, _state+0
	XRL A, #1
	JNZ #3
	LJMP L_main13
	MOV A, _state+0
	XRL A, #2
	JNZ #3
	LJMP L_main17
	MOV A, _state+0
	XRL A, #3
	JNZ #3
	LJMP L_main21
	MOV A, _state+0
	XRL A, #4
	JNZ #3
	LJMP L_main25
	MOV A, _state+0
	XRL A, #5
	JNZ #3
	LJMP L_main27
	MOV A, _state+0
	XRL A, #6
	JNZ #3
	LJMP L_main31
	MOV A, _state+0
	XRL A, #7
	JNZ #3
	LJMP L_main39
L_main12:
;Svetofor.c,96 :: 		DelayMs(100);            // такт работы автомата
	MOV FARG_DelayMs_m+0, #100
	MOV FARG_DelayMs_m+1, #0
	LCALL _DelayMs+0
;Svetofor.c,97 :: 		if(t==0) T_FLAG=1; else t--;  // счетчик
	MOV A, _t+0
	JNZ L_main47
	MOV _T_FLAG+0, #1
	SJMP L_main48
L_main47:
	DEC _t+0
L_main48:
;Svetofor.c,98 :: 		}
	LJMP L_main9
;Svetofor.c,99 :: 		}
	SJMP #254
; end of _main

_DelayMs:
;Svetofor.c,113 :: 		void DelayMs(unsigned int m){  // задержка по таймеру
;Svetofor.c,116 :: 		ms=0;
	MOV _ms+0, #0
	MOV _ms+1, #0
;Svetofor.c,117 :: 		WMCON.WDTRST=1; // сброс сторожевого таймера
	SETB C
	MOV A, WMCON+0
	MOV #224, C
	MOV WMCON+0, A
;Svetofor.c,118 :: 		while(ms!=m) continue;
L_DelayMs49:
	MOV A, _ms+0
	XRL A, FARG_DelayMs_m+0
	JNZ L__DelayMs53
	MOV A, _ms+1
	XRL A, FARG_DelayMs_m+1
L__DelayMs53:
	JZ L_DelayMs50
	SJMP L_DelayMs49
L_DelayMs50:
;Svetofor.c,119 :: 		}
	RET
; end of _DelayMs

_Timer1InterruptHandler:
	PUSH PSW+0
	PUSH 224
	PUSH B+0
	PUSH 130
	PUSH 131
;Svetofor.c,121 :: 		void Timer1InterruptHandler() org IVT_ADDR_ET1{
;Svetofor.c,123 :: 		EA_bit = 0;        // Clear global interrupt enable flag
	CLR EA_bit+0
;Svetofor.c,124 :: 		TF1_bit = 0;       // Ensure that Timer1 interrupt flag is cleared
	CLR TF1_bit+0
;Svetofor.c,126 :: 		TR1_bit = 0;       // Stop Timer1
	CLR TR1_bit+0
;Svetofor.c,127 :: 		TH1 = 0xFC;        // Reset Timer1 high byte  65536-1000
	MOV TH1+0, #252
;Svetofor.c,128 :: 		TL1 = 0x18;        // Reset Timer1 low byte
	MOV TL1+0, #24
;Svetofor.c,131 :: 		ms++;
	MOV A, #1
	ADD A, _ms+0
	MOV _ms+0, A
	MOV A, #0
	ADDC A, _ms+1
	MOV _ms+1, A
;Svetofor.c,133 :: 		EA_bit = 1;        // Set global interrupt enable flag
	SETB EA_bit+0
;Svetofor.c,134 :: 		TR1_bit = 1;       // Run Timer1
	SETB TR1_bit+0
;Svetofor.c,135 :: 		}
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
;Svetofor.c,137 :: 		void INT0_Interrupt() org IVT_ADDR_EX0 {
;Svetofor.c,138 :: 		EA_bit = 0;
	CLR EA_bit+0
;Svetofor.c,139 :: 		lcd_led=~lcd_led;
	MOV C, P0_4_bit+0
	CPL C
	MOV P0_4_bit+0, C
;Svetofor.c,140 :: 		EA_bit = 1;
	SETB EA_bit+0
;Svetofor.c,141 :: 		}
	POP 131
	POP 130
	POP B+0
	POP 224
	POP PSW+0
	RETI
; end of _INT0_Interrupt
