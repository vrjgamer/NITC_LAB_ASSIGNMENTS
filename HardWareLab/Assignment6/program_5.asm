section .data
msg1: db "Enter x :", 0Ah
len1: equ $-msg1

msg2: db "Enter n :", 0Ah
len2: equ $-msg2

msg3: db "Sum :", 0Ah
len3: equ $-msg3

msg4: db "Cos(x) :", 0Ah
len4: equ $-msg4

Type1: db "%lf", 0
Type2: db "%lf", 10

section .bss
num: resw 1
a: resd 1
x: resq 1
n: resw 1
f: resq 1
sum: resq 1
temp: resb 1

section .text
global main:
extern scanf
extern printf

main:

;;Enter x
mov eax, 4
mov ebx, 1
mov ecx, msg1
mov edx, len1
int 80h

call read_float

fstp qword[x]

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

call read_num

mov ax, word[num]
mov word[n], ax 

cmp word[n], 0
je EXIT

call cosx

fld qword[sum]

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

call print_float

ffree ST0
fld qword[x]

fcos

mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h

call print_float

EXIT:
mov eax, 1
mov ebx, 0
int 80h   


read_float:
push ebp
mov ebp, esp
sub esp, 8

lea eax, [esp]
push eax
push Type1
call scanf
fld qword[ebp - 8]

mov esp, ebp
pop ebp
ret


print_float:
push ebp
mov ebp, esp
sub esp, 8

fst qword[ebp - 8]
push Type2
call printf
mov esp, ebp
pop ebp
ret


]
cosx:

mov dword[a],1
fild dword[a]
fst qword[sum]
fstp qword[f]

mov esi, 1   
mov dword[a], esi  

loop1:

cmp si, word[n]
je end_loop1

fld qword[f]
fmul qword[x]
fmul qword[x]
fidiv dword[a]
inc dword[a]
fidiv dword[a]
fchs

fst qword[f]

fld qword[sum]

fadd ST1

fstp qword[sum]
ffree ST0

inc dword[a]
inc esi

jmp loop1

end_loop1:
ret


read_num:
pusha

mov word[num], 0
mov byte[temp], 0

loop_read:
mov eax, 3
mov ebx, 0
mov ecx, temp
mov edx, 1
int 80h

cmp byte[temp], 10  
je end_read

mov ax, word[num]
mov bx, 10
mul bx
mov bl, byte[temp]
sub bl, 30h
mov bh, 0
add ax, bx
mov word[num], ax
jmp loop_read

end_read:
popa
ret
