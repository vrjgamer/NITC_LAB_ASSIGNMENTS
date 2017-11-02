section .data
mes1: db "Input Floating Point Number :", 0Ah
len1: equ $-mes1

mes2: db "Sum :", 0Ah
len2: equ $-mes2

mes3: db "Difference :", 0Ah
len3: equ $-mes3

mes4: db "Product :", 0Ah
len4: equ $-mes4

Type1: db "%lf", 0
Type2: db "%lf", 10

section .bss
num: resw 1
float3: resq 1
float1: resq 1
float2: resq 1
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

fstp qword[float1]

mov eax, 4
mov ebx, 1
mov ecx, mes1
mov edx, len1
int 80h

call read_float

fstp qword[float2]

fld qword[float2]
fld qword[float1]
fadd ST1              

mov eax, 4
mov ebx, 1
mov ecx, mes2
mov edx, len2
int 80h

call print_float
ffree ST0
ffree ST1

fld qword[float2]
fld qword[float1]
fsub ST1
mov eax, 4
mov ebx, 1
mov ecx, mes3
mov edx, len3
int 80h
call print_float
ffree ST0
ffree ST1

fld qword[float2]
fld qword[float1]
fmul ST1
mov eax, 4
mov ebx, 1
mov ecx, mes4
mov edx, len4
int 80h
call print_float
ffree ST0
ffree ST1

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
