global _start

section .data
	msg: db 'Enter a number between 0-9', 0Ah
	msg_len: equ $-msg
	
	print_sum: db 'Sum of '
	print_sum_len: equ $-print_sum
		
	error: db 'Please Enter single digit', 0Ah
	error_len: equ $-error
	
	
	
section .bss
	number: resb 1
	sum: resw 1
	index: resb 1
	temp: resb 1
	x: resb 1


section .text
	_start:
	
	;enter no. msg
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, msg_len
	int 80h
	
	;read no.
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
	;Comuting sum
	movzx ax, byte[number]
     	sub ax, 30h
        mov word[sum], ax
	jmp ComputingSum
	
   ComputingSum:
	cmp ax, 0
     	je Print_sum
	dec ax
     	add bx, ax
     	jmp ComputingSum
	

Print_sum: 
	mov word[sum], bx
	mov byte[index], 0
	
	mov eax, 4
	mov ebx, 1
	mov ecx, print_sum
	mov edx, print_sum_len
	int 80h
	
	jmp conver_no
	
	conver_no:
		cmp word[sum], 0
			je print_no
		inc byte[index]
		mov dx, 0
		mov ax, word[sum]
		mov bx, 10
		div bx
		push dx
		mov word[sum], ax
	jmp conver_no
	
	print_no: 
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
	
	jmp print_no
	
	
	Exit:	
		;Exit	
		mov eax, 1
		mov ebx, 0
		int 80h
