global _start

section .data
	msg: db 'Enter a Digit ', 0Ah
	msg_len: equ $-msg
	
	squ_msg: db 'Square is '
	squ_msg_len: equ $-squ_msg
	
	error: db 'Please Enter single digit', 0Ah
	error_len: equ $-error
			
	next_line: db '',0Ah
	next_line_len: equ $-next_line

section .bss
	number: resb 1
	square: resw 1
	temp: resb 1
	index: resb 1
	x: resb 1

section .text
	
		_start:
		
		;enter digit msg
		mov eax, 4 
		mov ebx, 1
		mov ecx, msg
		mov edx, msg_len
		int 80h
		
		;read 
		mov eax, 3
		mov ebx, 0
		mov ecx, number
		mov edx, 1
		int 80h
		

		mov eax, 3
		mov ebx, 0
		mov ecx, x
		mov edx, 1
		int 80h
		
		cmp byte[x], 10
		jne print_error
		jmp compute		
	
	print_error:
		mov eax, 4
		mov ebx, 1
		mov ecx, error
		mov edx, error_len
		int 80h
		jmp Exit


	compute:
		;computing square
		mov bl, byte[number]
		sub bl, 30h
		mov al, bl
		mul bl
		mov word[square], ax
		jmp print_square
			
		
		;printing square
	print_square:
		mov eax, 4
		mov ebx, 1
		mov ecx, squ_msg
		mov edx, squ_msg_len
		int 80h
	
		conver_number:
			cmp word[square], 0
				je print_loop
			inc byte[index]
			mov dx, 0
			mov ax, word[square]
			mov bx, 10
			div bx
			push dx
			mov word[square], ax
		jmp conver_number		
		
		
		print_loop:
			cmp byte[index], 0
				je Exit
			dec byte[index]
			pop dx
			mov byte[temp], dl
			add byte[temp], 30h
			
			mov eax, 4
			mov ebx, 1
			mov ecx, temp
			mov edx, 1
			int 80h
		jmp print_loop	
		
	Exit:
				
		;Exit	
		mov eax, 1
		mov ebx, 0
		int 80h
