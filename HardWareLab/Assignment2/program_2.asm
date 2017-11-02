section .data
  msgnum1 db "Enter a number: ", 0Ah
  lenmsgnum1 equ $-msgnum1
  
  msgnum2 db "Enter another number: ", 0Ah
  lenmsgnum2 equ $-msgnum2
  
  msgoverflow db "The number is too large.", 0Ah
  lenmsgoverflow equ $-msgoverflow
  
  msgresult db "The result is: ", 0Ah
  lenmsgresult equ $-msgresult
  
section .bss
  number1: resw 1
  number2: resw 1
  digit: resb 1
  strnum: resb 10
  counter: resb 1
  
section .text
  global _start
  
  _start:
  mov ecx, msgnum1
  mov edx, lenmsgnum1
  call display
  
  mov eax, number1
  call readnum
  
  mov ecx, msgnum2
  mov edx, lenmsgnum2
  call display
  
  mov eax, number2
  call readnum
  
  mov ax, WORD[number1]
  add ax, WORD[number2]
  
  jc error
  
  push ax
  mov ecx, msgresult
  mov edx, lenmsgresult
  
  call display
  
  pop ax
  call displaynum
  
  ;We're done. Exit.
  mov eax, 1
  mov ebx, 0
  int 80h
  
  error:
  mov ecx, msgoverflow
  mov edx, lenmsgoverflow
  call display
  
  ;Send the error code to the OS.
  mov eax, 01
  mov ebx, 01
  int 80h
  
  display:
  mov eax, 04
  mov ebx, 01
  int 80h
  ret
  
  readnum:
  ;Our argument is in eax. Save it to the stack.
  mov WORD[eax], 0
  push eax
  
  read_digit:
  mov eax, 03
  mov ebx, 00
  mov ecx, digit
  mov edx, 1
  int 80h
  
  cmp BYTE[digit], 10
  
  ; Get ebx from the stack.
  pop ebx
  je got_number
  
  sub BYTE[digit], 30h
  
  mov cx, 10

  mov ax, WORD[ebx]
  mul cx
  
  jc error
  
  movzx cx, BYTE[digit]
  add ax, cx
  mov WORD[ebx], ax
  
  push ebx
  
  ;Go back.
  jmp read_digit
  
  got_number:
  ret
  
  displaynum:
  mov BYTE[counter], 0
  mov ebx, strnum
  add ebx, 9
  mov cx, 10
  
  convert:
  mov dx, 0
  div cx
  
  mov BYTE[ebx], dl
  add BYTE[ebx], 48
  dec ebx
  inc BYTE[counter]
  
  cmp ax, 0
  je displaynum_done
  jmp convert
  
  displaynum_done:
  mov ecx, ebx
  inc ecx
  movzx edx, BYTE[counter]
  call display
  ret
