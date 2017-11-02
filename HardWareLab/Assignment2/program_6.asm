global _start

section .data
	msg1: db "Enter the number of the elements",0Ah
	len1: equ $-msg1
	
	msg2: db "Enter the numbers of the array",0Ah
	len2: equ $-msg2
	
	msg3: db "output: ",0Ah
	len3: equ $-msg3
	
	new_line: db 0Ah
	len4: equ $-new_line
	
	msg5: db "invalid input!",0Ah
	len5: equ $-msg5
	
	
section .bss
	array: resw 100
	num: resw 1
	temp: resw 1
	index: resw 1
	temp1: resw 1
	temp2: resw 1
	size: resb 1
	size1: resb 1
	size2: resb 1
	i: resb 1
	j: resb 1
	number: resw 1

section .text

_start

	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,len1
	int 80h

	call read_num
	mov al,byte[num]
	mov byte[size],al
	cmp byte[size],0
	jng invalid
	mov byte[size1],al
	mov byte[size2],al
	
	mov eax,4
	mov ebx,1
	mov ecx,msg2
	mov edx,len2
	int 80h
	
	mov ebx,array
	
	
reading:
	call read_num
	mov ax,word[num]
	mov word[ebx],ax
	add ebx,2
	dec byte[size1]
	cmp byte[size1],0
		jg reading
	push ebx
	
	mov eax,4
	mov ebx,1
	mov ecx,msg3
	mov edx,len3
	int 80h
	
	pop ebx
	dec byte[size2]
	mov ebx,array
	mov byte[i],0
	mov al,byte[size2]
	cmp byte[i],al
		jl first_loop
		jmp print_array
		
		
first_loop:
	mov al,byte[i]
	inc al
	mov byte[j],al
	mov al,byte[size]
	cmp byte[j],al
	jl second_loop
	jmp first_loop

	
second_loop:
	mov ebx,array
	movzx ax,byte[i]
	mov cl,2
	mul cl
	movzx ecx,ax
	add ebx,ecx
	mov ax,word[ebx]
	mov word[temp1],ax
	mov ebx,array
	movzx ax,byte[j]
	mov cl,2
	mul cl
	movzx ecx,ax
	add ebx,ecx
	mov ax,word[ebx]
	mov word[temp2],ax
	mov ax,word[temp2]
	cmp word[temp1],ax
		jl if
		jmp check

if:
	mov ebx,array
	movzx ax,byte[i]
	mov cl,2
	mul cl
	movzx ecx,ax
	add ebx,ecx
	mov ax,word[temp2]
	mov word[ebx],ax
	mov ebx,array
	movzx ax,byte[j]
	mov cl,2
	mul cl
	movzx ecx,ax
	add ebx,ecx
	mov ax,word[temp1]
	mov word[ebx],ax

	jmp check
	
check:
	add byte[j],1
	mov al,byte[size]
	cmp byte[j],al
		jl second_loop
		jmp check2
		
check2:
	add byte[i],1
	mov al,byte[size2]
	cmp byte[i],al
		jl first_loop
	mov ebx,array
		jmp print_array

print_array:
	mov ax,word[ebx]
	mov word[number],ax
	call print_num
	push ebx
	
	mov eax,4
	mov ebx,1
	mov ecx,new_line
	mov edx,len4
	int 80h
	
	pop ebx
	add ebx,2
	dec word[size]
	cmp word[size],0
		jg print_array
		jmp exit

		
read_num:
	pusha
	mov word[num],0

	loop_read:
		mov eax,3
		mov ebx,0
		mov ecx,temp
		mov edx,1
		int 80h

		cmp byte[temp],10
			je end_read

		mov ax,word[num]
		mov bx,10
		mul bx
		mov bl,byte[temp]
		sub bl,30h
		mov bh,0
		add ax,bx
		mov word[num],ax
			jmp loop_read
			
end_read:
		popa
		ret

print_num:
		pusha
		
		extract_no:
			cmp word[number],0
				je print_no
			inc byte[index]
			mov dx,0
			mov ax,word[number]
			mov bx,10
			div bx
			push dx
			mov word[number],ax
				jmp extract_no
		print_no:
			cmp byte[index],0
				je end_print
			dec byte[index]
			pop dx
			mov byte[temp],dl
			add byte[temp],30h
	
			mov eax,4
			mov ebx,1
			mov ecx,temp
			mov edx,1
			int 80h
			
			jmp print_no
end_print:
			popa
			ret

invalid:
	mov eax,4
	mov ebx,1
	mov ecx,msg5
	mov edx,len5
	int 80h
	
	jmp exit
	
exit:
	mov eax,1
	mov ebx,0
	int 80h
