.model small
.data
	message db   'Symbol:  $'
.stack 256h
.code
main:
	mov ax,@data
	mov ds, ax
	lea dx,message
	mov ah,09h
	int 21h
               	mov ah,0
                int 16h
                mov ah,2
                mov dl,al
                int 21h
	mov ah,4ch
	int 21h
end main