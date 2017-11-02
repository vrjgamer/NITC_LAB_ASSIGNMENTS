global _start

section .data
	msg1: db 0Ah, "Enter the length of array: "
	size_msg1: equ $-msg1
	
	msg2: db 0Ah, "Enter the element: "
	size_msg2: equ $-msg2
	
	result: db 0Ah, "The second largest element is: "
	size_result: equ $-result
	
	new_space: db ' '

section .bss
	array: resb 100
	temp: resb 1
	temp1: resb 1
	nod: resb 1
	num: resb 1
	max: resb 1
	second_max: resb 1
	index: resb 1
	i: resb 1

section .text


	_start:

;Printing the first prompt
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, size_msg1
	int 80h

	call input
	mov ax, word[num]
	mov byte[index], al
	mov byte[i], al

;Reading elements for the array
	mov ebx, array

	read:
	push ebx

;Printing the message to print each element
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, size_msg2
	int 80h

	call input
	mov ax, word[num]

;Adding the number to the array
	pop ebx
	mov byte[ebx], al
	add ebx, 1
	dec byte[i]

	cmp byte[i], 0
	jg read

;Traversing through the elements of array to find the largest number
	movzx ecx, byte[index]
	mov byte[second_max], 0
	mov ebx, array

traverse:
	mov al, byte[ebx]
	cmp byte[second_max], al
	jnl end_traverse
	mov byte[second_max], al

end_traverse:
	add ebx, 1
	loop traverse

;Traversing through the elements of array to find second largest
	movzx ecx, byte[index]
	mov byte[max], 0
	mov ebx, array

traverse2:
	mov al, byte[second_max]
	cmp byte[ebx], al
	je end_traverse2
	mov al, byte[ebx]
	cmp byte[max], al
	jnl end_traverse2
	mov byte[max], al

end_traverse2:
	add ebx, 1
	loop traverse2

;Printing the result

	mov eax, 4
	mov ebx, 1
	mov ecx, result
	mov edx, size_result
	int 80h 

	movzx ax, byte[max]
	mov word[num], ax
	call print

;System Exit
	mov eax, 1
	mov ebx, 0
	int 80h


;Function to read a number
input:

	pusha

	mov word[num], 0

loopadd:
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
	sub byte[temp], 30h
	mov bl, byte[temp]
	mov bh, 0
	add ax, bx
	mov word[num], ax
	jmp loopadd

end_read:
	popa
	ret

;Function to print a number
print:

	pusha

	extract:
		cmp word[num], 0
			je print_no
		inc byte[nod]
		mov dx, 0
		mov ax, word[num]
		mov bx, 10
		div bx
		push dx
		mov word[num], ax
			jmp extract

	print_no:
		cmp byte[nod], 0
		je end_print
		dec byte[nod]
		pop dx
		mov byte[temp], dl
		add byte[temp], 30h

		mov eax, 4
		mov ebx, 1
		mov ecx, temp
		mov edx, 1
		int 80h

		jmp print_no

end_print:

		mov eax, 4
		mov ebx, 1
		mov ecx, new_space
		mov edx, 1
		int 80h

		popa
		ret
