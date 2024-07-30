; Птахова Анастсасия ИВТб-3301;;;
; Вариант 38

; Задание: Ввести строку символов. Сформировать новую строку,
; в которой символы разделены пробелами. Вывести обе строки строки
; на экран в режиме телетайпа с использованием атрибутов цвета
; 


.model small
.data
	message0 db  'String: $'
	message1 db  0Ah, 0Dh, 'Begin: $'
	message2 db  0Ah, 0Dh, 'Result: $'
	FullData STRUC
		one db 11 dup(0) ; name type count init
		two db 11 dup(0)
	FullData ENDS
	FD FullData 1 dup(<>)
.stack 256h
.code

GETSTRING proc near ; string will be written to [bx]
	push cx
	push dx

	mov cx, 0Ah ; string length
	mov dx, 01h ; break after Enter

getstring_loop:
	call GETCHAR ; get next char
	cmp byte ptr [bx], 0Dh ; test if char is Enter
	je getstring_quit
	inc bx
	loop getstring_loop

getstring_quit:
	pop dx
	pop cx
	ret
GETSTRING endp

GETCHAR proc near ; char will be written to [bx]
	push ax
	push dx

getchar_begin:
	mov ah, 08h
	int 21h     ; read char
	cmp al, 00h ; test if char is functional
	jne getchar_obtain_char

	mov ah, 08h
	int 21h
	jmp getchar_begin

getchar_obtain_char:
	cmp dx, 01h
	jne getchar_test_control
	cmp al, 0Dh ; test if char is Enter
	je getchar_write_char

getchar_test_control:
	cmp al, 31 ; test if char is control
	jle getchar_begin

getchar_write_char:
	mov [bx], al
	mov dl, al ; write symbol to stdout
	mov ah, 02h
	int 21h

	pop dx
	pop ax
	ret
GETCHAR endp

MESSAGE proc near ; data located in dx
	push ax
	push cx

	mov ah, 09h ; write string to stdout
	
	int 21h
	

	pop cx
	pop ax
	ret
MESSAGE endp

main:
	mov ax, @data
	mov ds, ax    ; load data segment
	mov es, ax
    
	lea dx, message0
	call MESSAGE

	lea bx, FD.one
	call GETSTRING

    
    mov cx, 0Ah
	mov al, 32
	lea si, FD.one
	lea di, FD.two
	
loop3_begin:
	
	
	mov ah, [si]
	mov byte ptr [di], ah
	inc di
	mov [di], al
	inc di
	inc si
	loop loop3_begin
	
	lea di, FD.two
	lea dx, message2
	call MESSAGE
	
	
	mov a6, 13h
	mov al, 1
	lea bp, FD.two
	mov bl, 3
    mov cx, 0Ah
    int 10h

   
	
	inc dh
	
	mov ah, 13h
	mov al, 1
	lea bp, FD.one 
	mov bl, 5
    mov cx, 0Ah
	
	
    int 10h


	
	mov ax, 4c00h
	int 21h
end main
