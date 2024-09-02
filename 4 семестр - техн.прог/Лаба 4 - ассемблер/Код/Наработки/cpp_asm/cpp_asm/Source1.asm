.MODEL FLAT,C;
.CODE
sum proc mas:dword, n:ptr dword , num: dword
push esi ; mas
push edx ;n
push ecx ;num
push eax 

mov esi, dword ptr [ebp+8] ; mas 
mov ecx, dword ptr [ebp+16] ;num
mov edx, dword ptr [ebp+12] ;n
mov ebx, 1000
l1:
  mov eax, [esi]
  cmp eax, 0
  je l3
  cmp eax, ebx
  jle l2
  jge l3
l2:
  mov ebx, eax
  jmp l3
l3:
  mov [edx], ebx
  add esi, 4
  dec ecx
  cmp ecx, 0
  jne l1

pop eax
pop ecx
pop edx
pop esi

ret
sum endp
end