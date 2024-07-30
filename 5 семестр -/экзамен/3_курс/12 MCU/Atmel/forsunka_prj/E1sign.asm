.include "tn2313def.inc"

.def mode       = R16
.def sel        = R17
.def en         = R18
.def v0         = R19
.def v1         = R20
.def v2         = R21
.def v3         = R22
.def v4         = R23
.def icnt       = R24


.equ KOut 		= 6
.equ Led0 		= 0
.equ Led1 		= 2
.equ Led2 		= 5
.equ Btn0 		= 1
.equ Btn1 		= 0
.equ Btn2 		= 4

;-------------------------------------------------------------------
;-------------   Hardware Definition   -----------------------------
;-------------------------------------------------------------------
;	Timer0 config
.equ	T0prsclr	= 0b00000100
.equ	T0intcntc	= 0x01
;-------------------------------------------------------------------

		.CSEG
		.org $0000
		rjmp	main

		.org OVF0addr
		rjmp	int_t0ovf		;Timer0 overflow  interrupt  handler
		
	
;---------------------------------------------------------------------
	
	.org	$0080
		
main:
			
		sbi     DDRD,Led0		;
		cbi     PORTD,Led0		; Led Output

		sbi     DDRD,Led1		;
		cbi     PORTD,Led1		; Led Output

		sbi     DDRD,Led2		;
		cbi     PORTD,Led2		; Led Output

		sbi     DDRD,KOut		;
		sbi     PORTD,Kout		; K output


		cbi     DDRD,Btn0		;
		sbi     PORTD,Btn0		; Button in

		cbi     DDRA,Btn1		;
		sbi     PORTA,Btn1		; Button in

		cbi     DDRD,Btn2		;
		sbi     PORTD,Btn2		; Button in



		ldi     v0,0x00	; Init Timer
		out		TCCR0A,v0 ;
		ldi     v0,0x04   ; div = 256
		out     TCCR0B,v0 ;

		ldi     mode,0x02	; Init INT Mask
		out     TIMSK,mode	;	

		ldi     mode,0x00
		ldi     sel,0x00
		ldi     en,0x00
		ldi     icnt,80

		ldi     v0,0x00
		ldi     v1,0x00
		ldi     v2,0x00

		sei
		
loop:

		cpi     mode, 0x00
		breq	led0set
		cbi		PORTD,Led0
		rjmp    nxt_led2
led0set:sbi		PORTD,Led0


nxt_led2:
		cpi     en,0x00
		breq	led2set
		cbi		PORTD,Led2
		rjmp    nxt_led1
led2set:sbi		PORTD,Led2


nxt_led1:
		rcall   blink_led
	
loop_end:

		rjmp    loop
			
;-------------------------------------------------------------------
blink_led:
		mov v0,sel
		cpi v0,0x04
		breq set_led
		inc v0

led_loop:
		sbi PORTD,Led1
		rcall time
		cbi PORTD,Led1
		rcall time

		dec v0
		cpi v0,0x00
		breq blink_end
		rjmp led_loop

set_led:sbi PORTD,Led1

blink_end:
		rcall time
		rcall time
		rcall time
		rcall time
		rcall time
		rcall time
		
		ret
;-------------------------------------------------------------------
time:	ldi 	v3, $02
		ldi 	v4, $ff
tt:		dec 	v3
		nop
		nop
		nop
		brne 	tt
		dec 	v4
		brne 	tt
		ret
		ret
;-------------------------------------------------------------------
;-------------------------------------------------------------------
;-------------------------------------------------------------------	
;-------------------------------------------------------------------
int_t0ovf:
		cli

; impulse forming:
		cpi icnt,79
		breq imp_start
		cpi icnt,59
		breq imp_end		


imp_start:
        cbi PORTD,KOut		; start front
		
  						    ; testing buttons
		cpi v1,0x00
		breq continue2
		dec v1
		rjmp continue1:
continue2:
		
		sbic PORTD,Btn0
		rjmp nxt_btn0
		inc mode
		cpi mode,0x02
		brne nxt_btn0
		ldi mode,0x00
		ldi v1, 0x0b
nxt_btn0:

		sbic PORTA,Btn1
		rjmp nxt_btn1
		inc sel
		cpi sel,0x05
		brne nxt_btn1
		ldi sel,0x00
		ldi v1, 0x0b

nxt_btn1:

		sbic PORTD,Btn2
		rjmp nxt_btn2
		inc en
		cpi en,0x02
		brne nxt_btn2
		ldi en,0x00
		ldi v1, 0x0b
nxt_btn2:
imp_end:
        sbi PORTD,KOut

continue1:
int_end:
		reti
;-------------------------------------------------------------------
		
int_end0:
		cbi		PORTB,2
		reti
;-------------------------------------------------------------------
