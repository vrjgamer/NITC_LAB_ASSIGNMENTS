global _start

;initialized vars
section .data
 msg: db 'Enter a character', 0Ah
 msg_len: equ $-msg
 
 caps_on_msg : db 'CapsLock is On', 0Ah
 caps_on_msg_len: equ $-caps_on_msg
 
 caps_off_msg: db 'CapsLock is Off', 0Ah
 caps_off_msg_len: equ $-caps_off_msg

 invalid_msg: db 'Please Enter alpha-character',0Ah
 invalid_msg_len: equ $-invalid_msg

;uninitialized vars
section .bss
read_var: resb 1


;main code
section .text
	
	_start:
	
	;enter char msg
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, msg_len
	int 80h
	
	;reading 
	mov eax, 3
	mov ebx, 0
	mov ecx, read_var
	mov edx, 1
	int 80h
	
	;checking capslock
	jmp checkCaps
	
checkCaps:
	cmp byte[read_var], 65
	jl invalid_input
	
	cmp byte[read_var], 90
	jl caps_on
	
	cmp byte[read_var], 97
	jl invalid_input
	
	cmp byte[read_var], 122
	jl caps_off
	
	jmp invalid_input
	
caps_on: 
	mov eax, 4
	mov ebx, 1
	mov ecx, caps_on_msg
	mov edx, caps_on_msg_len
	int 80h
	jmp Exit
	
caps_off:
	mov eax, 4
	mov ebx, 1
	mov ecx, caps_off_msg
	mov edx, caps_off_msg_len
	int 80h
	jmp Exit

invalid_input:
	mov eax, 4
	mov ebx, 1
	mov ecx, invalid_msg
	mov edx, invalid_msg_len
	int 80h
	jmp Exit
	
Exit:
	mov eax,1
	mov ebx,0
	int 80h
	
	

	
	
