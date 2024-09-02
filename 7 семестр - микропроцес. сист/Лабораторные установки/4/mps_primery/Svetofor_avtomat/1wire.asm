
_read_OW:
;1wire.c,12 :: 		unsigned char read_OW (void)
;1wire.c,14 :: 		unsigned char read_data=0;
	MOV read_OW_read_data_L0+0, #0
;1wire.c,16 :: 		WIRE1_PIN = 1;
	SETB P1_4_bit+0
;1wire.c,18 :: 		if (WIRE1_PIN==1)
	JNB P1_4_bit+0, L_read_OW0
	NOP
;1wire.c,19 :: 		read_data = 1;
	MOV read_OW_read_data_L0+0, #1
	SJMP L_read_OW1
L_read_OW0:
;1wire.c,21 :: 		read_data = 0;
	MOV read_OW_read_data_L0+0, #0
L_read_OW1:
;1wire.c,23 :: 		return read_data;
	MOV R0, read_OW_read_data_L0+0
;1wire.c,24 :: 		}
	RET
; end of _read_OW

_OW_reset_pulse:
;1wire.c,35 :: 		unsigned char OW_reset_pulse(void)
;1wire.c,40 :: 		WIRE1_PIN=0;                                 // Drive the bus low
	CLR P1_4_bit+0
;1wire.c,42 :: 		Delay_us(240);                                  // delay 480 microsecond (us)
	MOV R7, 119
	DJNZ R7, 
	NOP
;1wire.c,43 :: 		Delay_us(240);
	MOV R7, 119
	DJNZ R7, 
	NOP
;1wire.c,45 :: 		WIRE1_PIN=1;                                   // Release the bus
	SETB P1_4_bit+0
;1wire.c,47 :: 		Delay_us(70);                                // delay 70 microsecond (us)
	MOV R7, 34
	DJNZ R7, 
	NOP
;1wire.c,49 :: 		presence_detect = read_OW();        //Sample for presence pulse from slave
	LCALL _read_OW+0
	MOV OW_reset_pulse_presence_detect_L0+0, 0
;1wire.c,51 :: 		Delay_us(205);                                  // delay 410 microsecond (us)
	MOV R7, 102
	DJNZ R7, 
;1wire.c,52 :: 		Delay_us(205);
	MOV R7, 102
	DJNZ R7, 
;1wire.c,54 :: 		WIRE1_PIN=1;                            // Release the bus
	SETB P1_4_bit+0
;1wire.c,56 :: 		return presence_detect;
	MOV R0, OW_reset_pulse_presence_detect_L0+0
;1wire.c,57 :: 		}
	RET
; end of _OW_reset_pulse

_OW_write_bit:
;1wire.c,67 :: 		void OW_write_bit (unsigned char write_bit)
;1wire.c,69 :: 		if (write_bit)
	MOV A, FARG_OW_write_bit_write_bit+0
	JZ L_OW_write_bit2
;1wire.c,72 :: 		WIRE1_PIN=0;                                 // Drive the bus low
	CLR P1_4_bit+0
;1wire.c,73 :: 		Delay_us(6);                                // delay 6 microsecond (us)
	MOV R7, 2
	DJNZ R7, 
	NOP
;1wire.c,74 :: 		WIRE1_PIN=1;                                  // Release the bus
	SETB P1_4_bit+0
;1wire.c,75 :: 		Delay_us(6);                                // delay 64 microsecond (us)
	MOV R7, 2
	DJNZ R7, 
	NOP
;1wire.c,76 :: 		}
	SJMP L_OW_write_bit3
L_OW_write_bit2:
;1wire.c,80 :: 		WIRE1_PIN=0;                                 // Drive the bus low
	CLR P1_4_bit+0
;1wire.c,81 :: 		Delay_us(60);                                // delay 60 microsecond (us)
	MOV R7, 29
	DJNZ R7, 
	NOP
;1wire.c,82 :: 		WIRE1_PIN=1;                                  // Release the bus
	SETB P1_4_bit+0
;1wire.c,83 :: 		Delay_us(10);                                // delay 10 microsecond for recovery (us)
	MOV R7, 4
	DJNZ R7, 
	NOP
;1wire.c,84 :: 		}
L_OW_write_bit3:
;1wire.c,85 :: 		}
	RET
; end of _OW_write_bit

_OW_read_bit:
;1wire.c,96 :: 		unsigned char OW_read_bit (void)
;1wire.c,100 :: 		WIRE1_PIN=0;                                                 // Drive the bus low
	CLR P1_4_bit+0
;1wire.c,101 :: 		Delay_us(6);                                                // delay 6 microsecond (us)
	MOV R7, 2
	DJNZ R7, 
	NOP
;1wire.c,102 :: 		WIRE1_PIN=1;                                                  // Release the bus
	SETB P1_4_bit+0
;1wire.c,103 :: 		Delay_us(9);                                                // delay 9 microsecond (us)
	MOV R7, 4
	DJNZ R7, 
;1wire.c,105 :: 		read_data = read_OW();                                       //Read the status of OW_PIN
	LCALL _read_OW+0
	MOV OW_read_bit_read_data_L0+0, 0
;1wire.c,107 :: 		Delay_us(55);                                                // delay 55 microsecond (us)
	MOV R7, 27
	DJNZ R7, 
;1wire.c,108 :: 		return read_data;
	MOV R0, OW_read_bit_read_data_L0+0
;1wire.c,109 :: 		}
	RET
; end of _OW_read_bit

_OW_write_byte:
;1wire.c,119 :: 		void OW_write_byte (unsigned char write_data)
;1wire.c,123 :: 		for (loop = 0; loop < 8; loop++)
	MOV OW_write_byte_loop_L0+0, #0
L_OW_write_byte4:
	CLR C
	MOV A, OW_write_byte_loop_L0+0
	SUBB A, #8
	JNC L_OW_write_byte5
;1wire.c,125 :: 		OW_write_bit(write_data & 0x01);         //Sending LS-bit first
	MOV A, FARG_OW_write_byte_write_data+0
	ANL A, #1
	MOV FARG_OW_write_bit_write_bit+0, A
	LCALL _OW_write_bit+0
;1wire.c,126 :: 		write_data >>= 1;                                        // shift the data byte for the next bit to send
	MOV R0, #1
	MOV A, FARG_OW_write_byte_write_data+0
	INC R0
	SJMP L__OW_write_byte11
L__OW_write_byte12:
	CLR C
	RRC A
L__OW_write_byte11:
	DJNZ R0, L__OW_write_byte12
	MOV FARG_OW_write_byte_write_data+0, A
;1wire.c,123 :: 		for (loop = 0; loop < 8; loop++)
	INC OW_write_byte_loop_L0+0
;1wire.c,127 :: 		}
	SJMP L_OW_write_byte4
L_OW_write_byte5:
;1wire.c,128 :: 		}
	RET
; end of _OW_write_byte

_OW_read_byte:
;1wire.c,138 :: 		unsigned char OW_read_byte (void)
;1wire.c,140 :: 		unsigned char loop, result=0;
	MOV OW_read_byte_result_L0+0, #0
;1wire.c,142 :: 		for (loop = 0; loop < 8; loop++)
	MOV OW_read_byte_loop_L0+0, #0
L_OW_read_byte7:
	CLR C
	MOV A, OW_read_byte_loop_L0+0
	SUBB A, #8
	JNC L_OW_read_byte8
;1wire.c,145 :: 		result >>= 1;                                 // shift the result to get it ready for the next bit to receive
	MOV R0, #1
	MOV A, OW_read_byte_result_L0+0
	INC R0
	SJMP L__OW_read_byte13
L__OW_read_byte14:
	CLR C
	RRC A
L__OW_read_byte13:
	DJNZ R0, L__OW_read_byte14
	MOV OW_read_byte_result_L0+0, A
;1wire.c,146 :: 		if (OW_read_bit())
	LCALL _OW_read_bit+0
	MOV A, R0
	JZ L_OW_read_byte10
;1wire.c,147 :: 		result |= 0x80;                                // if result is one, then set MS-bit
	ORL OW_read_byte_result_L0+0, #128
L_OW_read_byte10:
;1wire.c,142 :: 		for (loop = 0; loop < 8; loop++)
	INC OW_read_byte_loop_L0+0
;1wire.c,148 :: 		}
	SJMP L_OW_read_byte7
L_OW_read_byte8:
;1wire.c,149 :: 		return result;
	MOV R0, OW_read_byte_result_L0+0
;1wire.c,150 :: 		}
	RET
; end of _OW_read_byte
