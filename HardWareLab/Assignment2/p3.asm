global _start

section .data
	msg: db 'Enter two numbers', 0Ah
	msg_len: equ $-msg

section .bss
	num1: resd 1
	num2: resd 1
	sum: resd 1
	temp: resb 1
	return: resd 1
	index: resb 1
	

section .text
	_start:
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, msg_len
	int 80h
	
	;reading num1
	call read_loop
	mov num1, return
	
	;reading num2
	call read_loop 
	mov num2, return
	
	mov eax, num1
	mov ebx, num2
	add eax, ebx
	
	mov dword[sum], eax
	
	call printOutput
	
	jmp Exit
	
	;read function	
	read_loop:
		mov return, 0
		
		mov eax, 3
		mov ebx, 0
		mov ecx, temp
		mov edx, 1
		int 80h
		
		cmp byte[temp], 10
		jne read
		
		ret
		
		read:
		mov eax, dword[return]
		mov ebx, 10
		mul ebx
		movzx ebx, byte[temp]
		sub ebx, 30h
		add eax, ebx
		mov dword[return], eax
		jmp read_loop
	
	
	;write function
	printOutput:
		
		extract:
		cmp dword[sum], 0
		je print
		inc byte[index]
		
		mov edx, 0
		mov eax, dword[sum]
		mov ebx, 10
		div ebx
		push edx
		mov dword[sum], eax
		jmp extract
		
		print:
		
		cmp byte[index], 0
		je ret
		dec byte[index]
		pop edx
		mov byte[temp], dl
		add byte[temp], 30h
		
		mov eax, 4
		mov ebx, 1
		mov ecx, temp
		mov edx, 1 
		int 80h
		
		jmp print
		
	
	Exit:
	
	mov eax, 1
	mov ebx, 0
	int 80h
	
		
		