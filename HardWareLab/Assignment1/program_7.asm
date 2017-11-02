
 global _start:
   _start:

   mov eax,4              
   mov ebx,1
   mov ecx,msg1
   mov edx,len1
   int 80h

   mov dword[number1], 0      
   mov dword[number2], 0

 loop_read1:
    mov eax, 3                
    mov ebx, 0
    mov ecx, temp
    mov edx, 1
    int 80h

    cmp byte[temp], 10      
    je print2

    mov eax, dword[number1]
    mov ebx, 10
    mul ebx                 
    movzx ebx, byte[temp]   ;;ebx=temp
    sub ebx, 30h            ;;make ebx an int
    add eax, ebx            ;eax=eax+temp
    mov dword[number1], eax
    jmp loop_read1

print2:
   mov eax,4            ;;Ask for second number
   mov ebx,1
   mov ecx,msg2
   mov edx,len2
   int 80h


 loop_read2:
    mov eax, 3
    mov ebx, 0
    mov ecx, temp
    mov edx, 1
    int 80h

    cmp byte[temp], 10
    je add

    mov eax, dword[number2]
    mov ebx, 10
    mul ebx
    movzx ebx, byte[temp]
    sub ebx, 30h
    add eax, ebx
    mov dword[number2], eax
    jmp loop_read2

 add:
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,len3
    int 80h

    mov eax, dword[number1]
    mov ebx, dword[number2]
    add eax, ebx
    mov dword[sum], eax

    mov eax, dword[sum]

   extract_no:
    cmp dword[sum], 0
    je print_no
    inc byte[nod]
    mov edx, 0
    mov eax, dword[sum]
    mov ebx, 10
    div ebx
    push edx
    mov dword[sum], eax
    jmp extract_no

  print_no:
    cmp byte[nod], 0
    je exit
    dec byte[nod]
    pop edx
    mov byte[temp], dl
    add byte[temp], 30h


    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 1
    int 80h

    jmp print_no


    exit:
 mov eax,1
 mov ebx,0
 int 80h

 section .data
  msg1: db "Enter first number",0Ah
  len1: equ $-msg1
  msg2: db "Enter second number",0Ah
  len2: equ $-msg2
  msg3: db "Sum of the numbers", 0Ah
  len3: equ $-msg3


 section .bss
  number1: resd 1
  number2: resd 1
  sum: resd 1
  temp: resb 1
  nod: resb 1
