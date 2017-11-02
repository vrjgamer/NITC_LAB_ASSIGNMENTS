global _start

section .data 
	prompt1: db 'Enter length of array: '
	.length: equ $-prompt1
	
	prompt2: db 'Enter elements of array in ascending order: ', 10
	.length: equ $-prompt2
	
	prompt3: db 'Enter element to search for: '
	.length: equ $-prompt3

	prompt4: db 'Element was not found', 10
	.length: equ $-prompt4

	prompt5: db 'Element found at '
	.length: equ $-prompt5

	endline: db 10

section .bss
	length: resb 1

	input: resb 1
	
	flag: resb 1
	temp: resb 1
	to_search: resb 1
	index: resb 1

	arr: resb 100	

	start: resb 1
	end: resb 1
	mid: resb 1

	output: resw 1

section .text
	_start:	mov eax, 4
		mov ebx, 1
		mov ecx, prompt1
		mov edx, prompt1.length
		int 0x80

		mov byte[input], 0
		call get_ip
		mov byte[length], al
		jmp get_arr
		
	get_ip:	mov eax, 3
		mov ebx, 0
		mov ecx, temp
		mov edx, 1
		int 0x80
		
		cmp byte[temp], 10
			je fin_ip
		sub byte[temp], 30h
		mov al, byte[input]
		mov ah, 10
		mul ah
		add al, byte[temp]
		mov byte[input], al
		jmp get_ip
	
	fin_ip: mov al, byte[input]
		ret
		
	get_arr:mov eax, 4
		mov ebx, 1
		mov ecx, prompt2
		mov edx, prompt2.length
		int 0x80

		mov byte[index], 0

	ip_arr:	mov al, byte[length]
		cmp byte[index], al
			je fin_arr 
		mov byte[input], 0
		call get_ip
		movzx ebx, byte[index] 
		mov byte[arr + ebx], al
		inc byte[index]
		jmp ip_arr

	fin_arr:mov eax, 4
		mov ebx, 1
		mov ecx, prompt3
		mov edx, prompt3.length
		int 0x80

		mov byte[input], 0
		call get_ip
		mov byte[to_search], al
		
		mov byte[flag], 0
		mov byte[start], 0
		mov al, byte[length]
		mov byte[end], al


	search:
		pusha			
		mov ax, 0
		mov al, byte[start]
		add al, byte[end]
		mov bl, 2
		div bl
		mov byte[mid], al	; Finds the midpoint of start and end		

		mov al, byte[start]
		cmp al, byte[end]
			je nfound	; if start equals end, element not found

		movzx eax, byte[mid]
		mov bl, byte[arr + eax]
		
		mov al, byte[to_search]
		cmp al, bl
			je found
			jna greater
			jmp lesser	
	
	greater:mov al, byte[mid]
		mov byte[end], al
		popa
		jmp search

	lesser: mov al, byte[mid]
		mov byte[start], al 
		popa
		jmp search
	
	found:
	      popa
	        mov eax, 4
		mov ebx, 1
		mov ecx, prompt5
		mov edx, prompt5.length
		int 0x80

		movzx ax, byte[mid]
		add ax, 1
		mov word[output], ax
		call printOutput
		
		jmp exit

	nfound: mov eax, 4
		mov ebx, 1
		mov ecx, prompt4
		mov edx, prompt4.length
		int 0x80

	exit: 	mov eax, 4
		mov ebx, 1
		mov ecx, endline
		mov edx, 1
		int 0x80
		
		mov eax, 1
		mov ebx, 0
		int 0x80 	
		
	;write function
	printOutput:
		pusha
		mov byte[index], 0
		extract:
		cmp word[output], 0
		je print
		inc byte[index]
		
		mov edx, 0
		movzx eax, word[output]
		mov ebx, 10
		div ebx
		push edx
		mov word[output], ax
		jmp extract
		
		print:
		
		cmp byte[index], 0
			je end_prt
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
		
	

    	end_prt:
		popa		
		ret			
