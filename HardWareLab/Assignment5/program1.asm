section .data
msg1:db "String :",0Ah
len1:equ $-msg1
msg2:db "Sorted String :",0Ah
len2:equ $-msg2
newline:db "",0Ah
space:db " "

section .bss
size:resw 1
string:resb 200
iter:resw 1
iter1:resw 1
array:resw 10
char:resb 1
num1:resw 1
num2:resw 1
flag:resb 1

section .text
global _start:
_start:


mov eax,4
mov ebx,1
mov ecx,msg1
mov edx,len1
int 80h

cld
mov ebx,0
mov word[size],0
loop1:
mov edi,string
add edi,ebx
loop2:
call read_char
mov al,byte[char]
cmp al,' '
je loop1end
cmp al,10
je funct
stosb 
jmp loop2
loop1end:
mov byte[edi],0
inc word[size]
add ebx,20
jmp loop1


funct:
mov byte[edi],0
inc word[size]
mov word[iter],0
mov ebx,array
loop5:
mov ax,word[size]
cmp ax,word[iter]
je sort
mov ax,word[iter]
mov word[ebx],ax
add ebx,2
inc word[iter]
jmp loop5   

sort:
mov ebx,array
mov word[iter],0
loop6:
mov ax,word[size]
cmp word[iter],ax
je print
mov ecx,ebx
add ecx,2
mov ax,word[iter]
inc ax
mov word[iter1],ax
loop7:
mov ax,word[size]
cmp ax,word[iter1]
je loop6end
mov ax,word[ebx]
mov word[num1],ax
mov ax,word[ecx]
mov word[num2],ax
call check
cmp byte[flag],0
je loop7end
mov ax,word[ebx]
mov dx,word[ecx]
mov word[ebx],dx
mov word[ecx],ax
loop7end:
inc word[iter1]
add ecx,2
jmp loop7
loop6end:
inc word[iter]
add ebx,2
jmp loop6
 





print:
mov eax,4
mov ebx,1
mov ecx,msg2
mov edx,len2
int 80h
cld
mov ebx,array

mov word[iter],0
loop3:
mov ax,word[size]
cmp word[iter],ax
je exit
mov esi,string
mov dx,0
mov ax,word[ebx]
mov cx,20
mul cx
movzx ecx,ax
;movzx ecx ,ax
add esi,ecx
loop4:
lodsb 
cmp al,0
je loop3end
mov byte[char],al
call print_char
jmp loop4
loop3end:
call print_space
inc word[iter]
add ebx,2
jmp loop3

exit:

call print_newline

mov eax,1
mov ebx,0
int 80h

print_newline:
pusha
mov eax,4
mov ebx,1
mov ecx,newline
mov edx,1
int 80h
popa
ret

print_space:
pusha
mov eax,4
mov ebx,1
mov ecx,space
mov edx,1
int 80h
popa
ret


print_char:
pusha
mov eax,4
mov ebx,1
mov ecx,char
mov edx,1
int 80h
popa
ret

read_char:
pusha
mov eax,3
mov ebx,0
mov ecx,char
mov edx,1
int 80h
popa
ret


check:
pusha
mov ax,word[num1]
mov bx,20
mul bx
movzx ebx,ax
mov ecx,string
add ecx,ebx
mov ax,word[num2]
mov bx,20
mul bx
movzx ebx,ax
mov edx,string
add edx,ebx
mov byte[flag],0
loop_cmp:
mov al,byte[ecx]
cmp al,0
je check_end
mov al,byte[edx]
cmp al,0
jne label1
mov byte[flag],1
jmp check_end
label1:
mov al,byte[ecx]
cmp al,byte[edx]
je label2
cmp al,byte[edx]
jb check_end
mov byte[flag],1
jmp check_end
label2:
inc ecx
inc edx
jmp loop_cmp
check_end:
popa
ret 			




