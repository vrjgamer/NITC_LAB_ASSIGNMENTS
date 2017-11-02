section .data
mes1: db "Radius :", 0Ah
len1: equ $-mes1

mes2: db "Perimeter :", 0Ah
len2: equ $-mes2

mes10: db "Invalid Input ",0Ah
len10: equ $-mes10

Type1: db "%lf", 0
Type2: db "%lf", 10

section .bss
num: resd 1
rad: resq 1
peri: resq 1
tmp: resb 1

section .text
global main:
extern scanf
extern printf

main:

mov eax, 4
mov ebx, 1
mov ecx, mes1
mov edx, len1
int 80h

call read_float

fst qword[rad]

fldz 
fcomp qword[rad]

fstsw ax
sahf

ja label
jmp continue


label:
mov eax,4
mov ebx,1
mov ecx,mes10
mov edx,len10
int 80h
jmp EXIT

continue:
fst qword[peri]

mov dword[num], 44
fimul dword[num]
mov dword[num], 7
fidiv dword[num]

mov eax, 4
mov ebx, 1
mov ecx, mes2
mov edx, len2
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
