section .data
msg1: db "Enter A :", 0Ah
len1: equ $-msg1

msg2: db "Enter B :", 0Ah
len2: equ $-msg2

msg3: db "Enter C :", 0Ah
len3: equ $-msg3

msg4: db "Root1 :", 0Ah
len4: equ $-msg4

msg5: db "Root2 :", 0Ah
len5: equ $-msg5

msg6: db "Imaginary ", 0Ah
len6: equ $-msg6

Type1: db "%lf", 0
Type2: db "%lf", 10

section .bss
num: resd 1
a: resq 1
b: resq 1
c: resq 1
root1: resq 1
root2: resq 1
temp1: resq 1
temp2: resq 1
tmp: resb 1

section .text
global main:
extern scanf
extern printf

main:

mov eax, 4
mov ebx, 1
mov ecx, msg1
mov edx, len1
int 80h

call read_float

fstp qword[a]

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

call read_float

fstp qword[b]

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h

call read_float

fstp qword[c]

fld qword[b]
fmul ST0				

fstp qword[temp1]

fld qword[a]
fld qword[c]

mov dword[num], 4
fimul dword[num]

fmul ST1

fld qword[temp1]
fsub ST1

fstp qword[temp1]
ffree ST0
ffree ST1

fldz 
fcomp qword[temp1]

fstsw ax
sahf

jna continue

mov eax, 4
mov ebx, 1
mov ecx, msg6
mov edx, len6
int 80h

jmp EXIT

continue:

fld qword[temp1]
fsqrt

fstp qword[temp1]

fld qword[b] 
fchs

fld qword[temp1]   
fadd ST1

mov dword[num], 2
fidiv dword[num]

fdiv qword[a]

fstp qword[root1]
ffree ST0

fld qword[b]       
fchs

fld qword[temp1]  
fchs
fadd ST1

mov dword[num], 2
fidiv dword[num]

fdiv qword[a]

fstp qword[root2]
ffree ST0

fld qword[root1]

mov eax, 4
mov ebx, 1
mov ecx, msg4
mov edx, len4
int 80h

call print_float

fld qword[root2]

mov eax, 4
mov ebx, 1
mov ecx, msg5
mov edx, len5
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
