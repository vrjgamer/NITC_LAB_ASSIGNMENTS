section .data
 	msg: db 'Enter string', 0Ah
	msg_len: equ $-msg
	str_len: db 0
	blank: db 10

section .bss
	strings: resb 500
	container: resb 500
	x: resb 1
	i: resb 8
	j: resb 8
	k: resb 8
	char: resb 1
	temp: resb 1
	temp1: resb 1

section .text
	global _start:
_start:

reading:
	;;read string
	mov ecx,msg
	mov edx,msg_len
	call WRITE
	
	mov ebx,strings
	call READSTRING

mov al, byte[str_len]
mov byte[x], al
dec al
mov byte[i], al
mov byte[k], 0

loop1:
	cmp byte[i], 0
	jl end
	
	mov ebx, strings
	add ebx, dword[i]
	mov al, byte[ebx]
	cmp al, ' '
	je loop2
	cmp byte[i], 0
	je loop2

	dec byte[i]
	jmp loop1

	loop2:
		cmp byte[i], 0
		jne next
		dec byte[i]
		
		next:
			mov al, byte[i]
			inc al
			mov byte[j], al
			
		loop3:
			mov al, byte[x]
			cmp byte[j], al
			jge endloop3
			mov ebx, strings
			add ebx, dword[j]
			mov al, byte[ebx]
			mov ecx, container
			add ecx, dword[k]
			mov byte[ecx], al
			inc byte[k]
			inc byte[j]
			jmp loop3

		endloop3:
			mov al, byte[i]
			mov byte[x], al
			dec byte[i]
			mov ecx, container
			add ecx, dword[k]
			mov byte[ecx], ' '
			inc byte[k]
			jmp loop1
end:
	mov ecx,container
	movzx edx,BYTE[str_len]
	call WRITE
	call NEWLINE
exit:
	mov eax,1
	mov ebx,0
	int 80h

;SUBROUTINES
WRITE:
	mov eax,4
	mov ebx,1
	int 80h
	ret
READ:
	mov eax,3
	mov ebx,0
	int 80h
	ret
NEWLINE:
	mov ecx,blank
	mov edx,1
	call WRITE
	ret
READSTRING:
	mov BYTE[str_len],0
read_character:
	push ebx
	mov ecx,char
	mov edx,1
	call READ
	pop  ebx
	
	cmp BYTE[char],10
	jne carry_on
	ret
carry_on:	
	inc BYTE[str_len]
	mov al,BYTE[char]
	mov BYTE[ebx],al
	add ebx,1
	jmp read_character
