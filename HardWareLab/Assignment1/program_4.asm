section .data
minus: db "-"
msg1: db "Please enter the no of elements in the array"
msg1_len: equ $-msg1
msg2: db "The Elements of the Array are:"
msg2_len: equ $-msg2
msg3: db "Element         No of Occurences"
msg3_len: equ $-msg3
msg4: db "The modes are:"
msg4_len: equ $-msg4
newline: db " ",0Ah
space: db "                   "
occ: TIMES 100 db 0
small_space: db "  "
section .bss
    num: resw 1
    nod : resb 1
    temp: resb 1
    sign: resb 1
    array: resw 100
    noe:  resb 1
    modes: resw 100
    nom: resb 1
    max_freq:resb 1
    
  section .txt
 global _start
 
 _start:
 mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1_len
    int 80h
     
   call read_num
   mov ax,word[num]
   mov byte[noe],al
   
   mov ecx,0
   mov cl,byte[noe]
   mov edi,array
   cld
   
   input:
   call read_num
   mov ax,word[num]
   STOSW
   loop input
   
   call print_newline
   
   
    mov ecx,0
    mov ebx,occ
   mov cl,byte[noe]
   mov esi,array
   cld
    
    update:
    LODSW
    movzx edx,ax
    add edx,ebx
    inc byte[edx]
    loop update
    
    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, msg3_len
    int 80h
    
    call print_newline
    
    mov ecx,0
    mov edx,0
    mov eax,0
   mov cl,100
   mov edx,modes
   mov ebx,occ
   mov byte[noe],0
   mov byte[nom],0
    mov byte[max_freq],0
   cld
 
 
  output:
    cmp byte[ebx],0
    jne occurence
    jmp increment
    
    occurence:
     movzx ax,byte[noe]
     mov word[num],ax
     call print_num
     call print_space
     movzx ax,byte[ebx]
     mov word[num],ax
     call print_num
     call print_newline
     cmp al,byte[max_freq]
     ja reset
     je add_another
     jmp increment
     
     reset:
     mov byte[max_freq],al
     mov edx,modes
     mov byte[nom],1
     movzx ax,byte[noe]
     mov word[edx],ax
     add edx,2
     jmp increment
     
     add_another:
     movzx ax,byte[noe]
     mov word[edx],ax
     add edx,2
     inc byte[nom]
     
     
 increment:    
     inc byte[noe]
     inc ebx
     cmp byte[noe],100
     jl output
     
    
     
     mov eax,4
   mov ebx, 1
    mov ecx, msg4
    mov edx, msg4_len
    int 80h
    call print_small
    mov eax,0
    mov ebx,0
    mov edx,0
    mov ecx,0
   mov cl,byte[nom]
   mov edx,modes
   cld
    
    output_modes:
    mov ax,word[edx]
    mov word[num],ax
    call print_num
    call print_small
    add edx,2
   loop output_modes
  
     
    
    
   call print_newline
   jmp exit 
   
   
     



read_num:

  pusha
  mov word[num], 0
  mov eax,0
  mov byte[sign],0
  read:
    mov eax, 3
    mov ebx, 0
    mov ecx, temp
    mov edx, 1
    int 80h
    
    cmp word[num],0
     jne cont
     cmp byte[temp],2dh
     je sign_detect


    
   cont:
     cmp byte[temp], 10
      je end
      
      cmp byte[temp],32
      je end
    
    mov ax, word[num]
    mov bx, 10
    mul bx
    mov bl, byte[temp]
    sub bl, 30h
    mov bh, 0
    add ax, bx
    mov word[num], ax
    jmp read 
   sign_detect:
   mov byte[sign],1
   jmp read
  end:
  cmp byte[sign],1
  je sign_inv
  popa
  ret
  sign_inv:
  mov ax,word[num]
  mov bx,-1
  mul bx
  mov word[num],ax
  popa
  ret




print_num:
  pusha
  cmp word[num],0
  jl negative
  je zero
  resume: mov byte[nod],0
  extract_no:
    cmp word[num], 0
    je print_no
    inc byte[nod]
    mov edx, 0
    mov ebx,0
    mov ax, word[num]
    mov bx, 10
    div bx
    push dx
    mov word[num], ax
  jmp extract_no


  print_no:
    
    cmp byte[nod], 0
    je end_print
    dec byte[nod]
    pop dx
    mov byte[temp],dl
    add byte[temp], 30h


    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 1
    int 80h
    
    jmp print_no
    
negative:
 call sign_invert
 jmp resume
 
 zero:
 mov byte[temp],30h
    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 1
    int 80h
 
 
  end_print:   
  popa
  ret 
 sign_invert:
  pusha
   mov eax, 4
    mov ebx, 1
    mov ecx, minus
    mov edx, 1
    int 80h
  mov ax,word[num]
  mov bx,-1
  mul bx
  mov word[num],ax
  popa
  ret
  
  print_newline:
  pusha
  mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 2
    int 80h
  popa 
  ret
  print_space:
  pusha
  mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 19
    int 80h
  popa 
  ret
  print_small:
  pusha
  mov eax, 4
    mov ebx, 1
    mov ecx, small_space
    mov edx, 2
    int 80h
  popa 
  ret

exit:       mov eax, 1
            mov ebx, 0
            int 80h
