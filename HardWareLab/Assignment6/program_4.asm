section .data
msg1: db "Input Number Count :", 0Ah
len1: equ $-msg1

msg2: db "Array :", 0Ah
len2: equ $-msg2

msg3: db "Sorted Array :", 0Ah
len3: equ $-msg3

Type1: db "%lf", 0
Type2: db "%lf", 10

section .bss
array: resq 100
num: resw 1
array_length: resw 1
temp: resb 1

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

call read_num

cmp word[num], 0
je EXIT

mov ax, word[num]
mov word[array_length], ax

mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, len2
int 80h

call take_array_input

mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, len3
int 80h


call bubble_sort


call print_array

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
pusha
push ebp
mov ebp, esp
sub esp, 8

fst qword[ebp - 8]
push Type2
call printf
mov esp, ebp
pop ebp
popa
ret



take_array_input:
pusha
mov esi, 0

taking:

cmp si, word[array_length]
je end_taking  

call read_float 

fstp qword[array + esi*8]

inc esi

jmp taking
end_taking:
popa
ret



print_array:
pusha
mov esi, 0
printing:

cmp si, word[array_length]
je end_printing  

fld qword[array + esi*8]

call print_float 

ffree ST0

inc esi

jmp printing
end_printing:
popa
ret



bubble_sort:
pusha
mov edi, 0

loop1:

mov esi, 0
movzx eax, word[array_length]
sub eax, edi
sub eax, 1

loop2:
push eax

fld qword[array + 8*esi]

fld qword[array + 8*esi + 8]

fcom ST1

fstsw ax
sahf

jb swap
jmp cont1

swap:

fstp qword[array + 8*esi]
fstp qword[array + 8*esi + 8]

jmp cont

cont1:
ffree ST0
ffree ST1

cont:
pop eax
add esi, 1
cmp esi, eax
jl loop2


add edi, 1
movzx eax, word[array_length] 
cmp edi, eax
jl loop1 

popa
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
